#include "Time_module.h"
#include <ErriezDS1302.h>

#define RTC_CLK_PIN 25
#define RTC_IO_PIN 23
#define RTC_CE_PIN 13

ErriezDS1302 rtc(RTC_CLK_PIN, RTC_IO_PIN, RTC_CE_PIN);

time_t timegm(register struct tm * t);

// --- Begin ---
void Time_module::begin(){
	preferences.begin("TimeModule");

	//preferences.clear();

	if(preferences.isKey("zoneOffset")){
		zoneOffset = preferences.getInt("zoneOffset", zoneOffset);
	}
	if(preferences.isKey("daylightOffset")){
		daylightOffset = preferences.getInt("daylightOffset", daylightOffset);
	}
	if(preferences.isKey("offline")){
		offline = preferences.getBool("offline", offline);
	}
	
	
	

	configTime(zoneOffset, daylightOffset, ntpServer1, ntpServer2);
	rtc.begin();
	rtc.clockEnable();

	if(offline){
		timeSource = TS_Manual;
	}
}


// --- Update ---
bool Time_module::updateNtp(){
	if(offline){
		return true;
	}

	time_t newEpoch;
	uint32_t start = millis();
	tm info;
	bool ok = false;
    while((millis()-start) <= 500) {
        time(&newEpoch);
        localtime_r(&newEpoch, &info);
        if(info.tm_year > (2021 - 1900)){
            ok = true;
			break;
        }
        delay(10);
    }
	if(!ok){
		printf("updateNtp: Failed to synchronize with NTP!\n");
		timeSource = TS_RTC;
		return false;
	}
	timeSource = TS_Internet;
	epochTime = newEpoch;
	rtc.clockEnable(false);
	if(!rtc.write(gmtime(&newEpoch))){
		printf("updateNtp: Failed to write to RTC!\n");
		return false;
	}
	rtc.clockEnable(true);
	//printf("Got ntp time: %i", newEpoch);
	return true;
}
bool Time_module::updateRtc(bool forced){
	static uint32_t lastUpdate = 0;
	if((millis() - lastUpdate < rtcUpdatePeriod) && !(forced || timeSource == TS_RTC)){
		return true;
	}
	tm newTime;
	rtc.read(&newTime);
	time_t newEpoch = timegm(&newTime);
	if(!newEpoch){
		printf("updateRtc: RTC read failed!\n");
		return false;
	}
	//printf("Got rtc time: %i", newEpoch);
	epochTime = newEpoch;
	lastUpdate = millis();
	return true;
}


// --- Time ---
tm Time_module::getLocalTime(){
	tm returnTime;
	localtime_r(&epochTime, &returnTime);
	return returnTime;
}
tm Time_module::getGmtTime(){
	tm returnTime;
	gmtime_r(&epochTime, &returnTime);
	return returnTime;
}
time_t Time_module::getEpoch(){
	return epochTime;
}
String Time_module::getLocalTimeStamp(){
	char buff[26];
	asctime_r(localtime(&epochTime), buff);
	return String(buff);
}
String Time_module::getGmtTimeStamp(){
	char buff[26];
	asctime_r(gmtime(&epochTime), buff);
	return String(buff);
}

// --- Time zone config ---
void Time_module::setTimeZone(int zoneOffset_sec, int daylightOffset_sec, bool saveToPreferences){
	zoneOffset = zoneOffset_sec;
	daylightOffset = daylightOffset_sec;
	if(saveToPreferences){
		preferences.putInt("zoneOffset", zoneOffset);
		preferences.putInt("daylightOffset", daylightOffset);
	}

	int zoneOffsetNeg = -zoneOffset;


    char cst[17] = {0};
    char cdt[17] = "DST";
    char tz[33] = {0};

    if(zoneOffsetNeg % 3600){
        sprintf(cst, "UTC%ld:%02u:%02u", zoneOffsetNeg / 3600, abs((zoneOffsetNeg % 3600) / 60), abs(zoneOffsetNeg % 60));
    } else {
        sprintf(cst, "UTC%ld", zoneOffsetNeg / 3600);
    }
    if(daylightOffset != 3600){
        long tz_dst = zoneOffsetNeg - daylightOffset;
        if(tz_dst % 3600){
            sprintf(cdt, "DST%ld:%02u:%02u", tz_dst / 3600, abs((tz_dst % 3600) / 60), abs(tz_dst % 60));
        } else {
            sprintf(cdt, "DST%ld", tz_dst / 3600);
        }
    }
    sprintf(tz, "%s%s", cst, cdt);
    setenv("TZ", tz, 1);
    tzset();
}
int Time_module::getTimeZoneOffset(){
	return zoneOffset;
}
int Time_module::getDaylightOffset(){
	return daylightOffset;
}


// --- Offline mode ---
void Time_module::setOfflineMode(bool isOffline, bool saveToPreferences){
	offline = isOffline;
	if(saveToPreferences){
		preferences.putBool("offline", offline);
	}
	if(offline){
		timeSource = TS_Manual;
	}
}
bool Time_module::isOffline(){
	return offline;
}
bool Time_module::setOfflineLocalTime(tm newTime){
	if(!offline){
		printf("setOfflineLocalTime: Offline mode not enabled!\n");
		return false;
	}
	time_t _newTime = mktime(&newTime);
	tm _newTimeGmt;
	gmtime_r(&_newTime, &_newTimeGmt);
	if(!rtc.write(&_newTimeGmt)){
		printf("setOfflineLocalTime: RTC Write failed!\n");
		return false;
	}
	epochTime = _newTime;
	return true;
}


// --- Utility ---
TimeSource Time_module::getTimeSource(){
	return timeSource;
}
String Time_module::getClockText(){
	char clockText[4];
    tm currentTime = getLocalTime();
    sprintf(clockText, "%02d%02d", currentTime.tm_hour, currentTime.tm_min);
    return String(clockText);
}

/*
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
*/

time_t timegm(register struct tm * t)
/* struct tm to seconds since Unix epoch */
{
    register long year;
    register time_t result;
#define MONTHSPERYEAR   12      /* months per calendar year */
    static const int cumdays[MONTHSPERYEAR] =
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

    /*@ +matchanyintegral @*/
    year = 1900 + t->tm_year + t->tm_mon / MONTHSPERYEAR;
    result = (year - 1970) * 365 + cumdays[t->tm_mon % MONTHSPERYEAR];
    result += (year - 1968) / 4;
    result -= (year - 1900) / 100;
    result += (year - 1600) / 400;
    if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0) &&
        (t->tm_mon % MONTHSPERYEAR) < 2)
        result--;
    result += t->tm_mday - 1;
    result *= 24;
    result += t->tm_hour;
    result *= 60;
    result += t->tm_min;
    result *= 60;
    result += t->tm_sec;
    if (t->tm_isdst == 1)
        result -= 3600;
    /*@ -matchanyintegral @*/
    return (result);
}