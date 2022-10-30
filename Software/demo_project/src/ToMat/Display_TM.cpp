#include "Display_TM.h"

#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

ColorRGB black = {0, 0, 0};
ColorRGB white = {255, 255, 255};
ColorRGB red = {255, 0, 0};
ColorRGB green = {0, 255, 0};
ColorRGB blue = {0, 0, 255};
ColorRGB cyan = {0, 255, 255};
ColorRGB magenta = {255, 0, 255};
ColorRGB yellow = {255, 255, 0};

SegmentSelector all = {1, 1, 1, 1, 1, 1};
SegmentSelector frontlight = {1, 1, 1, 1, 1, 0};
SegmentSelector backlight = {0, 0, 0, 0, 0, 1};
SegmentSelector digits = {1, 1, 0, 1, 1, 0};
SegmentSelector colon = {0, 0, 1, 0, 0, 0};

ColorRGB transformColorBrightness(ColorRGB color, float brightness) {

    color.red = constrain(round(color.red * brightness), 0, 255);
    color.green = constrain(round(color.green * brightness), 0, 255);
    color.blue = constrain(round(color.blue * brightness), 0, 255);
    return color;
}

ColorRGB shiftColor(ColorRGB color, int red, int green, int blue) {
    color.red = constrain(color.red + red, 0, 255);
    color.green = constrain(color.green + green, 0, 255);
    color.blue = constrain(color.blue + blue, 0, 255);
    return color;
}

ColorRGB HSVtoRGB(ColorHSV color) {
    float H = constrain(color.hue, 0, 360);
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
    // TODO
    ColorHSV colorHSV;
    return colorHSV;
}

void Display_TM::begin() {
    pixels.begin();
    setSegments(all, black);
    setBrightness(all, 1.0);
    update();
    setUpdateActive(false);
}

void Display_TM::update() {
    int timeNow = millis();
    static int timePrev = timeNow;
    int timeDiff = timeNow - timePrev;
    timePrev = timeNow;

    if(updateActive == false) {
        return;
    }

    for(uint8_t ledID = 0; ledID < LED_COUNT; ++ledID) {
        int segmentID = getSegmentIndex(ledID);
        ColorRGB dimmedColor = transformColorBrightness(desiredState[ledID], panelBrightness[segmentID]);
        float step = timeDiff / 1000.0 * 255.0 / transitionRate[segmentID];

        switch(transitionType[segmentID]) {
            case linear: {
                float deviation = dimmedColor.red - currentState[ledID][0];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][0] = dimmedColor.red;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][0] += sign * step;
                }

                deviation = dimmedColor.green - currentState[ledID][1];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][1] = dimmedColor.green;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][1] += sign * step;
                }

                deviation = dimmedColor.blue - currentState[ledID][2];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][2] = dimmedColor.blue;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][2] += sign * step;
                }
            } break;
            case infiniteImpulseResponse:
            case none:
            default:
                currentState[ledID][0] = dimmedColor.red;
                currentState[ledID][1] = dimmedColor.green;
                currentState[ledID][2] = dimmedColor.blue;
        }
        uint32_t color = pixels.Color(round(currentState[ledID][0]), round(currentState[ledID][1]), round(currentState[ledID][2]));
        pixels.setPixelColor(ledID, color);
    }
    pixels.show();
}

void Display_TM::setUpdateActive(bool state) {
    updateActive = state;
}

bool Display_TM::getSegmentSelected(SegmentSelector selector, int segmentID) {
    switch(segmentID) {
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

int Display_TM::getSegmentIndex(int ledID) {
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

void Display_TM::setLED(int segmentID, int ledID, ColorRGB color) {
    if(segmentID < 0 || segmentID > 5)
        return;
    if(ledID < 0 || ledID > 20)
        return;
    
    int ledAbsoluteID = 0;

    // 2 leftmost digits
    if(segmentID <= 1)
        ledAbsoluteID = segmentID * 21 + charToIndexMap[ledID];

    // Center colon
    else if(segmentID == 2) {
        if(ledID > 1)
            return;
        ledAbsoluteID = segmentID * 21 + ledID;
    }
        
    // 2 rightmost digits
    else if(segmentID <= 4)
        ledAbsoluteID = (segmentID - 1) * 21 + 2 + charToIndexMap[ledID];
    
    // Backlight
    else {
        if(ledID > 8)
            return;
        ledAbsoluteID = (segmentID - 1) * 21 + 2 + ledID;
    }

    if(ledAbsoluteID < 0 || ledAbsoluteID > LED_COUNT) {
        return;
    }
    
    desiredState[ledAbsoluteID] = color;
}

void Display_TM::setSegment(int segmentID, ColorRGB color) {
    for(int i = 0; i < 21; ++i) {
        setLED(segmentID, i, color);
    }
}
void Display_TM::setSegment(int segmentID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setSegment(segmentID, colorRGB);
}

void Display_TM::setSegments(SegmentSelector selector, ColorRGB color) {
    for(int i = 0; i < 6; ++i) {
        if(getSegmentSelected(selector, i) == true) {
            setSegment(i, color);
        }
    }
}

void Display_TM::setSegments(SegmentSelector selector, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setSegments(selector, colorRGB);
} 

void Display_TM::setLED(int digitIndex, int ledID, ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setLED(digitIndex, ledID, colorRGB);
}

void Display_TM::setChar(int charID, char character, ColorRGB color) {
    if(charID < 0 || charID > 3)
        return;
	int segmentID = charID;
    if(segmentID >= 2)
        ++segmentID;    // center colon segment offset
	
	if(character == ' '){
		for(uint8_t i = 0; i < 21; ++i) {
			setLED(segmentID, i, black);
		}
	}

    if((character < 40 || character > 91))
        return;
    for(uint8_t i = 0; i < 21; ++i) {
        if(characterSet[character - 40][i]) {
            setLED(segmentID, i, color);
        }
        else {
            setLED(segmentID, i, black);
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

void Display_TM::setBrightness(SegmentSelector selector, float brightness) {
    for(int i = 0; i < 6; ++i) {
        if(getSegmentSelected(selector, i) == true) {
            panelBrightness[i] = constrain(brightness, 0.0, 1.0);
        }
    }
}

void Display_TM::setTransition(SegmentSelector selector, TransitionType aTransitionType, float aTransitionRate) {
    if(aTransitionRate < RATE_MIN) {
        aTransitionRate = RATE_MIN;
    }

    for(int i = 0; i < 6; ++i) {
        if(getSegmentSelected(selector, i) == true) {
            transitionType[i] = aTransitionType;
            transitionRate[i] = aTransitionRate;
        }
    }
}

float Display_TM::currentState[LED_COUNT][3] = {0.0, };
ColorRGB Display_TM::desiredState[LED_COUNT] = {black, };
float Display_TM::panelBrightness[] = {1.0, };
TransitionType Display_TM::transitionType[] = {none, };
float Display_TM::transitionRate[] = {1.0, };
bool Display_TM::updateActive = true;
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