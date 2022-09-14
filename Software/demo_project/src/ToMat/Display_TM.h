#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

#define LED_PIN 16
#define LED_COUNT 95
#define RATE_MIN 0.1

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

typedef struct segmentSelector {
    bool digitLeftLeft;
    bool digitCenterLeft;
    bool colon;
    bool digitCenterRight;
    bool digitRightRight;
    bool backlight;
} SegmentSelector;

enum TransitionType {
    none = 0,
    linear = 1,
    infiniteImpulseResponse = 2
};

extern ColorRGB red;
extern ColorRGB green;
extern ColorRGB blue;
extern ColorRGB cyan;
extern ColorRGB magenta;
extern ColorRGB yellow;
extern ColorRGB black;
extern ColorRGB white;

extern SegmentSelector all;
extern SegmentSelector frontlight;
extern SegmentSelector backlight;
extern SegmentSelector digits;
extern SegmentSelector colon;

class Display_TM {
    static uint8_t charToIndexMap[21];
    static bool characterSet[51][21];
    static float currentState[LED_COUNT][3];    // {red, green, blue}
    static ColorRGB desiredState[LED_COUNT];
    static float panelBrightness[6];            // {leftLeft, centerLeft, colon, centerRight, rightRight, backlight}
    static TransitionType transitionType[6];
    static float transitionRate[6];             // [seconds/fullRange]
    static bool updateActive;

public:
    static void begin();
    static void update();
    static void setUpdateActive(bool state);
    static bool getSegmentSelected(SegmentSelector selector, int segmentID);
    static int getSegmentIndex(int ledID);

    static void setLED(int segmentID, int ledID, ColorRGB color);
    static void setLED(int segmentID, int ledID, ColorHSV color);

    static void setSegment(int segmentID, ColorRGB color);
    static void setSegment(int segmentID, ColorHSV color);

    static void setSegments(SegmentSelector selector, ColorRGB color);
    static void setSegments(SegmentSelector selector, ColorHSV color);

    static void setChar(int charID, char character, ColorRGB color);
    static void setChar(int charID, char character, ColorHSV color);

    static void setText(String text, ColorRGB color);
    static void setText(String text, ColorHSV color);

    static void setBrightness(SegmentSelector selector, float brightness);
    static void setTransition(SegmentSelector selector, TransitionType aTransitionType, float aTransitionRate);
};

#endif // _DISPLAY_H_