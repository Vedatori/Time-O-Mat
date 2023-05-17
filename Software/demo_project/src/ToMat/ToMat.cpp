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
        ToMat.time.updateRTC();
        delay(20);
    }
}

void TM::refreshTaskSlow(void * parameter) {
    for(;;) {
        ToMat.power.update();
        ToMat.display.setCurrentLimit(ToMat.power.getLimitA() - TM::idleCurrent);
        ToMat.updateTemperature();

        static uint32_t wifiUpdateTime = 0;
        static uint32_t internetUpdateTime = 0;
        static uint32_t softApDisableTime = 0;
        static bool softApEnabled = true;
        if((millis() - wifiUpdateTime) > TM::WIFI_UPDATE_PERIOD || wifiUpdateTime == 0) {
            if(!WiFi.isConnected()) {
                if(!softApEnabled) {
                    softApEnable();
                    softApEnabled = true;
                }
                connectWifiAsClient();
                internetUpdateTime = 0;
            }
        }
		if((millis() - internetUpdateTime) > TM::INTERNET_UPDATE_PERIOD || internetUpdateTime == 0) {
			ToMat.checkInternetConnected();
            if(ToMat.getInternetConnected()) {
                internetUpdateTime = millis();
                if(softApEnabled && softApDisableTime == 0) {
                    softApDisableTime = millis();
                }
            }
            else if(ToMat.getWifiCaptStarted() && !softApEnabled) {
                softApEnable();
                softApEnabled = true;
            }
		}
        if(ToMat.getInternetConnected()) {
            ToMat.time.updateNTP();
            ToMat.weather.updateBothWF();
        }
        if(softApDisableTime != 0 && (millis() - softApDisableTime) > TM::SOFT_AP_DISABLE_TIMEOUT) {
            softApDisable();
            softApEnabled = false;
            softApDisableTime = 0;
        }
        delay(1000);
    }
}

void ToMat_class::begin() {
    beginCalled = true;


    power.begin(TM::CC_PIN[0], TM::CC_PIN[1]);
    illumination.update();
    display.begin();
    display.setCurrentLimit(ToMat.power.getLimitA() - TM::idleCurrent);
    time.begin(1000 * 60 * 15);
    touchBar.begin();
    piezo.begin(TM::BUZZER_CHANNEL, TM::BUZZER_PIN);

	weather.init(1000 * 60 * 15);
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

float ToMat_class::autoBrightnessFront(float illumination) {
    float brightness = 0.0;
    if(illumination > 0.7) {
        brightness = (illumination - 0.7) / 0.3 * 0.8 + 0.2;
    }
    else if(illumination > 0.5) {
        brightness = (illumination - 0.5) / 0.2 * 0.15 + 0.05;
    }
    else if(illumination > 0.2) {
        brightness = (illumination - 0.2) / 0.3 * 0.046 + 0.004;
    }
    else {
        brightness = 0.004;
    }
    return brightness;
}
float ToMat_class::autoBrightnessBack(float illumination) {
    float brightness = 0.0;
    if(illumination > 0.7) {
        brightness = 0.0;
    }
    else if(illumination > 0.5) {
        brightness = -(illumination - 0.5) / 0.2 * 0.1 + 0.1;
    }
    else if(illumination > 0.2) {
        brightness = (illumination - 0.2) / 0.3 * 0.1;
    }
    else {
        brightness = 0.0;
    }
    return brightness;
}

void ToMat_class::printDiagnostics() {
    for(int i = 0; i <= 2; ++i) {
        printf("btn%d: %d ", i, buttonRead(i));
    }
    
    printf("touchDigit: ");
    for(int i = 0; i <= 7; ++i) {
        printf("%d", touchBar.getPressed(i));
    }

    printf(" power: %s %.1fA ", power.getVoltagesText().c_str(), power.getLimitA());
    printf("illum: %s", illumination.getIlluminationText().c_str());

    //printf("priority: %d ", uxTaskPriorityGet(NULL));

    printf("temp: %f ", temperature);

    String timeDisp = ToMat.time.getClockText();
    printf("time: %s ", timeDisp.c_str());

    printf("weather: %s \n", ToMat.weather.getWeather().getWeatherString().c_str());

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

void ToMat_class::commandSend(String type, String text) {
    commandSendCaptain(type, text);
}

void ToMat_class::commandDisp(String text) {
    commandSend("commandDisp", text);
}

ToMat_class ToMat;