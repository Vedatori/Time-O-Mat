// Autor: Denis Bálint

#include "ToMat/ToMat.h"

// barva
colorRGB color = {255,0,0};

// potřebné proměnné
float notes[7] = {16.35, 18.35, 20.60, 21.83, 24.50, 27.50, 30.87};
float sharpNotes[7] = {17.32, 19.45, 20.60, 23.12, 25.96, 29.14, 30.87};
int multiplyer[8] = {1,2,4,8,16,32,64,128};
bool playing = false;
bool pianoButtonState = false;
bool octaveButtonState = false;
bool sharpButtonState = false;
bool sharpTones = false;
int octave = 1;


void piano();
int TouchbarID();

void setup() {
    
}

void loop() {
    // zavolání funkce piano()
    piano();
}

// funkce která po zavolání vrátí číslo zmáčknutého tlačítka na Touch Baru

int TouchbarID(){
    for(int i = 0; i <= 7; ++i) {
        if(ToMat.touchBar.getPressed(i)){
            return i;
        }
    }
    return -1;
}


// funkce piano

void piano(){

    // zvýšení oktávy

    if(ToMat.buttonRead(2)){
        pianoButtonState = ToMat.buttonRead(2);       
    }
    if(ToMat.buttonRead(2) != pianoButtonState){
        if(ToMat.buttonRead(2) == false){
            octave++;
            if(octave == 8){
                octave = 7;
            }
            pianoButtonState = false;
        }
    }

    //snížení oktávy

    if(ToMat.buttonRead(1)){
        octaveButtonState = ToMat.buttonRead(1);       
    }

    if(ToMat.buttonRead(1) != octaveButtonState){
        if(ToMat.buttonRead(1) == false){
            octave--;
            if(octave == 0){
                octave = 1;
            }
            octaveButtonState = false;
        }
    }

    if(ToMat.touchBar.getPressed(7)){
        sharpButtonState = ToMat.touchBar.getPressed(7);       
    }

    // přepínání mezi ostrými(fis, cis, dis gis) a normálními(f,c,d,g)

    if(ToMat.touchBar.getPressed(7) != sharpButtonState){
        if(ToMat.touchBar.getPressed(7) == false){
            if(sharpTones){
                sharpTones = false;
            } else {
                sharpTones = true;
            }
            sharpButtonState = false;
        }
    }

    if(sharpTones){
        ToMat.display.setText(String(octave) + "  S" , color);
    } else {
        ToMat.display.setText(String(octave) + "   ", color);
    }

    if(TouchbarID() != -1 && TouchbarID() != 7){
        if(!sharpTones){
            ToMat.piezo.tone(notes[TouchbarID()] * multiplyer[octave]);
        } else {
            ToMat.piezo.tone(sharpNotes[TouchbarID()] * multiplyer[octave]);
        }
        
        playing = true;
    }


    
    while (playing){
        if(TouchbarID() == -1){
            playing = false;
            break;
        }
        delay(5);
    }
    
    
    ToMat.piezo.stop();
    delay(5);
}