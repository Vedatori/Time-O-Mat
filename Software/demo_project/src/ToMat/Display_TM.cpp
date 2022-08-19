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

ColorRGB transformColorBrightness(ColorRGB color, float brightness) {

    color.red = constrain(round(color.red * brightness), 0, 255);
    color.green = constrain(round(color.green * brightness), 0, 255);
    color.blue = constrain(round(color.blue * brightness), 0, 255);
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
    setFront(black);
    setBack(black);
    setBrightnessFront(1.0);
    setBrightnessBack(1.0);
    update();
    setUpdateActive(false);
}

void Display_TM::update() {
    int timeNow = millis();
    static int timePrev = timeNow;
    float step = transitionRate * (timeNow - timePrev) / 1000.0 * 255.0;
    timePrev = timeNow;

    if(updateActive == false) {
        return;
    }

    for(uint8_t ledID = 0; ledID < LED_COUNT; ++ledID) {
        switch(transitionType) {
            case Linear: {
                float deviation = desiredState[ledID].red - currentState[ledID][0];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][0] = desiredState[ledID].red;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][0] += sign * step;
                }

                deviation = desiredState[ledID].green - currentState[ledID][1];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][1] = desiredState[ledID].green;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][1] += sign * step;
                }

                deviation = desiredState[ledID].blue - currentState[ledID][2];
                if(abs(deviation) < (step + 1.0)) {
                    currentState[ledID][2] = desiredState[ledID].blue;
                }
                else {
                    int8_t sign = deviation > 0 ? 1 : -1;
                    currentState[ledID][2] += sign * step;
                }
            } break;
            case InfiniteImpulseResponse:
            case None:
            default:
                currentState[ledID][0] = desiredState[ledID].red;
                currentState[ledID][1] = desiredState[ledID].green;
                currentState[ledID][2] = desiredState[ledID].blue;
        }
        uint32_t color = pixels.Color(round(currentState[ledID][0]), round(currentState[ledID][1]), round(currentState[ledID][2]));
        pixels.setPixelColor(ledID, color);
    }
    pixels.show();
}

void Display_TM::setUpdateActive(bool state) {
    updateActive = state;
}

void Display_TM::setLED(int segmentID, int ledID, ColorRGB color) {
    if(segmentID < 0 || segmentID > 5)
        return;
    if(ledID < 0 || ledID > 20)
        return;
    
    int ledAbsoluteID = 0;
    int ledSide = 0;    // 0-front, 1-back

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
        ledSide = 1;
    }

    if(ledAbsoluteID < 0 || ledAbsoluteID > LED_COUNT) {
        return;
    }
    
    desiredState[ledAbsoluteID] = transformColorBrightness(color, panelBrightness[ledSide]);
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

void Display_TM::setColon(ColorRGB color) {
    setLED(2, 0, color);
    setLED(2, 1, color);
}
void Display_TM::setColon(ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setColon(colorRGB);
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

void Display_TM::setFront(ColorRGB color) {
   setText("8888", color);
   setColon(color);
}

void Display_TM::setFront(ColorHSV color) {
   setText("8888", color);
   setColon(color);
}

void Display_TM::setBack(ColorRGB color) {
    for(int i = 0; i < 9; ++i) {
        setLED(5, i, color);
    }
}

void Display_TM::setBack(ColorHSV color) {
    ColorRGB colorRGB = HSVtoRGB(color);
    setBack(colorRGB);
}

void Display_TM::setBrightnessFront(float brightness) {
    panelBrightness[0] = constrain(brightness, 0.0, 1.0);
}

void Display_TM::setBrightnessBack(float brightness) {
    panelBrightness[1] = constrain(brightness, 0.0, 1.0);
}

void Display_TM::setTransition(TransitionType aTransitionType, float aTransitionRate) {
    transitionType = aTransitionType;
    transitionRate = aTransitionRate;
}

float Display_TM::currentState[LED_COUNT][3] = {0.0, };
ColorRGB Display_TM::desiredState[LED_COUNT] = {black, };
float Display_TM::panelBrightness[] = {1.0, 1.0};
TransitionType Display_TM::transitionType = None;
float Display_TM::transitionRate = 1.0;
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