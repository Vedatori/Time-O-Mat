#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

extern Color red;
extern Color green;
extern Color blue;
extern Color cyan;
extern Color magenta;
extern Color yellow;
extern Color black;
extern Color white;

class Display_TM {
    static uint8_t charToIndexMap[21];
    static bool characterSet[51][21];
    static Color currentState[86];
    static Color desiredState[86];

public:
    void begin();
    void update();
    void setLED(const int16_t digitIndex, const int16_t position, const Color color, int16_t brightness = 255);
    void setChar(const int16_t digitIndex, const char character, const Color color, int16_t brightness = 255);
    void setColon(const Color colorTop, const Color colorBottom, int16_t brightness = 255);
    void setText(const String text, const Color color, int16_t brightness = 255);

    static Color transformColorBrightness(Color color, int16_t brightness);
};

#endif // _DISPLAY_H_