#ifndef _ILLUMINATION_MODULE_
#define _ILLUMINATION_MODULE_

#include "Arduino.h"

const int PHOTORES_PIN[2] = {36, 39};

class Illumination_module {
    int rawData[2];
public:
    void update();
    int getRaw(int photoresID);
    String getIlluminationText();
};


#endif // _ILLUMINATION_MODULE_