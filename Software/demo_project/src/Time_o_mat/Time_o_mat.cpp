#include "Time_o_mat.h"

#include "OneWire.h"
#include "DallasTemperature.h"

OneWire oneWire(TM::ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void TM::refreshTaskQuick(void * parameter) {
    for(;;) {
        Time_o_mat.handleMelody();
        //Time_o_mat.display.update();
        //delayMicroseconds(500);
        Time_o_mat.touchBar.update();
        delay(20);
    }
}

void TM::refreshTaskSlow(void * parameter) {
    for(;;) {
        sensors.requestTemperatures();
        Time_o_mat.power.update();
        printf("temp: %f \n", sensors.getTempCByIndex(0));
        delay(1000);
    }
}

void Time_o_mat_class::begin() {

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

bool Time_o_mat_class::buttonRead(int buttonID) {
    if(buttonID < 1 || buttonID > 3) {
        printf("Invalid button ID: %d\n", buttonID);
        return 0;
    }
    return !digitalRead(TM::BUTTON_PIN[buttonID - 1]);  // 1 = pressed
}

void Time_o_mat_class::soundTone(float freq) {
    ledcAttachPin(TM::BUZZER_PIN, TM::BUZZER_CHANNEL);
    ledcWriteTone(TM::BUZZER_CHANNEL, freq);
}
void Time_o_mat_class::soundEnd() {
    ledcDetachPin(TM::BUZZER_PIN);
}

void Time_o_mat_class::playMelody(const int * aMelody, const int size, const int tempo)
{
	Time_o_mat_class::melodyPlaying = true;
    Time_o_mat_class::melodyPause = true;
    Time_o_mat_class::melodyTempo = tempo;
    Time_o_mat_class::melody = aMelody;
    Time_o_mat_class::melodythisNote = 0;
    Time_o_mat_class::melodySize = size;
}

void Time_o_mat_class::stopMelody(){
    Time_o_mat_class::melodyPlaying = false;
    Time_o_mat.soundEnd();
}

void Time_o_mat_class::handleMelody(){
    if(!Time_o_mat_class::melodyPlaying){
        return;
    }
    int notes = Time_o_mat_class::melodySize / sizeof(int) / 2;
    int wholenote = ((60000 * 4) / Time_o_mat_class::melodyTempo);
    int divider = 0, noteDuration = 0;

    divider = Time_o_mat_class::melody[Time_o_mat_class::melodythisNote + 1];
	if (divider > 0) {
	// regular note, just proceed
	    noteDuration = (wholenote) / divider;
	} else if (divider < 0) {
	// dotted notes are represented with negative durations!!
	    noteDuration = (wholenote) / abs(divider);
	    noteDuration *= 1.5; // increases the duration in half for dotted notes
	}

    if((millis() >= Time_o_mat_class::melodyLastMillis+(noteDuration*0.9))&&!Time_o_mat_class::melodyPause){
        Time_o_mat_class::melodyPause=true;
        Time_o_mat_class::melodythisNote+=2;
        Time_o_mat_class::soundEnd();
        if(Time_o_mat_class::melodythisNote>notes*2){
            Time_o_mat_class::melodyPlaying = false;
            return;
        }
        Time_o_mat_class::melodyLastMillis = millis();
    }else if((millis() >= Time_o_mat_class::melodyLastMillis+(noteDuration*0.1))&&Time_o_mat_class::melodyPause){
        Time_o_mat_class::soundTone(Time_o_mat_class::melody[Time_o_mat_class::melodythisNote]);
        Time_o_mat_class::melodyPause=false;
        Time_o_mat_class::melodyLastMillis = millis();
    }
}

Time_o_mat_class Time_o_mat;
