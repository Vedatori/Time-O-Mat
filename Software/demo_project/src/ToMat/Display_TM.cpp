#include "Display_TM.h"

#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

ColorRGB red = {255, 0, 0};
ColorRGB green = {0, 255, 0};
ColorRGB blue = {0, 0, 255};
ColorRGB cyan = {0, 255, 255};
ColorRGB magenta = {255, 0, 255};
ColorRGB yellow = {255, 255, 0};
ColorRGB black = {0, 0, 0};
ColorRGB white = {255, 255, 255};
ColorRGB pink = {255, 192, 203};
ColorRGB brown = {165, 42, 42};
ColorRGB salmon = {250, 128, 114};
ColorRGB orange = {255, 165, 0};
ColorRGB gold = {255, 215, 0};
ColorRGB tomato = {255, 99, 71};

PanelSelector all = {1, 1, 1, 1, 1, 1};
PanelSelector frontlight = {1, 1, 1, 1, 1, 0};
PanelSelector backlight = {0, 0, 0, 0, 0, 1};
PanelSelector digits = {1, 1, 0, 1, 1, 0};
PanelSelector colon = {0, 0, 1, 0, 0, 0};

ColorRGB dimColor(ColorRGB color, float brightness) {
    brightness = constrain(brightness, 0.0, 1.0);

    uint8_t * colorPtr = (uint8_t *)&color;
    for(int i = 0; i < 3; ++i) {
        colorPtr[i] = constrain(colorPtr[i] * brightness, 0, 255);
    }
    return color;
}

ColorRGB shiftColor(ColorRGB color, int red, int green, int blue) {
    color.red = constrain(color.red + red, 0, 255);
    color.green = constrain(color.green + green, 0, 255);
    color.blue = constrain(color.blue + blue, 0, 255);
    return color;
}

ColorRGB HSVtoRGB(ColorHSV color) {
    float H = color.hue;
    while(H < 0) {
        H += 360;
    }
    while(H > 360) {
        H -= 360;
    }
    float s = constrain(color.saturation, 0, 1);
    float v = constrain(color.value, 0, 1);

    float C = s*v;
    float X = C* (1- fabs(fmod(H/ 60, 2)- 1));
    float m = v-C;
    float r, g, b;

    if(H > 300) {
        r = C;
        g = 0;
        b = X;
    }
    else if(H > 240) {
        r = X;
        g = 0;
        b = C;
    }
    else if(H > 180) {
        r = 0;
        g = X;
        b = C;
    }
    else if(H > 120) {
        r = 0;
        g = C;
        b = X;
    }
    else if(H > 60) {
        r = X;
        g = C;
        b = 0;
    }
    else {
        r = C;
        g = X;
        b = 0;
    }
    
    ColorRGB colorRGB;
    colorRGB.red = constrain(round((r+m)*255), 0, 255);
    colorRGB.green = constrain(round((g+m)*255), 0, 255);
    colorRGB.blue = constrain(round((b+m)*255), 0, 255);
    return colorRGB;
}

ColorHSV RGBtoHSV(ColorRGB color) {
    uint8_t * colorPtr = (uint8_t *)&color;
    float colorNorm[3];
    for(int colorID = 0; colorID < 3; ++colorID) {
        colorNorm[colorID] = colorPtr[colorID] / 255.0;
    }

    int maxID = 0, minID = 0;  // 0-red, 1-green, 2-blue
    float mMax = 0, mMin = 0;
    if(colorNorm[0] >= colorNorm[1] && colorNorm[0] >= colorNorm[2]) {
        mMax = colorNorm[0];
        maxID = 0;
    }
    else if(colorNorm[1] >= colorNorm[0] && colorNorm[1] >= colorNorm[2]) {
        mMax = colorNorm[1];
        maxID = 1;
    }
    else {
        mMax = colorNorm[2];
        maxID = 2;
    }
    if(colorNorm[0] <= colorNorm[1] && colorNorm[0] <= colorNorm[2]) {
        mMin = colorNorm[0];
        minID = 0;
    }
    else if(colorNorm[1] <= colorNorm[0] && colorNorm[1] <= colorNorm[2]) {
        mMin = colorNorm[1];
        minID = 1;
    }
    else {
        mMin = colorNorm[2];
        minID = 2;
    }

    float c = mMax - mMin;
    float colorTemp[3];
    for(int colorID = 0; colorID < 3; ++colorID) {
        colorTemp[colorID] = (mMax - colorNorm[colorID]) / c;
    }
    float hTemp = 0;
    if(maxID == minID) {
        hTemp = 0;
    }
    else if (maxID == 0) {
        hTemp = colorTemp[2] - colorTemp[1];
    }
    else if (maxID == 1) {
        hTemp = 2 + colorTemp[0] - colorTemp[2];
    }
    else if (maxID == 2) {
        hTemp = 4 + colorTemp[1] - colorTemp[0];
    }
    while(hTemp < 0) {
        hTemp += 6.0;
    }
    while(hTemp > 6.0) {
        hTemp -= 6.0;
    }

    float hue = hTemp / 6 * 360;
    float saturation = c / mMax;
    float value = mMax;

    ColorHSV colorHSV;
    colorHSV.hue = constrain(hue, 0, 360);
    colorHSV.saturation = constrain(saturation, 0, 1);
    colorHSV.value = constrain(value, 0, 1);
    return colorHSV;
}

