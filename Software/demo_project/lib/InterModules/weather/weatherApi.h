#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <Preferences.h>

#include "weather.h"

#define WEATHER_FORECAST_SIZE 8 //3h step for 1 day
#define MIN_UPDATE_PERIOD 1000*60*5	//[ms] 

namespace WEATHERAPI{

enum WEATHERAPI_SET_MODE{
	WA_SAVE,
	WA_SET,
	WA_DEFAULT
};

}

class WeatherApi {
private:
	String apiKey = "";
	
	Weather currentWeather;
	Weather forecast[WEATHER_FORECAST_SIZE]; 

	Preferences preferences;

	double positionLat = 0;
	double positionLon = 0;
	String positionName = "";
	int updatePeriod = MIN_UPDATE_PERIOD;

public:
	void init(int newUpdatePeriod);

	void setKey(String key, WEATHERAPI::WEATHERAPI_SET_MODE mode = WEATHERAPI::WA_SAVE);
	String getKey() {return apiKey;}

	void setPosition(double latitude, double longitude, String name, WEATHERAPI::WEATHERAPI_SET_MODE mode = WEATHERAPI::WA_SAVE);

	void updateWeather();
	void updateForecast();
	void updateBothWF();

	Weather getWeather();
	Weather getForecast(int index);

	String getPositionDisplayName() {return positionName;}
	double getPositionLatitude() {return positionLat;}
	double getPositionLongitude() {return positionLon;}

	


	bool geocodingByName(String name, String &retName, double &retLat, double &retLon);

	bool geocodingByName(String name);
};