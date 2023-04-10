#ifndef _TIME_MODULE_
#define _TIME_MODULE_

#include "Arduino.h"
#include "sntp.h"
#include "time.h"

const char ntpServer1[] = "pool.ntp.org";
const char ntpServer2[] = "time.nist.gov";
const int minUpdatePeriodNTP = 1000 * 60 * 5;   // [ms]

// Default time zone for Europe/Prague including daylight adjustment rules
// Other time zones available at https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
const String defaultTimeZone = "CET-1CEST,M3.5.0,M10.5.0/3";

enum TimeSource {
    TimeSource_internet,
    TimeSource_offline,
    TimeSource_manual
};

class Time_module {
    struct tm time;
	const uint32_t updatePeriodRTC = 500;           // [ms]
    bool updateNowNTP = false;                      // 0-wait for next scheduled NTP update period, 1-update in next updateNTP()
    uint32_t updatePeriodNTP = minUpdatePeriodNTP;  // [ms]
    TimeSource timeSource = TimeSource_internet;
    String timeZone = defaultTimeZone;
public:
    void begin(int newUpdatePeriodNTP);
    void setTimeZone(String timeZone);
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