#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

void setup() {
    ToMat.begin();

    ToMat.startWiFiCaptain("<your_name>");

    ToMat.display.setBrightnessFront(0.2);
    ToMat.display.setBrightnessBack(0.1);
    ToMat.display.setTransition(Linear, 0.5);
    ToMat.display.setBacklight(white);
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();

        if(ToMat.buttonRead(0)) {
            ESP.restart();
        }
        if(ToMat.buttonRead(2)) {
            ToMat.piezo.playMelody(themeMelody);
        }
        
        String timeDisp = ToMat.time.getClockText();
        ToMat.display.setText(timeDisp, red);

        static bool colonState = 0;
        if(colonState)
            ToMat.display.setColon(red);
        else
            ToMat.display.setColon(black);
        colonState = !colonState;

        ToMat.printDiagnostics();
    }
    ToMat.display.update();
    delay(20);
}