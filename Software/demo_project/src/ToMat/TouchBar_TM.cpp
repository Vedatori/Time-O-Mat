#include "TouchBar_TM.h"

void TouchBar_TM::begin() {
    for(int i = 0; i < 5; ++i) {
        rawData[i][0] = touchRead(TOUCH_PIN[i]);
        rawData[i][1] = rawData[i][0];
        rawDataIIR[i] = float(getPadRaw(i));
        digitalData[i] = 0;
    }
}

void TouchBar_TM::update() {
    for(int i = 0; i < 5; ++i) {
        rawData[i][1] = rawData[i][0];
        rawData[i][0] = touchRead(TOUCH_PIN[i]);

        uint8_t rawFiltered = getPadRaw(i);

        digitalData[i] = rawFiltered < (rawDataIIR[i] - digitalThreshold);

        if(digitalData[i] == false) {
            rawDataIIR[i] = coefIIR*rawFiltered + (1.0 - coefIIR)*rawDataIIR[i];
        }
    }
}

uint16_t TouchBar_TM::getPadRaw(int padID) {
    if(padID < 0 || padID > 4) {
        printf("Invalid pad ID: %d\n", padID);
        return 0;
    }
    return max(rawData[padID][0], rawData[padID][1]);;
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

int TouchBar_TM::getPressedIndex() {
    for(int i = 0; i < 8; ++i) {
        if(getPressed(i)) {
            return i;
        }
    }
    return -1;
}