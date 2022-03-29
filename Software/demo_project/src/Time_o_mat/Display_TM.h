#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

extern Color red;
extern Color black;

class Display_TM {
    static uint8_t charToIndexMap[21];
    static bool characterSet[51][21];

public:
    void begin();
    void setLED(const int16_t letter, const int16_t position, const Color color);
    void setChar(const int16_t letter, const char character, const Color color);
    void setColon(const Color colorTop, const Color colorBottom);
    void setText(const String text, const Color color);
};


#endif // _DISPLAY_H_