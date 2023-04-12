#include "Illumination_module.h"

void Illumination_module::update() {
    for(int i = 0; i < 2 ; ++i) {
        rawData[i] = analogRead(PHOTORES_PIN[i]);
    }
}

int Illumination_module::getRaw(int photoresID) {
    if(photoresID < 0 || photoresID > 1) {
        printf("Invalid photores ID: %d\n", photoresID);
        return 0;
    }
    return rawData[photoresID];
}

float Illumination_module::get(int photoresID) {
    if(photoresID < 0 || photoresID > 1) {
        printf("Invalid photores ID: %d\n", photoresID);
        return 0;
    }
    return float(rawData[photoresID])/4095.0;
}

String Illumination_module::getIlluminationText() {
    char illuminationText[32];
    sprintf(illuminationText, "photo0: %d photo1: %d ", rawData[0], rawData[1]);
    return String(illuminationText);
}