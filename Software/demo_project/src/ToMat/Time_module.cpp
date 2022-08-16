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
    char clockText[4];
    getTime();
    sprintf(clockText, "%02d%02d", time.tm_hour, time.tm_min);
	if(clockText[0]=='0') clockText[0] = ' ';
    return String(clockText);
}