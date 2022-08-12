#include "Time_module.h"

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void Time_module::begin() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

struct tm Time_module::getTime() {
    if(!getLocalTime(&time)){
        printf("No time available (yet)\n");
    }
    return time;
}

String Time_module::getClockText() {
    static char clockText[4];
    getTime();
    sprintf(clockText, "%02d%02d", time.tm_hour, time.tm_min);
    return String(clockText);
}