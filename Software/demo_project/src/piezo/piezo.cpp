#include "piezo.h"

bool Piezo::begin(uint8_t channel, int pin){
    pChannel = channel;
    pPin = pin;
	pinMode(pPin,OUTPUT);
    return ledcSetup(pChannel, 1000, 10); //returns 0 if failed (false), frequency if ok (true)
    
}

uint8_t Piezo::getState(){
    return pState;
}

void Piezo::tone(uint16_t freq){
    pChangeState(1);
    pTone(freq);
}

void Piezo::stop(){
    pChangeState(0);
}

void Piezo::pTone(uint16_t freq){
    ledcAttachPin(pPin, pChannel);
    ledcWriteTone(pChannel, freq);
}
void Piezo::pStop(){
    ledcDetachPin(pPin);
}

void Piezo::pChangeState(uint8_t state){
	pStop();
	pState = state;
	pDeleteUpdateTask(); 
	// Ensure propper pStop() and pState change when task is deleting itself
	// When task is deleting itself, the code stops here

	pState = state;
	pStop();
}

void Piezo::pCreateUpdateTask(){
	xTaskCreatePinnedToCore(Piezo::pUpdate, ("PiezoUpdate"+String(pChannel)).c_str(), 10000 , this, 1, &pTaskHandle, 1);
}

void Piezo::pDeleteUpdateTask(){
	if(pTaskHandle != NULL){
		// Ensure propper NULL when task is deleting itself
		TaskHandle_t t = pTaskHandle;
		pTaskHandle = NULL;
		vTaskDelete(t); // When task deletes itself, the code stops here
	}
}

void Piezo::pUpdate(void * params){
	Piezo * piezo = (Piezo *) params;
	for(;;){
		switch (piezo->pState)
		{
		case 2:
			piezo->pMLoop();
			break;
		default:
			piezo->pDeleteUpdateTask();
			break;
		
		}
		vTaskDelay(piezo->pDelay/portTICK_PERIOD_MS);
	}
}



void Piezo::playMelody(int * melody, uint16_t size, uint16_t tempo){
	playMelody(Melody(melody, size, tempo));
}
void Piezo::playMelody(String melody){
	playMelody(Melody(melody));
}
void Piezo::playMelody(Melody melody){
	pChangeState(2);
	dataCounter = 0;
	currentMelody = melody;
	preCutoff = true;
	pDelay = 0;

	pCreateUpdateTask();
}

void Piezo::pMLoop(){
	
	if(dataCounter>=currentMelody.data.length()){
		pChangeState(0);
	}

	if(!preCutoff){
		pStop();
		pDelay = pDelay*currentMelody.cutoffPercent/(100-currentMelody.cutoffPercent);
		preCutoff = true;
		return;
	}
	pDelay = 0;

	String token = Melody::getThisToken(currentMelody.data, dataCounter);
	//Serial.print("Note: ");
	//Serial.println(token);
	if(token == ""){
		return;
	}
	if(Melody::isMetaToken(token)){ //METADATA
		String metaName = "";
		int metaValue = 0;
		if(!Melody::parseMetaToken(token, metaName, metaValue)) {return; }
		if(!currentMelody.setParameter(metaName,metaValue)){
			Serial.println("Melody: Invalid parameter: "+token);
		}
	}else{ //NOTEDATA

		int note = 0;
		int time = 0;
		if(!Melody::parseNoteToken(token, currentMelody.useTuning, note, currentMelody.useTempo, time)) {return;};

		if(currentMelody.useTempo && time!=0){
			pDelay = 60000*4 /(currentMelody.tempo)/abs(time) * ((time<0)? 1.5 : 1);
		}else{
			pDelay = time;
		}
		if(currentMelody.useCutoff){
			pDelay = pDelay*(100-currentMelody.cutoffPercent)/100;
			preCutoff = false;
		}

		if(note == 0){
			pStop();
			return;
		}

		if(currentMelody.useTuning){
			//Serial.println(Melody::calculateNoteFrequency(note, currentMelody.tuningBaseFreq, currentMelody.tuningBaseNotePosition));
			pTone(Melody::calculateNoteFrequency(note, currentMelody.tuningBaseFreq, currentMelody.tuningBaseNotePosition));
		}else{
			pTone(note);
		}


	}

}

Melody Piezo::getCurrentMelody(){
	return currentMelody;
}
