#pragma once
#include <vector>
#include <Arduino.h>
//format:
/*
TEMPO=180 tempo=180 useTempo=1
(tempo and tuning)	b1/16 a4/1 c2#/4 			(note)/(beat fraction)
(tempo only)		1000/4 4000/2 				(frequency)/(beat fraction)
(tuning only)		b1/1000 a4#/400				(note)/(duration in ms)
(none)				1000/2000					(frequency)/(duration in ms)

*/


//notePosition: 
/*
	( (letter C=0, D=1, E=2, F=3, G=4, A=5, B/H=6) + (number)*7 )*2 + (modifier none=0 #=1) - 11
	REST - 0
	B0 - 1
	B0# - 2
	C1 - 3
	C1# - 4
	D1 - 5
	D1# - 6
	...
	B8# - 114
*/

class Melody {
public:
	bool useTuning = true;
	uint16_t tuningBaseFreq = 440;
	int16_t tuningBaseNotePosition = 47; //A4

	bool useTempo = true;
	uint16_t tempo = 120;

	bool useCutoff = true;
	uint8_t cutoffPercent = 10;

	String data = "";

	String toString();

	Melody(String melody);
	Melody(int * melody, int size, int tempo);

	bool setParameter(String name, int value);

	static uint8_t noteToNotePosition(String note);
	static String notePositionToNote(uint8_t note);
	static String getThisToken(String data, uint16_t &startOfToken, bool updateCounter = true);
	static bool isMetaToken(String token);
	static bool parseMetaToken(String token, String &name_return, int &value_return);
	static bool parseNoteToken(String token, bool useTuning, int &note_return, bool useTempo, int &time_return);
	static int calculateNoteFrequency(int note, uint16_t baseFreq, uint8_t baseNote);

	Melody(){}
};