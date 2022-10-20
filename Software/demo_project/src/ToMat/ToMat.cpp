#include "ToMat.h"

#include "OneWire.h"
#include "DallasTemperature.h"
#include "SPIFFS.h"

OneWire oneWire(TM::ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);
Melody themeMelodyFull(
	"TEMPO=140 " 
	"F5#/8 H4/8 E5#/8 H4/8 F5#/8 H4/8 E5#/8 H4/8 F5#/8 C5#/8 E5#/8 C5#/8 F5#/8 C5#/8 E5#/8 C5#/8 F5#/8 A4#/8 E5#/8 A4#/8 F5#/8 A4#/8 E5#/8 A4#/8 F5#/8 A4#/8 E5#/8 A4#/8 D5#/8 A4#/8 E5#/8 A4#/8 F5#/8 H4/8 E5#/8 H4/8 F5#/8 H4/8 E5#/8 H4/8 "
    "F5#/8 C5#/8 E5#/8 C5#/8 F5#/8 C5#/8 E5#/8 C5#/8 F5#/8 A4#/8 E5#/8 A4#/8 F5#/8 A4#/8 E5#/8 A4#/8 F5#/8 A4#/8 E5#/8 A4#/8 D5#/8 F4#/8 C4#/8 F4#/8 E4#/4 E4#/4 E4#/4 E4#/8 D4#/8 "
    "E4#/8 F4#/8 E4#/8 D4#/8* D4#/8 F4#/8  E4#/4 E4#/4 E4#/8 F4#/8 E4#/8 D4#/8 D4#/2 R/4 A3#/8 D4#/8 "
    "C4#/4 C4#/4 C4#/4 C4#/8 H3/8 C4#/8 D4#/8 C4#/8 C4#/2 C4#/8 C4#/8 C4#/4 C4#/8 D4#/4 A3#/8 A3#/8 A3#/2 R/4 D4#/8 F4#/8 "
    "E4#/4 E4#/4 E4#/4 E4#/8 D4#/8 E4#/8 F4#/8 E4#/8 D4#/4* D4#/8 F4#/8 E4#/4 E4#/4 E4#/8 F4#/8 E4#/8 D4#/8 D4#/2 R/4 A3#/8 D4#/8 "
    "C4#/4 C4#/4 C4#/4 C4#/8 H3/8 C4#/8 D4#/8 C4#/8 C4#/2 C4#/8 C4#/8 C4#/8 C4#/8 C4#/8 D4#/4 A3#/8 A3#/8 C4#/2 R/2 "
    "F5#/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/2 F5#/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 G5#/8* F5#/8 F5#/8 "
    "F5#/8 E5#/8 D5#/8 R/8 F5#/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 F5#/8 R/8 F5#/8 F5#/4 E5#/8 D5#/8 E5#/8 E5#/8 "
    //REPETICE - HLAVNI MELODIE
    "R/2 R/8 D5#/8 E5#/8 F5#/8 F5#/8 E5#/8 D5#/8 R/4 G5#/4 G5#/4 F5#/8 E5#/8 R/8 D5#/8 R/8 D5#/4 R/8 D5#/4* R/8 R/4 R/4 R/4* D5#/8 E5#/8 F5#/8 F5#/8 F5#/4 F5#/4 F5#/4 F5#/4 E5#4 E5#/4 D5#/4 D5#/4 "
    "R/2 R/8 D5#/8 E5#/8 F5#/8 F5#/8 E5#/8 D5#/8 R/4 G5#/4 G5#/4 F5#/8 E5#/8 R/8 D5#/8 R/8 D5#/4 R/8 D5#/4* R/8 R/4 R/4 R/4* D5#/8 E5#/8 F5#/8 F5#/8 F5#/4 F5#/4 F5#/4 F5#/4 E5#4 E5#/4 D5#/4 D5#/4 "
);
Melody themeMelody(
	"TEMPO=140 " 
	"R/2 R/8 D5#/8 E5#/8 F5#/8 F5#/8 E5#/8 D5#/8 R/4 G5#/4 G5#/4 F5#/8 E5#/8 R/8 D5#/8 R/8 D5#/4 R/8 D5#/4* R/8 R/4 R/4 R/4* D5#/8 E5#/8 F5#/8 F5#/8 F5#/4 F5#/4 F5#/4 F5#/4 E5#4 E5#/4 D5#/4 D5#/4 "
    "R/2 R/8 D5#/8 E5#/8 F5#/8 F5#/8 E5#/8 D5#/8 R/4 G5#/4 G5#/4 F5#/8 E5#/8 R/8 D5#/8 R/8 D5#/4 R/8 D5#/4* R/8 R/4 R/4 R/4* D5#/8 E5#/8 F5#/8 F5#/8 F5#/4 F5#/4 F5#/4 F5#/4 E5#4 E5#/4 D5#/4 D5#/4 "
);

