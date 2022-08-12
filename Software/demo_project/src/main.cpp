#include "Time_o_mat/Time_o_mat.h"

#include <WiFi.h>

const char* ssid       = "";
const char* password   = "";

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

int CCPin[] = {36, 39};

int lightPin[] = {35, 34};

//ColorRGB myColor = {255, 0, 0};
ColorHSV myColor = {0, 1, 1};

void setup() {
    Time_o_mat.begin();

    Time_o_mat.display.setBrightnessFront(0.2);
    Time_o_mat.display.setBrightnessBack(0.0);
    Time_o_mat.display.setTransition(Linear, 0.5);
    Time_o_mat.display.setBacklight(white);

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
            printf("btn%d: %d ", i, Time_o_mat.buttonRead(i));
        }
        
        for(int i = 1; i <= 5; ++i) {
            printf("touch%d: %d ", i, Time_o_mat.touchBar.getRaw(i));
        }

        for(int i = 0; i < 2; ++i) {
            printf("CC%d: %d ", i + 1, analogRead(CCPin[i]));
        }

        for(int i = 0; i < 2; ++i) {
            printf("light%d: %d ", i + 1, analogRead(lightPin[i]));
        }
        
        if(Time_o_mat.buttonRead(1)) {
            Time_o_mat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }

        printf("Priority: %d ", uxTaskPriorityGet(NULL));

        String timeDisp = Time_o_mat.time.getClockText();
        //sprintf(timeDisp, "%2.0f%2.0f", analogRead(CCPin[0])/4095.0*33.0, analogRead(CCPin[1])/4095.0*33.0);
        printf("time: %s\n", timeDisp.c_str());
        Time_o_mat.display.setText(timeDisp, myColor);

        static bool colonState = 0;
        if(colonState)
            Time_o_mat.display.setColon(myColor);
        else
            Time_o_mat.display.setColon(black);
        colonState = !colonState;
    }
    Time_o_mat.display.update();
    delay(20);
}
