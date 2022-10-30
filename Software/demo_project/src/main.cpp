#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;
ColorRGB displayColor = red;
ColorRGB backlightColor = white;

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");

    ToMat.display.setTransition(all, linear, 3.0);
    ToMat.display.setTransition(colon, linear, 1.0);
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();

        if(ToMat.buttonRead(0)) {
            ESP.restart();
        }
        if(ToMat.buttonRead(1)) {
            ToMat.piezo.playMelody(themeMelodyFull);
        }

        if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(0)) {
            ToMat.time.shiftMinutes(-1);
        }
        if(ToMat.buttonRead(2) && ToMat.touchBar.getPressed(1)) {
            ToMat.time.shiftMinutes(1);
        }

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


        float displayBrightness, backlightBrightness;
        float illumination = ToMat.illumination.getRaw(0) / 4095.0;
        if(illumination > 0.7) {
            displayBrightness = (illumination - 0.7) / 0.3 * 0.8 + 0.2;
            backlightBrightness = 0.0;
        }
        else if(illumination > 0.5) {
            displayBrightness = (illumination - 0.5) / 0.2 * 0.15 + 0.05;
            backlightBrightness = -(illumination - 0.5) / 0.2 * 0.1 + 0.1;
        }
        else if(illumination > 0.2) {
            displayBrightness = (illumination - 0.2) / 0.3 * 0.046 + 0.004;
            backlightBrightness = (illumination - 0.2) / 0.3 * 0.1;
        }
        else {
            displayBrightness = 0.004;
            backlightBrightness = 0.0;
        }

        ToMat.display.setBrightness(frontlight, displayBrightness);
        ToMat.display.setBrightness(backlight, backlightBrightness);

        String timeDisp = ToMat.time.getClockText();
        ToMat.display.setText(timeDisp, displayColor);
        ToMat.display.setSegments(backlight, backlightColor);

        static bool colonState = 0;
        if(colonState)
            ToMat.display.setSegments(colon, displayColor);
        else
            ToMat.display.setSegments(colon, black);
        colonState = !colonState;

        //ToMat.printDiagnostics();
    }
    delay(20);
}