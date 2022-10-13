#include "Time_module.h"
#include <ErriezDS1302.h>

#define RTC_CLK_PIN 25
#define RTC_IO_PIN 23
#define RTC_CE_PIN 13

ErriezDS1302 rtc(RTC_CLK_PIN, RTC_IO_PIN, RTC_CE_PIN);

void Time_module::begin() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
	rtc.begin();
	rtc.clockEnable();
}

bool Time_module::updateTime() {
	tm ntpTime;
	if(!getLocalTime(&ntpTime)) {
        printf("NTP time not available!\n");
		return false;
    }
	if(!rtc.write(&ntpTime)) {
		printf("RTC time write failed!\n");
		return false;
	}
	return true;
}

struct tm Time_module::getTime() {
	static uint32_t prevGetTime = 0;
	if(prevGetTime!=0 && millis()-prevGetTime<rtcGetTimeDelay) {
		return time;
	}
	prevGetTime = millis();

    if(!rtc.read(&time)){
		printf("RTC time read failed!");
	}
    return time;
}

TimeSource Time_module::getTimeSource() {
	TimeSource source = TimeInternet;
	return source;
}

String Time_module::getClockText() {
    char clockText[4];
    getTime();
    sprintf(clockText, "%02d%02d", time.tm_hour, time.tm_min);
    return String(clockText);
}