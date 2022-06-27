#include "Display_TM.h"

#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel pixels(86, 16, NEO_GRB + NEO_KHZ800);

Color red = {255, 0, 0};
Color green = {0, 255, 0};
Color blue = {0, 0, 255};
Color cyan = {0, 255, 255};
Color magenta = {255, 0, 255};
Color yellow = {255, 255, 0};
Color black = {0, 0, 0};
Color white = {255, 255, 255};

void Display_TM::begin() {
    pixels.begin();
}

void Display_TM::update() {
    for(uint8_t ledID = 0; ledID < 86; ++ledID) {
        uint32_t color = pixels.Color(desiredState[ledID].red, desiredState[ledID].green, desiredState[ledID].blue);
        pixels.setPixelColor(ledID, color);
    }
    pixels.show();
}

void Display_TM::setLED(const int16_t digitIndex, const int16_t position, const Color color, int16_t brightness) {
    if(digitIndex < 0 || digitIndex > 4)
        return;
    if(position < 0 || position > 20)
        return;
    brightness = constrain(brightness, 0, 255);
    
    int16_t ledID = 0;
    if(digitIndex < 2)
        ledID = digitIndex*21 + charToIndexMap[position];
    else if(digitIndex < 4)
        ledID = digitIndex*21 + charToIndexMap[position] + 2;   // center colon offset
    else
        ledID = position + 42;

    if(ledID < 0 || ledID > 85) {
        return;
    }
    
    desiredState[ledID] = transformColorBrightness(color, brightness);
}

void Display_TM::setChar(const int16_t digitIndex, const char character, const Color color, int16_t brightness) {
    if(digitIndex < 0 || digitIndex > 3)
        return;
    if(character < 40 || character > 91)
        return;

    for(uint8_t i = 0; i < 21; ++i) {
        if(characterSet[character - 40][i]) {
            setLED(digitIndex, i, color, brightness);
        }
        else {
            setLED(digitIndex, i, black, brightness);
        }
    }
}

void Display_TM::setColon(const Color colorTop, const Color colorBottom, int16_t brightness) {
    setLED(4, 1, colorTop, brightness);
    setLED(4, 0, colorBottom, brightness);
}

void Display_TM::setText(const String text, const Color color, int16_t brightness) {
    for(uint8_t i = 0; i < 4; ++i) {
        setChar(i, text[i], color, brightness);
    }
}

Color Display_TM::transformColorBrightness(Color color, int16_t brightness) {
    color.red = constrain(round(color.red * brightness / 255.0), 0, 255);
    color.green = constrain(round(color.green * brightness / 255.0), 0, 255);
    color.blue = constrain(round(color.blue * brightness / 255.0), 0, 255);
    return color;
}

Color Display_TM::currentState[86] = {black, };
Color Display_TM::desiredState[86] = {black, };
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