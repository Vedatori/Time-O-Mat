#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

ColorRGB myColor = {255, 0, 0};

void setup() {
    ToMat.begin();

    ToMat.display.setBrightnessFront(0.2);
    ToMat.display.setBrightnessBack(0.1);
    ToMat.display.setText("    ", myColor);
    ToMat.display.update();
    delay(500);
    ToMat.display.setText("----", myColor);
    ToMat.display.update();
    ToMat.display.setTransition(Linear, 0.5);
    ToMat.display.setBacklight(white);

    ToMat.startWiFiCaptain("<your_name>");
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();
      
        if(ToMat.buttonRead(1)) {
            ToMat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }
        if(ToMat.buttonRead(3)) {
            ESP.restart();
        }

        String timeDisp = ToMat.time.getClockText();
        ToMat.display.setText(timeDisp, myColor);

        static bool colonState = 0;
        if(colonState)
            ToMat.display.setColon(myColor);
        else
            ToMat.display.setColon(black);
        colonState = !colonState;

        ToMat.printDiagnostics();
    }
    ToMat.display.update();
    delay(20);
}