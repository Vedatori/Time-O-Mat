#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <Preferences.h>

#include "weather.h"

#define WEATHER_FORECAST_SIZE 8 //3h step for 1 day

class WeatherApi {
private:
	String apiKey = "";
	
	Weather currentWeather;
	Weather forecast[WEATHER_FORECAST_SIZE]; 

	Preferences preferences;

	double positionLat = 0;
	double positionLon = 0;
	String positionName = "Not set";

public:
	void init();

	void setKey(String key);

	void setPosition(double latitude, double longitude, String name);

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