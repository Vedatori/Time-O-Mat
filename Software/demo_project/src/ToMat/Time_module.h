#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "sntp.h"
#include "time.h"

const char ntpServer1[] = "pool.ntp.org";
const char ntpServer2[] = "time.nist.gov";
const char time_zone[] = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Prague including daylight adjustment rules

enum TimeSource {
    TimeSource_internet,
    TimeSource_offline,
    TimeSource_manual
};

class Time_module {
    struct tm time;
	const uint32_t updatePeriodRTC = 500;   // [ms]
    const uint32_t updatePeriodNTP = 1000;   // [ms]
    TimeSource timeSource = TimeSource_internet;
public:
    void begin();
	void updateRTC();
    void updateNTP();
    TimeSource getTimeSource();
    struct tm getTime();
    String getClockText();
    void setTime(struct tm newTime);
    void setTime(int hours, int minutes);
    void shiftMinutes(int minutes);
};

#endif // _TIME_MODULE_