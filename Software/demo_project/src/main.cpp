#include "ToMat/ToMat.h"
#include "PubSubClient.h"

ColorRGB displayColor = red;
ColorRGB backgroundColor = black;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
const char* mqtt_server = "192.168.0.127";

void callback(char* topic, byte* message, unsigned int length) {
    String messageTemp;
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    printf("MQTT topic: %s message: %s ", topic, messageTemp.c_str());

    if(String(topic) == "tomatSetRGB") {
        uint8_t r, g, b;
        if(sscanf(messageTemp.c_str(), "%d,%d,%d", &r, &g, &b) == 3) {
            backgroundColor = {r, g, b};
        }
    }
}

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
    ToMat.display.setTransition(all, Exponential, 2.0);
    ToMat.display.setBrightness(frontlight, 0.0);

    delay(5000);
    mqttClient.setServer(mqtt_server, 1883);
    mqttClient.setCallback(callback);
    mqttClient.connect("ToMat");
    printf("mqttClient: %d\n", mqttClient.connected());
    mqttClient.subscribe("tomatSetRGB");
    mqttClient.publish("tomatOn", "true");
}

void loop() {
    // Handle side-button features
    if(ToMat.buttonRead(0)) {
        ESP.restart();
    }
    if(ToMat.buttonRead(1)) {
        ToMat.piezo.playMelody(themeMelodyFull);
    }

    // Handle manual time control
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(0)) {
        ToMat.time.shiftMinutes(-1);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(1)) {
        ToMat.time.shiftMinutes(1);
    }

    // Handle manual color control
    int colorStep = 20;
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(2)) {
        displayColor = shiftColor(displayColor, -colorStep, 0, 0);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(3)) {
        displayColor = shiftColor(displayColor, colorStep, 0, 0);
    }

    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(4)) {
        displayColor = shiftColor(displayColor, 0, -colorStep, 0);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(5)) {
        displayColor = shiftColor(displayColor, 0, colorStep, 0);
    }

    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(6)) {
        displayColor = shiftColor(displayColor, 0, 0, -colorStep);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(7)) {
        displayColor = shiftColor(displayColor, 0, 0, colorStep);
    }
    
    // Handle WebApp commands
    if(ToMat.commandGetIndexed(0) == "rgb") {
        displayColor.red = ToMat.commandGetIndexed(1).toInt();
        displayColor.green = ToMat.commandGetIndexed(2).toInt();
        displayColor.blue = ToMat.commandGetIndexed(3).toInt();
        ToMat.commandClear();
    }
    if(ToMat.commandGetIndexed(0) == "settime") {
        int hours = ToMat.commandGetIndexed(1).toInt();
        int minutes = ToMat.commandGetIndexed(2).toInt();
        ToMat.time.setTime(hours, minutes);
        ToMat.commandClear();
    }
    if(ToMat.commandGetIndexed(0) == "setzone") {
        ToMat.time.setTimeZone(ToMat.commandGetIndexed(1));
        ToMat.commandClear();
    }

    // Update LED brightness
    float illumination = ToMat.illumination.get(0);     // Front photoresistor
    float brightnessFront = ToMat.autoBrightnessFront(illumination);
    float brightnessBack = ToMat.autoBrightnessBack(illumination);
    ToMat.display.setBrightness(frontlight, brightnessFront);
    
    // Update backlight
    ToMat.display.setPanels(backlight, backgroundColor);

    // Update displayed time
    String timeDisp = ToMat.time.getClockText();
    ToMat.display.setText(timeDisp, displayColor);
    ToMat.display.setPanels(colon, displayColor);

    ToMat.printDiagnostics();

    if(ToMat.buttonRead(2)) {
        backgroundColor = red;
        char buffer[16];
        sprintf(buffer, "%d,%d,%d", backgroundColor.red, backgroundColor.green, backgroundColor.blue);
        mqttClient.publish("tomatGetRGB", buffer);
    }

    mqttClient.loop();
    delay(500);
}