bool Display_TM::isPanelSelected(PanelSelector selector, int panelID) {
    switch(panelID) {
        case 0:
            return selector.digitLeftLeft;
        case 1:
            return selector.digitCenterLeft;
        case 2:
            return selector.colon;
        case 3:
            return selector.digitCenterRight;
        case 4:
            return selector.digitRightRight;
        case 5:
            return selector.backlight;
        default:
            return false;
    }
}

int Display_TM::getPanelID(int ledID) {
    if(ledID < 0)
        return -1;
    if(ledID < 21)
        return 0;
    if(ledID < 42)
        return 1;
    if(ledID < 44)
        return 2;
    if(ledID < 65)
        return 3;
    if(ledID < 86)
        return 4;
    if(ledID < 95)
        return 5;
    else
        return -1;
}

int Display_TM::getLedAbsID(int panelID, int ledID) {
    if(panelID < 0 || panelID > 5)
        return -1;
    if(ledID < 0 || ledID > 20)
        return -1;
    
    int ledAbsoluteID = 0;

    // 2 leftmost digits
    if(panelID <= 1)
        ledAbsoluteID = panelID * 21 + charToIndexMap[ledID];

    // Center colon
    else if(panelID == 2) {
        if(ledID > 1)
            return -1;
        ledAbsoluteID = panelID * 21 + ledID;
    }
        
    // 2 rightmost digits
    else if(panelID <= 4)
        ledAbsoluteID = (panelID - 1) * 21 + 2 + charToIndexMap[ledID];
    
    // Backlight
    else {
        if(ledID > 8)
            return -1;
        ledAbsoluteID = (panelID - 1) * 21 + 2 + ledID;
    }

    if(ledAbsoluteID < 0 || ledAbsoluteID > LED_COUNT) {
        return -1;
    }
    return ledAbsoluteID;
}

ColorRGB Display_TM::updateLedState(LedState & state, int timeStep) {
    ColorRGB color = dimColor(state.targetColor, state.brightness);
    uint8_t * colorPtr = (uint8_t *)&color;
    
    float deviation[3];
    for(int ledID = 0; ledID < 3; ++ledID) {
        deviation[ledID] = colorPtr[ledID] - state.currentColorF[ledID];
    }

    float step = 0;
    switch(state.transitionType) {
        case Linear: {
            step = timeStep / 1000.0 * 441.7 / state.transitionRate;
        } break;
        case Exponential: {
            float currentColorSize = pow(pow(state.currentColorF[0], 2) + pow(state.currentColorF[1], 2) + pow(state.currentColorF[2], 2), 0.5);
            float beginStep = 0.01 * timeStep;
            step = beginStep + currentColorSize * (pow(441.7 / beginStep, timeStep / 1000.0 / state.transitionRate) - 1.0);
        } break;
        case None:
        default:
            step = 441.7;    // Maximal step to cover full diagonal at once
    }

    float devSize = pow(pow(deviation[0], 2) + pow(deviation[1], 2) + pow(deviation[2], 2), 0.5);
    for(int ledID = 0; ledID < 3; ++ledID) {
        if(devSize < (step + 0.1)) {
            state.currentColorF[ledID] = colorPtr[ledID];
        }
        else {
            state.currentColorF[ledID] += deviation[ledID] / devSize * step;
        }
    }
    state.updateNeeded = devSize > 0.1;
    
    state.currentColor.red = constrain(round(state.currentColorF[0]), 0, 255);
    state.currentColor.green = constrain(round(state.currentColorF[1]), 0, 255);
    state.currentColor.blue = constrain(round(state.currentColorF[2]), 0, 255);
    return state.currentColor;
}

