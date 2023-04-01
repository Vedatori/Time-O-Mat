#include "weatherApi.h"
#include "json/json.h"

// Temp befor wifi module is done
int makeHttpRequest(String url, String &out) {
	HTTPClient http;
	http.begin(url);

	int httpResponseCode = http.GET();

	out = http.getString();

	return httpResponseCode;
}


void WeatherApi::init(int newUpdatePeriod){
	preferences.begin("weatherApi-owm");
	if(preferences.isKey("apiKey")){
		apiKey = preferences.getString("apiKey");
	}
	if(preferences.isKey("positionName")) {
		positionLat = preferences.getDouble("positionLat");
		positionLon = preferences.getDouble("positionLon");
		positionName = preferences.getString("positionName");
	}
	updatePeriod = (newUpdatePeriod > MIN_UPDATE_PERIOD) ? newUpdatePeriod : MIN_UPDATE_PERIOD;
}
void WeatherApi::setKey(String key, WEATHERAPI::WEATHERAPI_SET_MODE mode){
	switch(mode){
		case WEATHERAPI::WA_DEFAULT:
			if (apiKey == "") apiKey = key;
			break;
		case WEATHERAPI::WA_SET:
			apiKey = key;
			break;
		case WEATHERAPI::WA_SAVE:
			apiKey = key;
			preferences.putString("apiKey", apiKey);
			break;
	}
	
}
void WeatherApi::setPosition(double latitude, double longitude, String name, WEATHERAPI::WEATHERAPI_SET_MODE mode) {
	switch (mode)
	{
	case WEATHERAPI::WA_DEFAULT:
		if(positionLat == 0 && positionLon == 0 && positionName == ""){
			positionLat = latitude;
			positionLon = longitude;
			positionName = name;
		}
		break;
	case WEATHERAPI::WA_SET:
		positionLat = latitude;
		positionLon = longitude;
		positionName = name;
		break;
	case WEATHERAPI::WA_SAVE:
		positionLat = latitude;
		positionLon = longitude;
		positionName = name;
		preferences.putDouble("positionLat", positionLat);
		preferences.putDouble("positionLon", positionLon);
		preferences.putString("positionName", positionName);
		break;

	}
	
}



void WeatherApi::updateWeather() {
	static uint32_t prevUpdate = 0;
	if(prevUpdate == 0 || (millis() - prevUpdate) > updatePeriod) {
		prevUpdate = millis();
		String data = "";
		int code = makeHttpRequest("http://api.openweathermap.org/data/2.5/weather?units=metric&lat="+String(positionLat)+"&lon="+String(positionLon)+"&appid="+String(apiKey), data);
		if(code!=200){
			printf("updateWeather failed, code %d: %s", code, data.c_str());
			return;
		}

		StaticJsonDocument<1024> jsonDoc;
		deserializeJson(jsonDoc,data);
		currentWeather.processCurrentWeather(jsonDoc.as<JsonObject>());
	}
}
void WeatherApi::updateForecast() {
	static uint32_t prevUpdate = 0;
	if(prevUpdate == 0 || (millis() - prevUpdate) > updatePeriod) {
		prevUpdate = millis();
		String data = "";
		int code = makeHttpRequest("http://api.openweathermap.org/data/2.5/forecast?units=metric&lat="+String(positionLat)+"&lon="+String(positionLon)+"&appid="+String(apiKey)+"&cnt="+String(WEATHER_FORECAST_SIZE), data);
		if(code!=200){
			printf("updateForecast failed, code %d: %s", code, data.c_str());
			return;
		}

		DynamicJsonDocument temp(WEATHER_FORECAST_SIZE*1024);
		deserializeJson(temp, data);
		int cnt = temp["cnt"].as<int>();

		//serializeJsonPretty(temp, Serial);

		for(int i = 0; i < cnt && i < WEATHER_FORECAST_SIZE; i++){
			forecast[i].processForecast(temp.as<JsonObject>());
			temp["list"].as<JsonArray>().remove(0);
		}
	}
	
	/*
	DynamicJsonDocument temp(WEATHER_MAX_JSON_SIZE);
	DynamicJsonDocument tempFilter(256);
	tempFilter["city"] = true;
	tempFilter["cnt"] = true;
	deserializeJson(temp, data, DeserializationOption::Filter(tempFilter));

	DynamicJsonDocument list(WEATHER_FORECAST_SIZE*WEATHER_MAX_JSON_SIZE);
	DynamicJsonDocument listFilter(256);
	listFilter["list"] = true;
	deserializeJson(list, data, DeserializationOption::Filter(listFilter));

	int cnt = temp["cnt"].as<int>();

	for(int i = 0; i < cnt && i < WEATHER_FORECAST_SIZE; i++){
		temp["list"][0] = list["list"][i];
		serializeJsonPretty(temp, Serial);
		forecast[i].processForecast(temp.as<JsonObject>());
	}
	*/
}
void WeatherApi::updateBothWF(){
	updateWeather();
	updateForecast();
}

Weather WeatherApi::getWeather(){
	return currentWeather;
}

Weather WeatherApi::getForecast(int index){
	if(index >= WEATHER_FORECAST_SIZE){
		index = 0;
	}
	return forecast[index];
}

bool WeatherApi::geocodingByName(String name, String &retName, double &retLat, double &retLon){
	String data = "";
	int code = makeHttpRequest("http://api.openweathermap.org/geo/1.0/direct?q="+String(name)+"&appid="+String(apiKey), data);
	if(code!=200){
		return false;
	}
	StaticJsonDocument<128> filter;
	filter[0]["name"] = true;
	filter[0]["lat"] = true;
	filter[0]["lon"] = true;

	StaticJsonDocument<512> temp;
	deserializeJson(temp, data, DeserializationOption::Filter(filter));

	retName = temp[0]["name"].as<const char*>();
	retLat = temp[0]["lat"];
	retLon = temp[0]["lon"];



	return true;
}

bool WeatherApi::geocodingByName(String name){
	return geocodingByName(name, positionName, positionLat, positionLon);
	setPosition(positionLat, positionLon, positionName);
}
