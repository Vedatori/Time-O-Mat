#pragma once
#include <Arduino.h>

#include "Melody.h"

class Piezo {
private:
	//Config
	uint8_t pChannel;
    int pPin;

	//Sound generation
    void pTone(uint16_t freq);
    void pStop();

	//State - Nepřiřazovat pState přímo, používat pChangeState
	void pChangeState(uint8_t state);
	uint8_t pState; //0 = no sound, 1 = manual tone, 2 = melody

	//Update task
	unsigned long pDelay;
	TaskHandle_t pTaskHandle = NULL;
	void pCreateUpdateTask();
	void pDeleteUpdateTask();
	static void pUpdate(void * params);

	//Melody
	void pMLoop();
	Melody currentMelody;
	uint16_t dataCounter = 0;
	bool preCutoff = true;


public:
	bool begin(uint8_t channel, int pin);

    uint8_t getState();
	
    void tone(uint16_t freq);
    void stop();

	void playMelody(int * melody, uint16_t size, uint16_t tempo);
    void playMelody(String melody);
	void playMelody(Melody melody);

	Melody getCurrentMelody();

	Piezo(){}
};