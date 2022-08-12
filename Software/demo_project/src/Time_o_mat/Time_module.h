#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "sntp.h"
#include "time.h"

extern const char* ntpServer1;
extern const char* ntpServer2;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;

//const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

class Time_module {
    struct tm time;
public:
    void begin();
    struct tm getTime();
    String getClockText();
};

#endif // _TIME_MODULE_