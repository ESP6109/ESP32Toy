#ifndef Http_h
#define Http_h

#include <ArduinoJson.h>
#include <HTTPClient.h>


// HTTP
/////////////////////////////////////////
JsonDocument doc;
String nettime = "http://api.k780.com/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";
String weanow = "https://api.seniverse.com/v3/weather/now.json?key=Ssc8BZZS3mQcC7kVV&location=wuhan&language=zh-Hans&unit=c";
String weadaily = "https://api.seniverse.com/v3/weather/daily.json?key=Ssc8BZZS3mQcC7kVV&location=wuhan&language=zh-Hans&unit=c&start=-1&days=5";
/////////////////////////////////////////

#endif