void Display_TM::begin() {
    pixels.begin();
    setPanels(all, black);
    setBrightness(all, 1.0);
    setTransition(all, None, 1.0);
    update();
}

void Display_TM::update() {
    int timeNow = millis();
    static int timePrev = timeNow;
    int timeStep = timeNow - timePrev;
    timePrev = timeNow;

    if(updateActive == false) {
        return;
    }

    bool updateNeeded = false;
    int sumRGB = 0;
    for(uint8_t ledID = 0; ledID < LED_COUNT; ++ledID) {
        ColorRGB currentColor = updateLedState(ledState[ledID], timeStep);
        sumRGB += (currentColor.red + currentColor.green + currentColor.blue);
        updateNeeded = updateNeeded || ledState[ledID].updateNeeded;
    }

    if(sumRGB <= 0) {
        sumRGB = 1; // prevent zero division
    }
    float ratio = currentLimit / (float(sumRGB) / 255.0 / float(LED_COUNT) * 1.12);
    currentLimitRatio = constrain(ratio, 0.0, 1.0);
    
    for(uint8_t ledID = 0; ledID < LED_COUNT; ++ledID) {
        ColorRGB powerLimitColor = dimColor(ledState[ledID].currentColor, currentLimitRatio);
        uint32_t color = pixels.Color(powerLimitColor.red, powerLimitColor.green, powerLimitColor.blue);
        pixels.setPixelColor(ledID, color);
    }

    if(updateNeeded) {
        pixels.show();
    }
}

void Display_TM::setUpdateActive(bool state) {
    updateActive = state;
}

void Display_TM::setCurrentLimit(float limit) {
    limit = constrain(limit, 0.0, 3.0);

    currentLimit = limit;
}

float Display_TM::getCurrentLimitRatio() {
    return currentLimitRatio;
}

void Display_TM::setLED(int panelID, int ledID, ColorRGB color) {
    int ledAbsID = getLedAbsID(panelID, ledID);
    ledState[ledAbsID].targetColor = color;
}

void Display_TM::setLED(int panelID, int ledID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setLED(panelID, ledID, colorRGB);
}

void Display_TM::setPanel(int panelID, ColorRGB color) {
    for(int i = 0; i < 21; ++i) {
        setLED(panelID, i, color);
    }
}
void Display_TM::setPanel(int panelID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setPanel(panelID, colorRGB);
}

void Display_TM::setPanels(PanelSelector selector, ColorRGB color) {
    for(int i = 0; i < 6; ++i) {
        if(isPanelSelected(selector, i) == true) {
            setPanel(i, color);
        }
    }
}

void Display_TM::setPanels(PanelSelector selector, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setPanels(selector, colorRGB);
} 

void Display_TM::setChar(int charID, char character, ColorRGB color) {
    if(charID < 0 || charID > 3)
        return;
	int panelID = charID;
    if(panelID >= 2)
        ++panelID;    // center colon panel offset
	
	if(character == ' '){
		for(uint8_t i = 0; i < 21; ++i) {
			setLED(panelID, i, black);
		}
	}

    if((character < 40 || character > 91))
        return;
    for(uint8_t i = 0; i < 21; ++i) {
        if(characterSet[character - 40][i]) {
            setLED(panelID, i, color);
        }
        else {
            setLED(panelID, i, black);
        }
    }
}
void Display_TM::setChar(int charID, char character, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setChar(charID, character, colorRGB);
}

void Display_TM::setText(String text, ColorRGB color) {
    for(uint8_t i = 0; i < 4; ++i) {
        setChar(i, text[i], color);
    }
}
void Display_TM::setText(String text, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setText(text, colorRGB);
}

void Display_TM::setBrightness(PanelSelector selector, float brightness) {
    brightness = constrain(brightness, 0.0, 1.0);

    for(int ledID = 0; ledID < LED_COUNT; ++ledID) {
        int panelID = getPanelID(ledID);
        if(isPanelSelected(selector, panelID) == true) {
            ledState[ledID].brightness = brightness;
        }
    }
}

