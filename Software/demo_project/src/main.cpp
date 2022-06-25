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

const uint16_t CONTROL_PERIOD = 1000;
uint32_t prevControlTime = 0;

uint8_t buttonPin[] = {18, 19, 21};

OneWire oneWire(22);
DallasTemperature sensors(&oneWire);

uint8_t touchPads[] = {12, 14, 27, 33, 32};

uint8_t CCPin[] = {36, 39};

uint8_t lightPin[] = {35, 34};

void setup() {
    Time_o_mat.begin();

    for(uint8_t i = 0; i < 3; ++i) {
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
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();
        for(uint8_t i = 0; i < 3; ++i) {
            printf("btn%d: %d ", i + 1, !digitalRead(buttonPin[i]));
        }
        sensors.requestTemperatures(); 
        printf("temp: %f ", sensors.getTempCByIndex(0)); 

        for(uint8_t i = 0; i < 5; ++i) {
            printf("touch%d: %d ", i, touchRead(touchPads[i]));
        }

        struct tm time;
        if(!getLocalTime(&time)){
            printf("No time available (yet)\n");
        }
        printf("time: %02d:%02d ", time.tm_hour, time.tm_min);

        for(uint8_t i = 0; i < 2; ++i) {
            printf("CC%d: %d ", i + 1, analogRead(CCPin[i]));
        }

        for(uint8_t i = 0; i < 2; ++i) {
            printf("light%d: %d ", i + 1, analogRead(lightPin[i]));
        }

        printf("\n");

        if(!digitalRead(buttonPin[0])) {
            Time_o_mat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }

        char timeDisp[4];
        sprintf(timeDisp, "%02d%02d", time.tm_hour, time.tm_min);
        //Time_o_mat.display.setChar(2, '3', red);
        Time_o_mat.display.setText(timeDisp, red);

        static bool colonState = 0;
        if(colonState)
            Time_o_mat.display.setColon(red, red);
        else
            Time_o_mat.display.setColon(black, black);
        colonState = !colonState;

        Time_o_mat.display.update();
    }
}
