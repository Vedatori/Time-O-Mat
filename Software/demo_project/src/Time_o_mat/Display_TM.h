#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

enum TransitionType {
    None = 0,
    Linear = 1,
    InfiniteImpulseResponse = 2
};

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
    static float currentState[86][3];
    static Color desiredState[86];
    static TransitionType transitionType;
    static float transitionRate;

public:
    static void begin();
    static void update();
    static void setLED(const int16_t digitIndex, const int16_t position, const Color color, int16_t brightness = 255);
    static void setChar(const int16_t digitIndex, const char character, const Color color, int16_t brightness = 255);
    static void setColon(const Color colorTop, const Color colorBottom, int16_t brightness = 255);
    static void setText(const String text, const Color color, int16_t brightness = 255);

    static Color transformColorBrightness(Color color, int16_t brightness);
    static void setTransition(TransitionType aTransitionType, float aTransitionRate);
};

#endif // _DISPLAY_H_