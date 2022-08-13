#include "Illumination_module.h"

void Illumination_module::update() {
    for(int i = 0; i < 2 ; ++i) {
        rawData[i] = analogRead(PHOTORES_PIN[i]);
    }
}

int Illumination_module::getRaw(int photoresID) {
    if(photoresID < 1 || photoresID > 2) {
        printf("Invalid photores ID: %d\n", photoresID);
        return 0;
    }
    return rawData[photoresID - 1];
}

String Illumination_module::getIlluminationText() {
    char illuminationText[32];
    sprintf(illuminationText, "photo1: %d photo2: %d ", rawData[0], rawData[1]);
    return String(illuminationText);
}