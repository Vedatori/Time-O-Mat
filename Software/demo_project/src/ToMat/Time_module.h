#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "sntp.h"
#include "time.h"

enum TimeSource {
    TimeInternet,
    TimeRTC,
    TimeManual
};

const char ntpServer1[] = "pool.ntp.org";
const char ntpServer2[] = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

//const char time_zone[] = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

class Time_module {
    struct tm time;
	const uint32_t rtcGetTimeDelay = 300;
public:
    void begin();
	bool updateTime();
    struct tm getTime();
    TimeSource getTimeSource();
    String getClockText();
};

#endif // _TIME_MODULE_