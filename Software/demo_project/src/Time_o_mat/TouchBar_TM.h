#ifndef _TOUCHBAR_H_
#define _TOUCHBAR_H_

#include <Arduino.h>

const int TOUCH_PIN[5] = {33, 27, 14, 12, 32};

class TouchBar_TM {
    uint16_t rawData[5];

public:
    void begin();
    void update();
    uint16_t getRaw(int padID);
};

#endif // _TOUCHBAR_H_