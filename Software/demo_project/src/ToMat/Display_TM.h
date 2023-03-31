#ifndef _DISPLAY_TM_H_
#define _DISPLAY_TM_H_

#include "Arduino.h"

#define LED_PIN 16
#define LED_COUNT 95
#define RATE_MIN 0.1

enum TransitionType {
    None = 0,
    Linear = 1,
    Exponential = 2
};

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

typedef struct panelSelector {
    bool digitLeftLeft;
    bool digitCenterLeft;
    bool colon;
    bool digitCenterRight;
    bool digitRightRight;
    bool backlight;
} PanelSelector;

typedef struct ledState {
    ColorRGB targetColor;
    float currentColor[3];          // {red, green, blue} - True displayed color
    float brightness;               // [0.0-1.0]
    TransitionType transitionType;
    float transitionRate;           // [seconds/fullRange]
    bool updateNeeded;
} LedState;

ColorRGB dimColor(ColorRGB color, float brightness);
ColorRGB shiftColor(ColorRGB color, int red, int green, int blue);
ColorRGB HSVtoRGB(ColorHSV color);
ColorHSV RGBtoHSV(ColorRGB color);

extern ColorRGB red;
extern ColorRGB green;
extern ColorRGB blue;
extern ColorRGB cyan;
extern ColorRGB magenta;
extern ColorRGB yellow;
extern ColorRGB black;
extern ColorRGB white;
extern ColorRGB pink;
extern ColorRGB brown;
extern ColorRGB salmon;
extern ColorRGB orange;
extern ColorRGB gold;
extern ColorRGB tomato;

extern PanelSelector all;
extern PanelSelector frontlight;
extern PanelSelector backlight;
extern PanelSelector digits;
extern PanelSelector colon;

class Display_TM {
    static LedState ledState[LED_COUNT];
    static bool updateActive;                   // 0-not active, 1-active
    static uint8_t charToIndexMap[21];          // Logical to physical LED index mapping for 1 digit
    static bool characterSet[51][21];           // Symbol alphabet

    static bool isPanelSelected(PanelSelector selector, int panelID);
    static int getPanelID(int ledID);
    static int getLedAbsID(int panelID, int ledID);
    static ColorRGB updateLedState(LedState & state, int timeStep);

public:
    static void begin();
    static void update();
    static void setUpdateActive(bool state);

    static void setLED(int panelID, int ledID, ColorRGB color);
    static void setLED(int panelID, int ledID, ColorHSV color);

    static void setPanel(int panelID, ColorRGB color);
    static void setPanel(int panelID, ColorHSV color);

    static void setPanels(PanelSelector selector, ColorRGB color);
    static void setPanels(PanelSelector selector, ColorHSV color);

    static void setChar(int charID, char character, ColorRGB color);
    static void setChar(int charID, char character, ColorHSV color);

    static void setText(String text, ColorRGB color);
    static void setText(String text, ColorHSV color);

    static void setBrightness(PanelSelector selector, float brightness);
    static void setTransition(PanelSelector selector, TransitionType aTransitionType, float apanelTransRate);
};

#endif // _DISPLAY_H_