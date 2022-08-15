#include "TouchBar_TM.h"

void TouchBar_TM::begin() {
    for(int i = 0; i < 5; ++i) {
        rawData[i] = touchRead(TOUCH_PIN[i]);
        rawDataIIR[i] = float(rawData[i]);
        digitalData[i] = 0;
    }
}

void TouchBar_TM::update() {
    for(int i = 0; i < 5; ++i) {
        rawData[i] = touchRead(TOUCH_PIN[i]);

        digitalData[i] = rawData[i] < (rawDataIIR[i] - digitalThreshold);

        if(digitalData[i] == false) {
            rawDataIIR[i] = coefIIR*rawData[i] + (1.0 - coefIIR)*rawDataIIR[i];
        }
    }
}

uint16_t TouchBar_TM::getPadRaw(int padID) {
    if(padID < 0 || padID > 4) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return rawData[padID];
}

float TouchBar_TM::getPadRawIIR(int padID) {
    if(padID < 0 || padID > 4) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return rawDataIIR[padID];
}

bool TouchBar_TM::getPadPressed(int padID) {
    if(padID < 0 || padID > 4) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return digitalData[padID];
}

bool TouchBar_TM::getPressed(int buttonID) {
    if(buttonID < 0 || buttonID > 7) {
        printf("Invalid button ID: %d\n", buttonID);
        return 0;
    }

    bool out;
    if(buttonID % 2 == 0) {
        out = digitalData[buttonID/2] && !digitalData[4];
    }
    else {
        out = digitalData[(buttonID - 1)/2] && digitalData[4];
    }
    return out;
}