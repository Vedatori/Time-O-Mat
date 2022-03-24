#pragma once

#include <Arduino.h>
#include "Preferences.h"

#include "Music.h"


namespace TM {

const uint8_t BUTTON = 18;
const uint8_t BUZZER = 17;

const uint8_t BUZZER_CHANNEL = 3;

const char STORAGE_NAMESPACE[] = "Time_o_mat";
const uint16_t communicationTimeout = 1000;
const uint16_t lettersSwapTimeout = 500;
const uint16_t lettersBlankTimeout = 50;
const uint16_t lettersSweepTimeout =  100;

void updateEnc(void * param);
}

class Time_o_mat_class {
    bool melodyPlaying = false;
    bool melodyPause = false;
    int melodyTempo = 180;
    const int * melody;
    int melodythisNote = 0;
    int melodySize = 0;
    unsigned long melodyLastMillis = 0;

public:
    Time_o_mat_class();
    void begin();

    bool buttonRead();

    void soundTone(float freq = 1000);
    void soundEnd();
    void playMelody(const int * aMelody, const int size, const int tempo = 180);
    void stopMelody();
    void handleMelody();

    void ledWrite(uint8_t id, bool state);
    void ledWriteAnalog(uint8_t id, uint8_t brightness);    // brightness 0-100
};

extern Time_o_mat_class Time_o_mat;