void TM::refreshTaskQuick(void * parameter) {
    for(;;) {
        ToMat.display.update();
        ToMat.touchBar.update();
        ToMat.illumination.update();
		ToMat.time.updateRtc();
        delay(20);
    }
}

static bool forceUpdateNtp = false;
void TM::refreshTaskSlow(void * parameter) {
    for(;;) {
        ToMat.power.update();
        ToMat.updateTemperature();

        static uint32_t internetUpdateTime = 0;
        static uint32_t softApDisableTime = 0;
        static bool softApEnabled = true;

		
		if(forceUpdateNtp){
			forceUpdateNtp = !ToMat.time.updateNtp();
		}

		if((millis() - internetUpdateTime) > TM::INTERNET_UPDATE_PERIOD || internetUpdateTime == 0) {
			ToMat.checkInternetConnected();

			forceUpdateNtp = ToMat.getInternetConnected();

            if(ToMat.getInternetConnected()) {
			    ToMat.weather.updateBothWF();


				

                internetUpdateTime = millis();
                if(softApEnabled) {
                    softApDisableTime = millis();
                }
            }
            else if(ToMat.getWifiCaptStarted() && !softApEnabled) {
                softApEnable();
            }
		}
        if(softApDisableTime != 0 && (millis() - softApDisableTime) > TM::SOFT_AP_DISABLE_TIMEOUT) {
            softApDisableTime = 0;
            softApEnabled = false;
            softApDisable();
        }
        delay(1000);
    }
}

