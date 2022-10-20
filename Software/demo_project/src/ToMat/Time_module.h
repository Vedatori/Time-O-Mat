#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "sntp.h"
#include "time.h"
#include "Preferences.h"

enum TimeSource {
	TS_Internet,
	TS_RTC,
 	TS_Manual
};




const char ntpServer1[] = "pool.ntp.org";
const char ntpServer2[] = "time.nist.gov";

//const char time_zone[] = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

class Time_module {
    time_t epochTime = 0; //Epoch starting on 1. January 1970
	int zoneOffset = 0; //seconds
	int daylightOffset = 0; //seconds
	bool offline = false;
	TimeSource timeSource = TS_RTC;
	uint32_t rtcUpdatePeriod = 200; //ms
	Preferences preferences;
public:
    void begin();

	bool updateNtp();
	bool updateRtc(bool forced = false);

    tm getLocalTime();
	tm getGmtTime();
	time_t getEpoch();
	String getLocalTimeStamp();
	String getGmtTimeStamp();
	
	void setTimeZone(int zoneOffset_sec, int daylightOffset_sec, bool saveToPreferences);
	int getTimeZoneOffset();
	int getDaylightOffset();

	void setOfflineMode(bool isOffline, bool saveToPreferences);
	bool isOffline();
	bool setOfflineLocalTime(tm newTime);

	

    TimeSource getTimeSource();
    String getClockText();
};

#endif // _TIME_MODULE_