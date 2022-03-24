#include "Time_o_mat.h"
#include "Preferences.h"

#include "DisplayCharactersSet.h"

void TM::updateEnc(void * parameter) {
    for(;;) {
        Time_o_mat.handleMelody();
        delayMicroseconds(500);
    }
}

Time_o_mat_class::Time_o_mat_class(void) {
}

void Time_o_mat_class::begin() {
    
    xTaskCreatePinnedToCore(TM::updateEnc, "updateEnc", 10000 , (void*) 0, 1, NULL, 1);

    ledcSetup(TM::BUZZER_CHANNEL, 1000, 10);
}

bool Time_o_mat_class::buttonRead() {
    // 0-not pressed, 1-pressed
    return !digitalRead(TM::BUTTON);
}

void Time_o_mat_class::soundTone(float freq) {
    ledcAttachPin(TM::BUZZER, TM::BUZZER_CHANNEL);
    ledcWriteTone(TM::BUZZER_CHANNEL, freq);
}
void Time_o_mat_class::soundEnd() {
    ledcDetachPin(TM::BUZZER);
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
