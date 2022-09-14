#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");

    ToMat.display.setBrightness(frontlight, 0.2);
    ToMat.display.setBrightness(backlight, 0.05);
    ToMat.display.setTransition(all, linear, 1.0);
    ToMat.display.setSegments(backlight, white);
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
            ToMat.display.setSegments(colon, red);
        else
            ToMat.display.setSegments(colon, black);
        colonState = !colonState;

        ToMat.printDiagnostics();
    }
    delay(20);
}