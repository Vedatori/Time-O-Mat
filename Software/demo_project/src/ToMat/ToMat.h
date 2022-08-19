#ifndef _TOMAT_
#define _TOMAT_

#include <Arduino.h>
#include "Preferences.h"

#include "Display_TM.h"
#include "Time_module.h"
#include "Touchbar_TM.h"
#include "USB_C_power_module.h"
#include "Illumination_module.h"
#include "WiFiCaptain.h"
#include <piezo/piezo.h>
#include <weather/weatherApi.h>
#include <ESP32Ping.h>

namespace TM {

const int BUTTON_PIN[3] = {18, 19, 21};
const uint8_t BUZZER_PIN = 17;
const uint8_t ONE_WIRE_PIN = 22;

const uint8_t BUZZER_CHANNEL = 3;

const char STORAGE_NAMESPACE[] = "Time_o_mat";
const uint16_t communicationTimeout = 1000;

const char WEATHER_API_KEY[] = "bde361c7c969906b9a9571a8f4a14c06";
const uint32_t INTERNET_UPDATE_PERIOD = 1000 * 60 * 15; // [ms]
const uint32_t SOFT_AP_DISABLE_TIMEOUT = 1000 * 60 * 5; // [ms]

void refreshTaskQuick(void * param);
void refreshTaskSlow(void * param);
}

class ToMat_class {
    bool beginCalled = false;
    bool connectionEnabled = false;
    bool connectionActive = false;
    uint32_t prevCommunicationTime = 0;
    bool internetConnected = false;
    bool wifiCaptStarted = false;

    float temperature = 0.0;

public:
    Display_TM display;
    Time_module time;
    TouchBar_TM touchBar;
    USB_C_power_module power;
    Illumination_module illumination;
    Piezo piezo;
	WeatherApi weather;
	

    void begin();
    bool buttonRead(int buttonID);
    void updateTemperature();
    float getTemperature();

    void printDiagnostics();

    void startWiFiCaptain(String name="", String password="");
    bool getWifiCaptStarted();
    void checkConnection();
    void checkInternetConnected();
	bool getInternetConnected();
    String commandGet();
    String commandGetIndexed(uint8_t index);
    void commandClear();
    void internCommandHandle();
    void commandSend(String type, String text);
    void commandDisp(String text);
};

extern ToMat_class ToMat;
extern Melody themeMelody;
extern Melody themeMelodyFull;

#endif // _TOMAT_