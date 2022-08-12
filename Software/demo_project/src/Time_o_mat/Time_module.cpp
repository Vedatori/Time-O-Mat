#include "Time_module.h"

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