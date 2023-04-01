#include "Time_module.h"
#include <ErriezDS1302.h>
#include "Preferences.h"

#define RTC_CLK_PIN 25
#define RTC_IO_PIN 23
#define RTC_CE_PIN 13

ErriezDS1302 rtc(RTC_CLK_PIN, RTC_IO_PIN, RTC_CE_PIN);
Preferences timePreferences;

void Time_module::begin(int newUpdatePeriodNTP) {
    configTime(0, 0, ntpServer1, ntpServer2);

	timePreferences.begin("timeMod", false);
	timeZone = timePreferences.getString("timeZone", defaultTimeZone);
    timePreferences.end();
	setTimeZone(timeZone);

	rtc.begin();
	rtc.clockEnable();

	updatePeriodNTP = (newUpdatePeriodNTP > minUpdatePeriodNTP) ? newUpdatePeriodNTP : minUpdatePeriodNTP;
}

void Time_module::setTimeZone(String newTimeZone) {
	setenv("TZ", newTimeZone.c_str(), 1);
	tzset();
	updateNowNTP = true;
	timePreferences.begin("timeMod", false);
	timePreferences.putString("timeZone", newTimeZone);
    timePreferences.end();
}

void Time_module::updateNTP() {
	if(timeSource == TimeSource_manual) {
		return;
	}

	static uint32_t prevUpdateNTP = 0;
	if(prevUpdateNTP == 0 || ((millis() - prevUpdateNTP) > updatePeriodNTP) || updateNowNTP) {
		prevUpdateNTP = millis();
		updateNowNTP = false;
		struct tm timeNTP;
		if(getLocalTime(&timeNTP)) {
			timeSource = TimeSource_internet;
			time = timeNTP;
			if(!rtc.write(&timeNTP)) {
				printf("RTC time write failed!\n");
			}
		}	
		else {
			timeSource = TimeSource_offline;
			printf("NTP time not available!\n");
		}
	}
}

void Time_module::updateRTC() {
	static uint32_t prevUpdateRTC = 0;
	if(prevUpdateRTC == 0 || (millis() - prevUpdateRTC) > updatePeriodRTC) {
		prevUpdateRTC = millis();
		struct tm timeRTC;
		if(rtc.read(&timeRTC)) {
			time = timeRTC;
		}
		else {
			printf("RTC time read failed!\n");
		}
	}
}

TimeSource Time_module::getTimeSource() {
	return timeSource;
}

struct tm Time_module::getTime() {
    return time;
}

String Time_module::getClockText() {
    char clockText[4];
    getTime();
    sprintf(clockText, "%02d%02d", time.tm_hour, time.tm_min);
    return String(clockText);
}

void Time_module::setTime(struct tm newTime) {
	timeSource = TimeSource_manual;
	if(!rtc.write(&newTime)) {
		printf("RTC time write failed!\n");
	}
}

void Time_module::setTime(int hours, int minutes) {
	struct tm newTime;
	newTime.tm_hour = hours;
	newTime.tm_min = minutes;
	setTime(newTime);
}

void Time_module::shiftMinutes(int minutes) {
	int newHours = time.tm_hour;
	int newMinutes = time.tm_min + minutes;

	while(newMinutes < 0) {
		newHours -= 1;
		newMinutes += 60;
	}
	while(newMinutes > 59) {
		newHours += 1;
		newMinutes -= 60;
	}
	while(newHours < 0) {
		newHours += 24;
	}
	while(newHours > 23) {
		newHours -= 24;
	}

	struct tm newTime = time;
	newTime.tm_hour = newHours;
	newTime.tm_min = newMinutes;
	setTime(newTime);
}