#include "ToMat/ToMat.h"

ColorRGB frontColor = red;
ColorRGB backColor = {255, 180, 85};

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
    ToMat.display.setTransition(all, Exponential, 2.0);
    ToMat.display.setBrightness(all, 0.0);
    ToMat.display.setPanels(backlight, backColor);
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
        frontColor = shiftColor(frontColor, -colorStep, 0, 0);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(3)) {
        frontColor = shiftColor(frontColor, colorStep, 0, 0);
    }

    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(4)) {
        frontColor = shiftColor(frontColor, 0, -colorStep, 0);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(5)) {
        frontColor = shiftColor(frontColor, 0, colorStep, 0);
    }

    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(6)) {
        frontColor = shiftColor(frontColor, 0, 0, -colorStep);
    }
    if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(7)) {
        frontColor = shiftColor(frontColor, 0, 0, colorStep);
    }
    
    // Handle WebApp commands
    if(ToMat.commandGetIndexed(0) == "rgb") {
        frontColor.red = ToMat.commandGetIndexed(1).toInt();
        frontColor.green = ToMat.commandGetIndexed(2).toInt();
        frontColor.blue = ToMat.commandGetIndexed(3).toInt();
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
    ToMat.display.setBrightness(backlight, brightnessBack);

    // Update displayed time
    String timeDisp = ToMat.time.getClockText();
    if(timeDisp[0] == '0') {
        timeDisp[0] = ' ';
    }
    ToMat.display.setText(timeDisp, frontColor);
    ToMat.display.setPanels(colon, frontColor);

    ToMat.printDiagnostics();

    delay(500);
}