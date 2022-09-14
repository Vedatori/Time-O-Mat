// Written by Martin Ptáček & Martin Coufal

#include "ToMat/ToMat.h"

const int CONTROL_PERIOD = 100;
int prevControlTime = 0;

ColorRGB colors[3] = {green, white, red};
int numberToColor[37] = {0, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1};
int currNumber = 0;
float currDelay = 0;
char text[10];

int state = 0;  // 0-waiting, 1-cycling, 2-stopping

void updateDisp() {
    sprintf(text, "%2d%2d", currNumber, currNumber);
    ToMat.display.setText(text, colors[numberToColor[currNumber]]);
    currNumber++;
    if(currNumber >= 37) {
        currNumber = 0;
    }
}

void setup() {
    ToMat.begin();

    ToMat.display.setBrightness(frontlight, 0.2);
    ToMat.display.setBrightness(backlight, 0.3);
    //ToMat.display.setTransition(Linear, 0.05);
    ToMat.display.setSegments(backlight, white);
}

void loop() {
    if(millis() > prevControlTime + CONTROL_PERIOD) {
        prevControlTime = millis();

        if(state == 0) {
            if(ToMat.buttonRead(2)) {
                state = 1;
                currDelay = 5;
                ToMat.display.setTransition(all, none, 1);
                ToMat.display.setSegments(colon, black);
                ToMat.display.setSegments(backlight, green);
            }
        }
        else if(state == 1) {
            if(ToMat.touchBar.getPressedIndex() >= 0) {
                state = 2;
                ToMat.display.setSegments(backlight, blue);
            }

        }
        else if(state == 2) {
            currDelay = currDelay * 1.1;
            if(currDelay > 250) {
                ToMat.display.setTransition(all, linear, currDelay/700.0);
            }
            if(currDelay > 1000) {
                state = 0;
                ToMat.display.setSegments(colon, red);
                ToMat.display.setSegments(backlight, white);
            }

        }
		printf("state: %d \n", state);
    }

    if(state == 0) {

    }
    else if(state == 1 || state == 2) {
        updateDisp();
        delay(currDelay);
    }
}