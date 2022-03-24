#include "Time_o_mat/Time_o_mat.h"
#include "Adafruit_NeoPixel.h"
#include "OneWire.h"
#include "DallasTemperature.h"

const uint8_t CONTROL_PERIOD = 200;
uint32_t prevControlTime = 0;

Adafruit_NeoPixel pixels(86, 16, NEO_GRB + NEO_KHZ800);

uint8_t buttonPin[] = {18, 19, 21};

OneWire oneWire(22);
DallasTemperature sensors(&oneWire);

uint8_t touchPads[] = {12, 14, 27, 33, 32};

void setup() {
    Time_o_mat.begin();
    pixels.begin();

    for(uint8_t i = 0; i < 3; ++i) {
        pinMode(buttonPin[i], INPUT_PULLUP);
    }
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
            uint16_t touch_value = 0;
            
            printf("touch%d: %d ", i, touchRead(touchPads[i]));
        }

        printf("\n");

        if(!digitalRead(buttonPin[0])) {
            Time_o_mat.playMelody(takeonme, sizeof(takeonme), takeonme_tempo);
        }

        pixels.clear();
        for(uint8_t i = 0; i < 86; ++i) {
            pixels.setPixelColor(i, pixels.Color(50, 0, 0));
        }
        pixels.show();
    }
}
