#ifndef _TOUCHBAR_H_
#define _TOUCHBAR_H_

#include <Arduino.h>

const int TOUCH_PIN[5] = {33, 27, 14, 12, 32};

class TouchBar_TM {
    uint16_t rawData[5][2];
    float rawDataIIR[5];
    bool digitalData[5];
    float coefIIR = 0.01;
    int digitalThreshold = 5.0;

public:
    void begin();
    void update();
    uint16_t getPadRaw(int padID);
    float getPadRawIIR(int padID);
    bool getPadPressed(int padID);
    bool getPressed(int buttonID);
};

#endif // _TOUCHBAR_H_