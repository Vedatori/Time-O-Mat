#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");

    ToMat.display.setBrightnessFront(0.2);
    ToMat.display.setBrightnessBack(0.1);
    ToMat.display.setTransition(Linear, 0.5);
    ToMat.display.setBack(white);
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();

        if(ToMat.buttonRead(0)) {
            ESP.restart();
        }
		if(ToMat.buttonRead(1)){
			ToMat.weather.getWeather().printDebug();
			while(ToMat.buttonRead(1));
		}
        if(ToMat.buttonRead(2)) {
            ToMat.piezo.playMelody(themeMelodyFull);
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
    delay(20);
}