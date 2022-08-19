#ifndef _USB_C_POWER_MODULE_
#define _USB_C_POWER_MODULE_

#include "Arduino.h"

enum PowerMode {
    USB2_500mA = 0,
    USB3_900mA = 1,
    Medium_1500mA = 2,
    High_3000mA = 3,
    Automatic = 4
};

const int CC_PIN[2] = {36, 39};

class USB_C_power_module {
    float pinVoltage[2];
    PowerMode currentMode = USB2_500mA; // By default lowest limit

public:
    void setMode(PowerMode mode);
    void update();
    float getLimitA();
    String getVoltagesText();
};

#endif // _USB_C_POWER_MODULE_