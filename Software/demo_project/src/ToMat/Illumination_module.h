#ifndef _ILLUMINATION_MODULE_
#define _ILLUMINATION_MODULE_

#include "Arduino.h"

const int PHOTORES_PIN[2] = {34, 35};   // Front, back

class Illumination_module {
    int rawData[2];
public:
    void update();
    float get(int photoresID);
    int getRaw(int photoresID);
    String getIlluminationText();
};

#endif // _ILLUMINATION_MODULE_