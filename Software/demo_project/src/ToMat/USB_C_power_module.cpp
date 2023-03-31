#include "USB_C_power_module.h"

void USB_C_power_module::begin(int pinA, int pinB) {
    ccPins[0] = pinA;
    ccPins[1] = pinB;
    update();
}

void USB_C_power_module::setMode(PowerMode mode) {
    currentMode = mode;
}

void USB_C_power_module::update() {
    for(int i = 0; i < 2; ++i) {
        pinVoltage[i] = analogRead(ccPins[i]) / 4095.0 * 3.2;
    }
}

float USB_C_power_module::getLimitA() {
    switch(currentMode) {
        case USB2_500mA:
            return 0.5;
        case USB3_900mA:
            return 0.9;
        case Medium_1500mA:
            return 1.5;
        case High_3000mA:
            return 3.0;
        case Automatic: {
            float minV = (pinVoltage[0] < pinVoltage[1]) ? pinVoltage[0] : pinVoltage[1];
            float maxV = (pinVoltage[0] > pinVoltage[1]) ? pinVoltage[0] : pinVoltage[1];
            if(minV > 0.1) {
                // Error, return minimal limit
                return 0.5;
            }
            if(maxV > 1.3) {
                return 3.0;
            }
            if(maxV > 0.7) {
                return 1.5;
            }
            return 0.9;
        }
        default:
            currentMode = USB2_500mA;
            return 0.5;
    }
}

String USB_C_power_module::getVoltagesText() {
    char voltagesText[25];
    sprintf(voltagesText, "CC1: %.2fV CC2: %.2fV ", pinVoltage[0], pinVoltage[1]);
    return String(voltagesText);
}