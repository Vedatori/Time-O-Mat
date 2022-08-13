#include "ToMat/ToMat.h"

#include <WiFi.h>

const char* ssid = "Vedatori1";
const char* password = "Kytice15";

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

//ColorRGB myColor = {255, 0, 0};
ColorHSV myColor = {0, 1, 1};

void setup() {
    ToMat.begin();

    ToMat.display.setBrightnessFront(0.2);
    ToMat.display.setBrightnessBack(0.0);
    ToMat.display.setText("    ", myColor);
    ToMat.display.update();
    delay(500);
    ToMat.display.setText("----", myColor);
    ToMat.display.update();
    ToMat.display.setTransition(Linear, 0.5);
    ToMat.display.setBacklight(white);

    printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printf(".");
    }
    printf("connected\n");
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();
        
        for(int i = 1; i <= 3; ++i) {
            printf("btn%d: %d ", i, ToMat.buttonRead(i));
        }
        
        for(int i = 1; i <= 5; ++i) {
            printf("touch%d: %d ", i, ToMat.touchBar.getRaw(i));
        }

        printf("%s", ToMat.power.getVoltagesText().c_str());
        printf("%s", ToMat.illumination.getIlluminationText().c_str());
        
        if(ToMat.buttonRead(1)) {
            ToMat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }
        if(ToMat.buttonRead(3)) {
            ESP.restart();
        }

        printf("Priority: %d ", uxTaskPriorityGet(NULL));

        String timeDisp = ToMat.time.getClockText();
        //sprintf(timeDisp, "%2.0f%2.0f", analogRead(CCPin[0])/4095.0*33.0, analogRead(CCPin[1])/4095.0*33.0);
        printf("time: %s\n", timeDisp.c_str());
        ToMat.display.setText(timeDisp, myColor);

        static bool colonState = 0;
        if(colonState)
            ToMat.display.setColon(myColor);
        else
            ToMat.display.setColon(black);
        colonState = !colonState;
    }
    ToMat.display.update();
    delay(20);
}
