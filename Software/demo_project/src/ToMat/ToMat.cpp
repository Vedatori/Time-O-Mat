#include "ToMat.h"

#include "OneWire.h"
#include "DallasTemperature.h"

OneWire oneWire(TM::ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void TM::refreshTaskQuick(void * parameter) {
    for(;;) {
        ToMat.handleMelody();
        //ToMat.display.update();
        //delayMicroseconds(500);
        ToMat.touchBar.update();
        delay(20);
    }
}

void TM::refreshTaskSlow(void * parameter) {
    for(;;) {
        sensors.requestTemperatures();
        ToMat.power.update();
        printf("temp: %f \n", sensors.getTempCByIndex(0));
        delay(1000);
    }
}

void ToMat_class::begin() {

    power.update();
    illumination.update();
    display.begin();
    time.begin();
    touchBar.begin();

    for(int i = 0; i < 3; ++i) {
        pinMode(TM::BUTTON_PIN[i], INPUT_PULLUP);
    }

    //sensors.begin();
    
    xTaskCreatePinnedToCore(TM::refreshTaskQuick, "refreshTaskQuick", 10000 , NULL, 3, NULL, 1);
    //xTaskCreatePinnedToCore(TM::refreshTaskSlow, "refreshTaskSlow", 10000 , NULL, 0, NULL, 0);

    ledcSetup(TM::BUZZER_CHANNEL, 1000, 10);
}

bool ToMat_class::buttonRead(int buttonID) {
    if(buttonID < 1 || buttonID > 3) {
        printf("Invalid button ID: %d\n", buttonID);
        return 0;
    }
    return !digitalRead(TM::BUTTON_PIN[buttonID - 1]);  // 1 = pressed
}

void ToMat_class::soundTone(float freq) {
    ledcAttachPin(TM::BUZZER_PIN, TM::BUZZER_CHANNEL);
    ledcWriteTone(TM::BUZZER_CHANNEL, freq);
}
void ToMat_class::soundEnd() {
    ledcDetachPin(TM::BUZZER_PIN);
}

void ToMat_class::playMelody(const int * aMelody, const int size, const int tempo)
{
	ToMat_class::melodyPlaying = true;
    ToMat_class::melodyPause = true;
    ToMat_class::melodyTempo = tempo;
    ToMat_class::melody = aMelody;
    ToMat_class::melodythisNote = 0;
    ToMat_class::melodySize = size;
}

void ToMat_class::stopMelody(){
    ToMat_class::melodyPlaying = false;
    ToMat.soundEnd();
}

void ToMat_class::handleMelody(){
    if(!ToMat_class::melodyPlaying){
        return;
    }
    int notes = ToMat_class::melodySize / sizeof(int) / 2;
    int wholenote = ((60000 * 4) / ToMat_class::melodyTempo);
    int divider = 0, noteDuration = 0;

    divider = ToMat_class::melody[ToMat_class::melodythisNote + 1];
	if (divider > 0) {
	// regular note, just proceed
	    noteDuration = (wholenote) / divider;
	} else if (divider < 0) {
	// dotted notes are represented with negative durations!!
	    noteDuration = (wholenote) / abs(divider);
	    noteDuration *= 1.5; // increases the duration in half for dotted notes
	}

    if((millis() >= ToMat_class::melodyLastMillis+(noteDuration*0.9))&&!ToMat_class::melodyPause){
        ToMat_class::melodyPause=true;
        ToMat_class::melodythisNote+=2;
        ToMat_class::soundEnd();
        if(ToMat_class::melodythisNote>notes*2){
            ToMat_class::melodyPlaying = false;
            return;
        }
        ToMat_class::melodyLastMillis = millis();
    }else if((millis() >= ToMat_class::melodyLastMillis+(noteDuration*0.1))&&ToMat_class::melodyPause){
        ToMat_class::soundTone(ToMat_class::melody[ToMat_class::melodythisNote]);
        ToMat_class::melodyPause=false;
        ToMat_class::melodyLastMillis = millis();
    }
}

ToMat_class ToMat;
