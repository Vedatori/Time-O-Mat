#include "ToMat/ToMat.h"

ColorRGB displayColor = red;

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
    ToMat.display.setTransition(all, Exponential, 2.0);
    ToMat.display.setBrightness(all, 0.0);
    ToMat.display.setPanels(backlight, white);
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
    ToMat.display.setBrightness(backlight, brightnessBack);

    // Update displayed time
    String timeDisp = ToMat.time.getClockText();
    ToMat.display.setText(timeDisp, displayColor);
    ToMat.display.setPanels(colon, displayColor);

    ToMat.printDiagnostics();

    delay(500);
}