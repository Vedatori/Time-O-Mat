#include "Time_o_mat/Time_o_mat.h"

#include <WiFi.h>
#include "time.h"
#include "sntp.h"

const char* ssid       = "";
const char* password   = "";

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

#include "OneWire.h"
#include "DallasTemperature.h"

const int CONTROL_PERIOD = 500;
int prevControlTime = 0;

int buttonPin[] = {18, 19, 21};

OneWire oneWire(22);
DallasTemperature sensors(&oneWire);

int touchPads[] = {33, 27, 14, 12, 32};

int CCPin[] = {36, 39};

int lightPin[] = {35, 34};

//ColorRGB myColor = {255, 0, 0};
float myHue = 0;
float myValue = 1;
ColorHSV myColor = {myHue, 1, myValue};

void setup() {
    Time_o_mat.begin();

    for(int i = 0; i < 3; ++i) {
        pinMode(buttonPin[i], INPUT_PULLUP);
    }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

    printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printf(".");
    }
    printf("connected\n");
    Time_o_mat.display.setBrightnessFront(0.5);
    Time_o_mat.display.setBrightnessBack(0.2);
    Time_o_mat.display.setTransition(Linear, 0.5);
    Time_o_mat.display.setBacklight(white);
}

void loop() {
    myHue = myHue + 0.05;
    myValue = map(analogRead(lightPin[1]), 0, 4095, 200, 1000);
    myValue = myValue/1000;

    if(myHue > 360){
        myHue = 0;
    }
    myColor = {myHue, 1, myValue};

    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();
        for(int i = 0; i < 3; ++i) {
            printf("btn%d: %d ", i + 1, !digitalRead(buttonPin[i]));
        }
        sensors.requestTemperatures(); 
        printf("temp: %f ", sensors.getTempCByIndex(0)); 

        for(int i = 0; i < 5; ++i) {
            printf("touch%d: %d ", i, touchRead(touchPads[i]));
        }

        struct tm time;
        if(!getLocalTime(&time)){
            printf("No time available (yet)\n");
        }
        printf("time: %02d:%02d ", time.tm_hour, time.tm_min);

        for(int i = 0; i < 2; ++i) {
            printf("CC%d: %d ", i + 1, analogRead(CCPin[i]));
        }

        for(int i = 0; i < 2; ++i) {
            printf("light%d: %d ", i + 1, analogRead(lightPin[i]));
        }

        printf("\n");

        if(!digitalRead(buttonPin[0])) {
            Time_o_mat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }

        char timeDisp[4];
        sprintf(timeDisp, "%02d%02d", time.tm_hour, time.tm_min);
        //sprintf(timeDisp, "%2.0f%2.0f", analogRead(CCPin[0])/4095.0*33.0, analogRead(CCPin[1])/4095.0*33.0);
        printf("%s\n", timeDisp);
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
