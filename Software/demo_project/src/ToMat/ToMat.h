#ifndef _TOMAT_
#define _TOMAT_

#include <Arduino.h>
#include "Preferences.h"

#include "Music.h"
#include "Display_TM.h"
#include "Time_module.h"
#include "Touchbar_TM.h"
#include "USB_C_power_module.h"
#include "Illumination_module.h"

namespace TM {

const int BUTTON_PIN[3] = {18, 19, 21};
const uint8_t BUZZER_PIN = 17;
const uint8_t ONE_WIRE_PIN = 22;

const uint8_t BUZZER_CHANNEL = 3;

const char STORAGE_NAMESPACE[] = "Time_o_mat";
const uint16_t communicationTimeout = 1000;

void refreshTaskQuick(void * param);
void refreshTaskSlow(void * param);
}

class ToMat_class {
    bool melodyPlaying = false;
    bool melodyPause = false;
    int melodyTempo = 180;
    const int * melody;
    int melodythisNote = 0;
    int melodySize = 0;
    unsigned long melodyLastMillis = 0;

public:
    Display_TM display;
    Time_module time;
    TouchBar_TM touchBar;
    USB_C_power_module power;
    Illumination_module illumination;

    void begin();
    bool buttonRead(int buttonID);

    void soundTone(float freq = 1000);
    void soundEnd();
    void playMelody(const int * aMelody, const int size, const int tempo = 180);
    void stopMelody();
    void handleMelody();

    void printDiagnostics();
};

extern ToMat_class ToMat;

#endif // _TOMAT_