void ToMat_class::begin() {
    beginCalled = true;

    power.update();
    illumination.update();
    display.begin();

	time.setTimeZone(3600, 3600, false); //Set default time zone
    time.begin();

    touchBar.begin();
    piezo.begin(TM::BUZZER_CHANNEL, TM::BUZZER_PIN);

	weather.init();
	weather.setKey(TM::WEATHER_API_KEY, WEATHERAPI::WA_DEFAULT);
	weather.setPosition(50.36, 15.79, "Choteborky", WEATHERAPI::WA_DEFAULT);

    for(int i = 0; i < 3; ++i) {
        pinMode(TM::BUTTON_PIN[i], INPUT_PULLUP);
    }

    sensors.begin();
    
    xTaskCreatePinnedToCore(TM::refreshTaskQuick, "refreshTaskQuick", 10000 , NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(TM::refreshTaskSlow, "refreshTaskSlow", 10000 , NULL, 0, NULL, 0);

    display.setUpdateActive(true);
}

bool ToMat_class::buttonRead(int buttonID) {
    if(buttonID < 0 || buttonID > 2) {
        printf("Invalid button ID: %d\n", buttonID);
        return 0;
    }
    return !digitalRead(TM::BUTTON_PIN[buttonID]);  // 1 = pressed
}

void ToMat_class::updateTemperature() {
    sensors.requestTemperatures();
    float newTemp = sensors.getTempCByIndex(0);
    if(newTemp > -100.0) {
        // Filter out nonsense measurements
        temperature = newTemp;
    }
}

float ToMat_class::getTemperature() {
    return temperature;
}

void ToMat_class::printDiagnostics() {
    for(int i = 0; i <= 2; ++i) {
        printf("btn%d: %d ", i, buttonRead(i));
    }
    
    printf("touchDigit: ");
    for(int i = 0; i <= 7; ++i) {
        printf("%d", touchBar.getPressed(i));
    }

    printf(" %s", power.getVoltagesText().c_str());
    printf("%s", illumination.getIlluminationText().c_str());

    //printf("priority: %d ", uxTaskPriorityGet(NULL));

    String timeDisp = ToMat.time.getClockText();
    printf("time: %s ", timeDisp.c_str());

    printf("temp: %f \n", temperature);
}

void handleWeatherConfig(){
	String msg = "";
	if(webserver.hasArg("apiKey")){
		ToMat.weather.setKey(webserver.arg("apiKey"));
		msg = String("Api key set to: ") + ToMat.weather.getKey();
	}else if(webserver.hasArg("geoLocatorLatitude")){
		double latitude = webserver.arg("geoLocatorLatitude").toDouble();
		double longitude = webserver.arg("geoLocatorLongitude").toDouble();
		printf("%.10f %.10f",latitude, longitude);
		ToMat.weather.setPosition(latitude, longitude, "None");
		msg = String("Postion set to: ")+String(ToMat.weather.getPositionLatitude())+String(" ")+String(ToMat.weather.getPositionLongitude());
	}else{
		File f = SPIFFS.open("/weatherSetup.html", "r");
    	webserver.streamFile(f, "text/html");
		f.close();
		return;
	}
	String Page;
	Page += F("<html>\n\t<head>\n\t\t<meta charset=\"utf-8\">\n\t\t<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0\">\n\t\t<meta name=\"theme-color\" content=\"#404040\"/>\n\t\t<title>TrackJet</title>\n\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n\t\t<style>\n\t\t\tbody {\n\t\t\t\toverflow : hidden;\n\t\t\t}\n\t\t\t</style>\n\t</head>\n\t<body>\n");
	Page += F("<p><a href='/'><input type = 'button' value = 'Remote Control page'/></a></p>");
	Page += msg;
	Page +=	F("</body></html>");

	webserver.send(200, "text/html", Page);
}

void handleTimeSetup(){
	if(webserver.hasArg("zoneOffset")){

		ToMat.time.setTimeZone(webserver.arg("zoneOffset").toInt()*3600, webserver.arg("daylightOffset").toInt()*3600, true);
	}else if(webserver.hasArg("maunalTime")){
		ToMat.time.setOfflineMode(webserver.hasArg("offlineMode"), true);

		char buff[17];
		for(int i = 0; i < (sizeof(buff)/sizeof(buff[0])); i++){
			buff[i] = 0;
		}

		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		tm newTime;
		webserver.arg("maunalTime").toCharArray(buff, sizeof(buff)/sizeof(buff[0]));
		for(int i = 0; i < (sizeof(buff)/sizeof(buff[0])); i++){
			if(buff[i] == 0){
				break;
			}
			switch (i)
			{
			case 0:
				year += 1000*(buff[i]-'0');
				break;
			case 1:
				year += 100*(buff[i]-'0');
				break;
			case 2:
				year += 10*(buff[i]-'0');
				break;
			case 3:
				year += 1*(buff[i]-'0');
				break;
			case 4:
				break;
			case 5:
				month += 10*(buff[i]-'0');
				break;
			case 6:
				month += 1*(buff[i]-'0');
				break;
			case 7:
				break;
			case 8:
				day += 10*(buff[i]-'0');
				break;
			case 9:
				day += 1*(buff[i]-'0');
				break;
			case 10:
				break;
			case 11:
				hour += 10*(buff[i]-'0');
				break;
			case 12:
				hour += 1*(buff[i]-'0');
				break;
			case 13:
				break;
			case 14:
				minute += 10*(buff[i]-'0');
				break;
			case 15:
				minute += 1*(buff[i]-'0');
				break;
			
			default:
				break;
			}
			newTime.tm_hour = hour;
			newTime.tm_min = minute;
			newTime.tm_isdst = -1;
			newTime.tm_mon = month - 1;
			newTime.tm_sec = 0;
			newTime.tm_year = year - 1900;
			newTime.tm_mday = day;
		}
		time_t newEpoch = mktime(&newTime);
		localtime_r(&newEpoch, &newTime);
		//printf(asctime(&newTime));

		if(ToMat.time.isOffline()){
			ToMat.time.setOfflineLocalTime(newTime);
		}
		

		forceUpdateNtp = true;
	}



	String msg = "";
	msg += F("Local time: ");
	msg += ToMat.time.getLocalTimeStamp();
	msg += F("<br>Gmt time: ");
	msg += ToMat.time.getGmtTimeStamp();
	msg += F("<br>Time zone offset: ");
	msg += String(ToMat.time.getTimeZoneOffset()/3600);
	msg += F("<br>Daylight saving offset: ");
	msg += String(ToMat.time.getDaylightOffset()/3600);
	msg += F("<br>Is manual time enabled: ");
	msg += String((ToMat.time.isOffline())? "YES" : "NO");
	msg += F("<br>Time source: ");
	switch (ToMat.time.getTimeSource())
	{
	case TS_Internet:
		msg += String("Internet (NTP)");
		break;
	case TS_RTC:
		msg += String("RTC (NTP not available)");
		break;
	case TS_Manual:
		msg += String("Manual (RTC)");
		break;
	}

	File f = SPIFFS.open("/timeSetup.html", "r");
	String page = f.readString();
	page += msg;
	page += "</div></body></html>";


	webserver.send(200, "text/html", page);
	f.close();
}

void ToMat_class::startWiFiCaptain(String name, String password) {
    wifiCaptStarted = true;
    if(!beginCalled) {
        begin();
    }

    display.setText("----", red);
    display.update();
    display.setUpdateActive(false);

    String ssid_final = "ToMat-";
    if(name.isEmpty() || name == "<your_name>") {
        ssid_final += WiFi.macAddress();
    }
    else {
        ssid_final += name;
    }
    setApCredentials(ssid_final, password);
    wifiCaptInit();

	webserver.on("/weatherSetup", handleWeatherConfig);
	webserver.on("/timeSetup", handleTimeSetup);

    connectionEnabled = true;

    display.setText("    ", red);
    display.setUpdateActive(true);
    display.update();
}


bool ToMat_class::getWifiCaptStarted() {
    return wifiCaptStarted;
}

void ToMat_class::checkConnection() {
    if(!connectionEnabled) {
        return;
    }
    if(millis() > prevCommunicationTime + TM::communicationTimeout) {
        connectionActive = false;
    }
    else {
        connectionActive = true;
    }
}


void ToMat_class::checkInternetConnected() {
	if(!WiFi.isConnected()) {
		internetConnected = false;
	}
    else {
        internetConnected = 
            Ping.ping(IPAddress(8, 8, 8, 8), 1) ||
            Ping.ping("google.com", 1) ||
            Ping.ping("vedatori.com", 1);
    }
}

bool ToMat_class::getInternetConnected() {
    return internetConnected;
}

String ToMat_class::commandGet() {
    String command = String(commandGetCaptain());
    command.toLowerCase();
    return command;
}

String ToMat_class::commandGetIndexed(uint8_t index) {
    char commandBuffer[64];
    sprintf(commandBuffer, commandGetCaptain());
    const char delimiter[2] = " ";
    char *token;
    token = strtok((char *)commandBuffer, delimiter);
    for(uint8_t i = 0; i < index; ++i) {
        token = strtok(NULL, delimiter);
    }
    String command = String(token);
    command.toLowerCase();
    return command;
}

void ToMat_class::commandClear() {
    commandClearCaptain();
}

void ToMat_class::internCommandHandle() {
    static uint8_t counter = 0;
    if(counter < 20) {
        counter++;
        return;
    }
    else {
        counter = 0;
    }
    if(ToMat.commandGetIndexed(0) == "reset" || ToMat.commandGetIndexed(0) == "restart") {
        ESP.restart();
    }
    else if(ToMat.commandGet() == "encoder calibrate") {
        ToMat.commandClear();
    }
}

void ToMat_class::commandSend(String type, String text) {
    commandSendCaptain(type, text);
}

void ToMat_class::commandDisp(String text) {
    commandSend("commandDisp", text);
}

ToMat_class ToMat;