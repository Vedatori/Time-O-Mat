#include "melody.h"

uint8_t Melody::noteToNotePosition(String noteIn){
	if(noteIn.length()<2 || noteIn.length()>3){
		return 0;
	}

	char note = ' ';
	bool modifier = false;
	uint8_t number = 0;

	for(int i = 0; i<noteIn.length(); i++){
		char thisNote = tolower(noteIn[i]);

		if(thisNote=='r'){ //REST
			return 0;
		}

		if(thisNote=='#' || thisNote=='s'){ //MODIFIER
			modifier = true;
			continue;
		}
		if(thisNote>='a' && thisNote<='h'){ //NOTE
			note = thisNote;
			if(note == 'h'){
				note = 'b';
			}
			
			continue;
		}
		if(thisNote>=0 && thisNote<='9'){  //OCTAVE
			number = thisNote - '0';
			continue;
		}
		
	}

	if(note == ' '){
		return 0;
	}

	uint8_t temp = 0;

	switch (note)
	{
	case 'b':
		temp += 2;
	case 'a':
		temp += 2;
	case 'g':
		temp += 2;
	case 'f':
		temp += 1;
	case 'e':
		temp += 2;
	case 'd':
		temp += 2;
	case 'c':
		temp += 1;
	default:
		break;
	} 

	return ( temp + number*12 + ((modifier)? 1 : 0) - 11);
}
String Melody::notePositionToNote(uint8_t note){
	if(note==0){
		return "R";
	}
	note = note + 11;

	uint8_t number = (note-1)/12;

	switch (note%12)
	{
	
	case 0:
		return "B"+String(number)+"";
		break;
	case 1:
		return "C"+String(number)+"";
		break;
	case 2:
		return "C"+String(number)+"#";
		break;
	case 3:
		return "D"+String(number)+"";
		break;
	case 4:
		return "D"+String(number)+"#";
		break;
	case 5:
		return "E"+String(number)+"";
		break;
	case 6:
		return "F"+String(number)+"";
		break;
	case 7:
		return "F"+String(number)+"#";
		break;
	case 8:
		return "G"+String(number)+"";
		break;
	case 9:
		return "G"+String(number)+"#";
		break;
	case 10:
		return "A"+String(number)+"";
		break;
	case 11:
		return "A"+String(number)+"#";
		break;
	}
	return "R";
}

int Melody::calculateNoteFrequency(int note, uint16_t baseFreq, uint8_t baseNote){
    int hNotesFromBase = note-baseNote;

    double root12thof2 = 1.059463094359;

    bool inverse = 0>hNotesFromBase;
    hNotesFromBase = abs(hNotesFromBase);

    double power = pow(root12thof2, hNotesFromBase);

    double guess = (inverse)? baseFreq/power : baseFreq*power;

    return round(guess);
}


String Melody::getThisToken(String data, uint16_t &positionCounter, bool updateCounter){
	String token = "";
	uint16_t localCounter = positionCounter;
	while(data[localCounter]!=' '){
		token = token + data[localCounter];
		localCounter++;
		if (localCounter+1 >= data.length()){
			token = token + data[localCounter];
			break;
		}
	}
	localCounter++;

	if(updateCounter) positionCounter = localCounter;
	return token;

}

bool Melody::isMetaToken(String token){
	for(int i = 0; i < token.length(); i++){
		if(token[i]=='=') return true;
	}
	return false;
}

bool Melody::parseMetaToken(String token, String &name_return, int &value_return){
	token.toLowerCase();
	String name = "";
	String value = "";

	bool isValue = false;
	for(int i = 0; i<token.length(); i++){
		if(token[i]=='='){
			isValue = true;
			continue;
		}
		
		if(isValue){
			value = value + token[i];
		}else{
			name = name + token[i];
		}
	}

	if(name=="" || value==""){
		return false;
	}

	name_return = name;
	value_return = value.toInt();
	return true;
}

bool Melody::parseNoteToken(String token, bool useTuning, int &note_return, bool useTempo, int &time_return){
	token.toLowerCase();

	String note = "";
	String time = "";

	bool isTime = false;
	for(int i = 0; i < token.length(); i++){
		if(token[i]=='/'){
			isTime = true;
			continue;
		}

		if(isTime){
			time = time + token[i];
		}else{
			note = note + token[i];
		}
		
	}

	if(!isTime){
		note_return = 0;
		return false;
	}

	if(useTuning){
		note_return = noteToNotePosition(note);
	}else{
		note_return = note.toInt();
	}

	if(useTempo){
		String timeNoMod = "";
		bool modifier = false;
		for(int i = 0; i<time.length(); i++){
			if(time[i]=='.'||time[i]=='*'){
				modifier=true;
				continue;
			}
			if(time[i]>='0'&&time[i]<='9'){
				timeNoMod = timeNoMod + time[i];
			}
			
		}
		time_return = ((modifier)? -timeNoMod.toInt() : timeNoMod.toInt());
	}else{
		time_return = time.toInt();
	}
	return true;
}

Melody::Melody(String melody){
	uint16_t c = 0;
	uint16_t prevC = 0;
	while(c<melody.length()){
		String token = getThisToken(melody, c);
		if(token=="" || !isMetaToken(token)){
			break;
		}
		String name = "";
		int value = 0;

		if(!Melody::parseMetaToken(token, name, value)){Serial.println("Melody: Invalid parameter: "+token); break;}
		if(!setParameter(name, value)){Serial.println("Melody: Invalid parameter: "+token); break;}
		prevC = c;
	}

	data = melody.substring(prevC);
}

Melody::Melody(int * melody, int size, int tempo){
	String out = "TEMPO="+String(tempo)+" USECUTOFF=1 CUTOFFPERCENT=10";
	for(int i = 0; i<size; i=i+2){
		out=out+" "+notePositionToNote(melody[i])+"/"+String(abs(melody[i+1]))+((melody[i+1]<0)? ("."):(""));
	}
	data = out;
}

bool Melody::setParameter(String name, int value){
		if(name=="tempo"){
			tempo = value;
		}else if(name=="usetempo"){
			useTempo = value;
		}else if(name=="usetuning"){
			useTuning = value;
		}else if(name=="tuningbasefreq"){
			tuningBaseFreq = value;
		}else if(name=="tuningbasenoteposition"){
			tuningBaseNotePosition = value;
		}else if(name=="usecutoff"){
			useCutoff = value;
		}else if(name=="cutoffpercent"){
			cutoffPercent = value;
		}else{
			return false;
		}
		return true;
}

String Melody::toString(){
	String out = 
			String("useTuning=")+ 				String((useTuning)? "1" : "0") + 
			String("tuningBaseFreq=")+			String(tuningBaseFreq)+
			String("tuningBaseNotePosition=")+	String(tuningBaseNotePosition)+
			String("useTempo=")+				String((useTempo)? "1" : "0")+
			String("tempo=")+					String(tempo)+
			String("useCutoff=")+				String((useCutoff)? "1" : "0")+
			String("cutoffPercent=")+			String(cutoffPercent)+
			data;
	return out;
}



