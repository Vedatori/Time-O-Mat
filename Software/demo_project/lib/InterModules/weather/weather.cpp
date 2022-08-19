#include "weather.h"

void Weather::processCurrentWeather(JsonObject JSON){
	temperature = JSON["main"]["temp"];
	tempFeelsLike = JSON["main"]["feels_like"];
	humidity = JSON["main"]["humidity"];
	pressure = JSON["main"]["pressure"];

	visibility = JSON["visibility"];

	windSpeed = JSON["wind"]["speed"];
	windHeading = JSON["wind"]["deg"];
	windGust = JSON["wind"]["gust"];

	clouds = JSON["clouds"]["all"];

	positionLongitude = JSON["coord"]["lon"];
	positionLatitude = JSON["coord"]["lat"];

	if(JSON["weather"].as<JsonArray>()[0].as<JsonObject>()["main"].as<const char*>() != nullptr){
		weatherString = JSON["weather"].as<JsonArray>()[0].as<JsonObject>()["main"].as<const char*>();
	}else{
		weatherString = "";
	}

	if(JSON["weather"].as<JsonArray>()[0].as<JsonObject>()["description"].as<const char*>() != nullptr){
		weatherDescription = JSON["weather"].as<JsonArray>()[0].as<JsonObject>()["description"].as<const char*>();
	}else{
		weatherDescription = "";
	}
	

	weatherCode = JSON["weather"].as<JsonArray>()[0].as<JsonObject>()["id"];
	timeOfCalculation = JSON["dt"];
	timeZone = JSON["timezone"];
	sunrise = JSON["sys"]["sunrise"];
	sunset = JSON["sys"]["sunset"];

	if(JSON["name"].as<const char*>() != nullptr){
		cityName = JSON["name"].as<const char*>();
	}else{
		cityName = "";
	}
	
	cityId = JSON["id"];

	if(JSON["sys"]["country"].as<const char*>() != nullptr){
		countryCode = JSON["sys"]["country"].as<const char*>();
	}else{
		countryCode = "";
	}
	

	rain = JSON["rain"]["3h"];
	snow = JSON["snow"]["3h"];
}

void Weather::processForecast(JsonObject JSON){
	JsonArray tempJsonArray = JSON["list"].as<JsonArray>();
	JsonObject tempList1stElement = tempJsonArray.getElement(0).as<JsonObject>();

	temperature = tempList1stElement["main"]["temp"];
	tempFeelsLike = tempList1stElement["main"]["feels_like"];
	humidity = tempList1stElement["main"]["humidity"];
	pressure = tempList1stElement["main"]["pressure"];

	visibility = tempList1stElement["visibility"];

	windSpeed = tempList1stElement["wind"]["speed"];
	windHeading = tempList1stElement["wind"]["deg"];
	windGust = tempList1stElement["wind"]["gust"];

	clouds = tempList1stElement["clouds"]["all"];

	if(tempList1stElement["weather"].as<JsonArray>()[0].as<JsonObject>()["main"].as<const char*>() != nullptr){
		weatherString = tempList1stElement["weather"].as<JsonArray>()[0].as<JsonObject>()["main"].as<const char*>();
	}else{
		weatherString = "";
	}
	
	if(tempList1stElement["weather"].as<JsonArray>()[0].as<JsonObject>()["description"].as<const char*>() != nullptr){
		weatherDescription = tempList1stElement["weather"].as<JsonArray>()[0].as<JsonObject>()["description"].as<const char*>();
	}else{
		weatherDescription = "";
	}
	
	timeOfCalculation = tempList1stElement["dt"];
	weatherCode = tempList1stElement["weather"].as<JsonArray>()[0].as<JsonObject>()["id"];

	rain = tempList1stElement["rain"]["3h"];
	snow = tempList1stElement["snow"]["3h"];

	positionLongitude = JSON["city"]["coord"]["lon"];
	positionLatitude = JSON["city"]["coord"]["lat"];
	timeZone = JSON["city"]["timezone"];
	sunrise = JSON["city"]["sunrise"];
	sunset = JSON["city"]["sunset"];

	if(JSON["city"]["name"].as<const char*>() != nullptr){
		cityName = JSON["city"]["name"].as<const char*>();
	}else{
		cityName = "";
	}
	

	cityId = JSON["city"]["id"];

	if(JSON["city"]["country"].as<const char*>() != nullptr){
		countryCode = JSON["city"]["country"].as<const char*>();
	}else{
		countryCode = "";
	}
	

	
}

void Weather::dump(Stream &stream){
	stream.printf("temperature: %f\n",temperature);
	stream.printf("tempFeelsLike: %f\n",tempFeelsLike);
	stream.printf("humidity: %f\n",humidity);
	stream.printf("pressure: %f\n",pressure);
	stream.printf("visibility: %d\n",visibility);
	stream.printf("windSpeed: %f\n",windSpeed);
	stream.printf("windHeading: %f\n",windHeading);
	stream.printf("windGust: %f\n",windGust);
	stream.printf("clouds: %f\n",clouds);
	stream.printf("positionLongitude: %f\n",positionLongitude);
	stream.printf("positionLatitude: %f\n",positionLatitude);
	stream.printf("weatherString: %s\n",weatherString.c_str());
	stream.printf("weatherDescription: %s\n",weatherDescription.c_str());
	stream.printf("timeOfCalculation: %u\n",timeOfCalculation);
	stream.printf("timeZone: %u\n",timeZone);
	stream.printf("sunrise: %u\n",sunrise);
	stream.printf("sunset: %u\n",sunset);
	stream.printf("cityName: %s\n",cityName.c_str());
	stream.printf("cityId: %u\n",cityId);
	stream.printf("countryCode: %s\n",countryCode.c_str());
	stream.printf("rain: %f\n", rain);
	stream.printf("snow: %f\n", snow);
	stream.printf("weatherCode: %d\n", weatherCode);
}

void Weather::printDebug(){
	printf("temperature: %f\n",temperature);
	printf("tempFeelsLike: %f\n",tempFeelsLike);
	printf("humidity: %f\n",humidity);
	printf("pressure: %f\n",pressure);
	printf("visibility: %d\n",visibility);
	printf("windSpeed: %f\n",windSpeed);
	printf("windHeading: %f\n",windHeading);
	printf("windGust: %f\n",windGust);
	printf("clouds: %f\n",clouds);
	printf("positionLongitude: %f\n",positionLongitude);
	printf("positionLatitude: %f\n",positionLatitude);
	printf("weatherString: %s\n",weatherString.c_str());
	printf("weatherDescription: %s\n",weatherDescription.c_str());
	printf("timeOfCalculation: %u\n",timeOfCalculation);
	printf("timeZone: %u\n",timeZone);
	printf("sunrise: %u\n",sunrise);
	printf("sunset: %u\n",sunset);
	printf("cityName: %s\n",cityName.c_str());
	printf("cityId: %u\n",cityId);
	printf("countryCode: %s\n",countryCode.c_str());
	printf("rain: %f\n", rain);
	printf("snow: %f\n", snow);
	printf("weatherCode: %d\n", weatherCode);
}