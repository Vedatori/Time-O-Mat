#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

#define LED_PIN 16
#define LED_COUNT 95

typedef struct colorRGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} ColorRGB;

typedef struct colorHSV {
    float hue;
    float saturation;
    float value;
} ColorHSV;

ColorRGB transformColorBrightness(ColorRGB color, float brightness);
ColorRGB HSVtoRGB(ColorHSV color);
ColorHSV RGBtoHSV(ColorRGB color);

enum TransitionType {
    None = 0,
    Linear = 1,
    InfiniteImpulseResponse = 2
};

extern ColorRGB red;
extern ColorRGB green;
extern ColorRGB blue;
extern ColorRGB cyan;
extern ColorRGB magenta;
extern ColorRGB yellow;
extern ColorRGB black;
extern ColorRGB white;

class Display_TM {
    static uint8_t charToIndexMap[21];
    static bool characterSet[51][21];
    static float currentState[LED_COUNT][3];    // {red, green, blue}
    static ColorRGB desiredState[LED_COUNT];
    static float panelBrightness[2];                 // {front, back}
    static TransitionType transitionType;
    static float transitionRate;

public:
    static void begin();
    static void update();

    static void setLED(int segmentID, int ledID, ColorRGB color);
    static void setLED(int segmentID, int ledID, ColorHSV color);

    static void setChar(int charID, char character, ColorRGB color);
    static void setChar(int charID, char character, ColorHSV color);

    static void setColon(ColorRGB color);
    static void setColon(ColorHSV color);

    static void setText(String text, ColorRGB color);
    static void setText(String text, ColorHSV color);

    static void setFront(ColorRGB color);
    static void setFront(ColorHSV color);

    static void setBacklight(ColorRGB color);
    static void setBacklight(ColorHSV color);

    static void setBrightnessFront(float brightness);
    static void setBrightnessBack(float brightness);
    static void setTransition(TransitionType aTransitionType, float aTransitionRate);
};

#endif // _DISPLAY_H_