void Display_TM::setTransition(PanelSelector selector, TransitionType transition, float rate) {
    if(rate < RATE_MIN) {
        rate = RATE_MIN;
    }

    for(int ledID = 0; ledID < LED_COUNT; ++ledID) {
        int panelID = getPanelID(ledID);
        if(isPanelSelected(selector, panelID) == true) {
            ledState[ledID].transitionType = transition;
            ledState[ledID].transitionRate = rate;
        }
    }
}

LedState Display_TM::ledState[LED_COUNT] = {0, };
bool Display_TM::updateActive = false;
float Display_TM::currentLimit = 3.0;
float Display_TM::currentLimitRatio = 1.0;
uint8_t Display_TM::charToIndexMap[21] = {0, 1, 2, 17, 3, 16, 4, 15, 5, 18, 19, 20, 14, 6, 13, 7, 12, 8, 11, 10, 9};
bool Display_TM::characterSet[51][21] = {
    {   // "("
           1, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           1, 0, 0,
    },
    {   // ")"
           0, 0, 1,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 1,
    },
    {   // "*"
           0, 0, 1,
        0,          1,
        0,          0,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           0, 0, 0,
    },
    {   // "+"
           0, 1, 0,
        0,          0,
        0,          0,
        0,          0,
           1, 1, 1,
        0,          0,
        0,          0,
        0,          0,
           0, 1, 0,
    },
    {   // ","
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "-"
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           1, 1, 1,
        0,          0,
        0,          0,
        0,          0,
           0, 0, 0,
    },
    {   // "."
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          0,
        0,          1,
           0, 0, 0,
    },
    {   // "/"
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "0"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "1"
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "2"
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    },
    {   // "3"
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
    },
    {   // "4"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "5"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
    },
    {   // "6"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "7"
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "8"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "9"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
    },
    {   // ":"
           0, 0, 0,
        0,          0,
        0,          1,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          1,
        0,          0,
           0, 0, 0,
    },
    {   // ";"
           0, 0, 0,
        0,          0,
        0,          1,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "<"
           0, 0, 0,
        0,          0,
        0,          0,
        0,          1,
           1, 1, 1,
        0,          1,
        0,          0,
        0,          0,
           0, 0, 0,
    },
    {   // "="
           1, 1, 1,
        0,          0,
        0,          0,
        0,          0,
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           1, 1, 1,
    },
    {   // ">"
           0, 0, 0,
        0,          0,
        0,          0,
        1,          0,
           1, 1, 1,
        1,          0,
        0,          0,
        0,          0,
           0, 0, 0,
    },
    {   // "?"
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 1, 0,
    },
    {   // "@"
           1, 1, 1,
        1,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "A"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
    },
    {   // "B"
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "C"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    },
    {   // "D"
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "E"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    },
    {   // "F"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "G"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "H"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
    },
    {   // "I"
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "J"
           0, 0, 0,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "K"
           0, 0, 0,
        1,          0,
        1,          0,
        1,          1,
           1, 1, 1,
        1,          1,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "L"
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    },
    {   // "M"
           1, 0, 1,
        1,          1,
        1,          1,
        1,          1,
           0, 1, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
    },
    {   // "N"
           1, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 1, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 1,
    },
    {   // "O"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "P"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "Q"
           1, 1, 1,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           0, 0, 0,
    },
    {   // "R"
           0, 0, 0,
        0,          0,
        0,          0,
        0,          0,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           0, 0, 0,
    },
    {   // "S"
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
    },
    {   // "T"
           0, 0, 0,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
        1,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    },
    {   // "U"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
    },
    {   // "V"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 0, 0,
        1,          1,
        0,          0,
        0,          0,
           0, 1, 0,
    },
    {   // "W"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           0, 1, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 0, 1,
    },
    {   // "X"
           0, 0, 0,
        1,          1,
        1,          1,
        0,          0,
           0, 1, 0,
        0,          0,
        1,          1,
        1,          1,
           0, 0, 0,
    },
    {   // "Y"
           0, 0, 0,
        1,          1,
        1,          1,
        1,          1,
           1, 1, 1,
        0,          1,
        0,          1,
        0,          1,
           1, 1, 1,
    },
    {   // "Z"
           1, 1, 1,
        0,          1,
        0,          1,
        0,          0,
           0, 1, 0,
        0,          0,
        1,          0,
        1,          0,
           1, 1, 1,
    }
};