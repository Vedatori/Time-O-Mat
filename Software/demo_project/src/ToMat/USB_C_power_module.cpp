#include "USB_C_power_module.h"

void USB_C_power_module::setMode(PowerMode mode) {
    currentMode = mode;
}

void USB_C_power_module::update() {
    for(int i = 0; i < 2; ++i) {
        pinVoltage[i] = analogRead(CC_PIN[i]) / 4095.0 * 33.0;
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
        case Automatic:
            ;
        default:
            currentMode = USB2_500mA;
            return 0.5;
    }
}

String USB_C_power_module::getVoltagesText() {
    char voltagesText[25];
    sprintf(voltagesText, "CC1: %.1fV CC2: %.1fV ", pinVoltage[0], pinVoltage[1]);
    return String(voltagesText);
}