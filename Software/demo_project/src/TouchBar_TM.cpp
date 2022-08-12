#include "TouchBar_TM.h"

void TouchBar_TM::begin() {
    for(int i = 0; i < 5; ++i) {
        rawData[i] = 0;
    }
}

void TouchBar_TM::update() {
    for(int i = 0; i < 5; ++i) {
        rawData[i] = touchRead(TOUCH_PIN[i]);
    }
}

uint16_t TouchBar_TM::getRaw(int padID) {
    if(padID < 1 || padID > 5) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return rawData[padID - 1];
}