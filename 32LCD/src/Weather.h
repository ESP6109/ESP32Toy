#ifndef Weather_h
#define Weather_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "BuSW.h"
#include "LCD.h"
#include "WIFIset.h"

// 温湿度
/////////////////////////////////////////
int Tem = 0, Hum = 0;
int MaxT[3] = {0, 0, 0};
int MinT[3] = {0, 0, 0};
/////////////////////////////////////////

// 日期
/////////////////////////////////////////
int Date[3] = {0, 0, 0};
/////////////////////////////////////////

// 天气图标
/////////////////////////////////////////
int weathericons[5] = {259, 223, 127, 124, 241}; // 日晴 夜晴 阴 云 雨
int IcCo[3] = {0, 0, 0};
int Icon[3] = {0, 0, 0};
/////////////////////////////////////////

// HTTP
/////////////////////////////////////////
String url1 = "https://api.seniverse.com/v3/weather/now.json?key=Ssc8BZZS3mQcC7kVV&location=wuhan&language=zh-Hans&unit=c";
JsonDocument doc1;
String url2 = "https://api.seniverse.com/v3/weather/daily.json?key=Ssc8BZZS3mQcC7kVV&location=wuhan&language=zh-Hans&unit=c&start=-1&days=5";
JsonDocument doc2;
/////////////////////////////////////////

void weather();
void weadisplay(int);
void weaicons(int);
void WeatherNow();
void WeatherDaily();

// 天气
/////////////////////////////////////////
void weather()
{
  int i = 0;
  while (!Button.pressed)
  {
    Switch.pressed = 0;
    Button.pressed = 0;
    joystick(&i, NULL);
    i += 2;
    i %= 2;
    weadisplay(i);
  }
  Switch.pressed = 0;
  Button.pressed = 0;
}
/////////////////////////////////////////

// 天气显示
/////////////////////////////////////////
void weadisplay(int s)
{
  int i = 0;
  //
  switch (s)
  {
  case 0:
  {
    weaicons(0);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    if (MaxT[0] <= -10)
      u8g2.setCursor(1, 14);
    else if (MaxT[0] >= -9 && MaxT[0] <= -1)
      u8g2.setCursor(10, 14);
    else if (MaxT[0] >= 0 && MaxT[0] <= 9)
      u8g2.setCursor(15, 14);
    else
      u8g2.setCursor(6, 14);
    u8g2.printf("%d°C", MaxT[0]);
    if (MinT[0] <= -10)
      u8g2.setCursor(1, 30);
    else if (MinT[0] >= -9 && MinT[0] <= -1)
      u8g2.setCursor(10, 30);
    else if (MinT >= 0 && MinT[0] <= 9)
      u8g2.setCursor(15, 30);
    else
      u8g2.setCursor(6, 30);
    u8g2.printf("%d°C", MinT[0]);
    if (Tem <= -10)
      u8g2.setCursor(80, 14);
    else if (Tem >= -9 && Tem <= -1)
      u8g2.setCursor(89, 14);
    else if (Tem >= 0 && Tem <= 9)
      u8g2.setCursor(94, 14);
    else
      u8g2.setCursor(85, 14);
    u8g2.printf("%d°C", Tem);
    if (Hum >= 0 && Hum <= 9)
      u8g2.setCursor(94, 30);
    else
      u8g2.setCursor(85, 30);
    u8g2.printf("%d %%", Hum);
    u8g2.setFont(u8g2_font_open_iconic_all_4x_t); // 设定字体
    u8g2.drawGlyph(45, 32, Icon[0]);
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    weaicons(1);
    weaicons(2);
    u8g2.clearBuffer();
    u8g2.drawRBox(7, 1, 21, 14, 1);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(9, 14);
    u8g2.setDrawColor(0);
    u8g2.printf("%02d", Date[1]); // Date1
    u8g2.setDrawColor(1);
    if (MaxT[1] <= -10)
      u8g2.setCursor(31, 14);
    else if (MaxT[1] <= -1 && MaxT[1] >= -9)
      u8g2.setCursor(40, 14);
    else if (MaxT[1] >= 0 && MaxT[1] <= 9)
      u8g2.setCursor(45, 14);
    else
      u8g2.setCursor(36, 14);
    u8g2.printf("%d", MaxT[1]); // MaxT1
    if (MinT[1] <= -10)
      u8g2.setCursor(31, 30);
    else if (MinT[1] <= -1 && MinT[1] >= -9)
      u8g2.setCursor(40, 30);
    else if (MinT[1] >= 0 && MinT[1] <= 9)
      u8g2.setCursor(45, 30);
    else
      u8g2.setCursor(36, 30);
    u8g2.printf("%d", MinT[1]); // MinT1
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(10, 32, Icon[1]);
    u8g2.drawRBox(69, 1, 21, 14, 1);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(71, 14);
    u8g2.setDrawColor(0);
    u8g2.printf("%02d", Date[2]); // Date2
    u8g2.setDrawColor(1);
    if (MaxT[1] <= -10)
      u8g2.setCursor(93, 14);
    else if (MaxT[2] <= -1 && MaxT[2] >= -9)
      u8g2.setCursor(102, 14);
    else if (MaxT[2] >= 0 && MaxT[2] <= 9)
      u8g2.setCursor(107, 14);
    else
      u8g2.setCursor(98, 14);
    u8g2.printf("%d", MaxT[2]); // MaxT2
    if (MinT[2] <= -10)
      u8g2.setCursor(93, 30);
    else if (MinT[2] <= -1 && MinT[2] >= -9)
      u8g2.setCursor(102, 30);
    else if (MinT[2] >= 0 && MinT[2] <= 9)
      u8g2.setCursor(107, 30);
    else
      u8g2.setCursor(98, 30);
    u8g2.printf("%d", MinT[2]); // MinT2
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(72, 32, Icon[2]);
    u8g2.sendBuffer();
    break;
  }
  }
}

/////////////////////////////////////////

void weaicons(int i)
{
  if (IcCo[i] == 0 || IcCo[i] == 2)
  {
    Icon[i] = weathericons[0];
  }
  else if (IcCo[i] == 1 || IcCo[i] == 3)
  {
    Icon[i] = weathericons[1];
  }
  else if (IcCo[i] >= 4 && IcCo[i] <= 8)
  {
    Icon[i] = weathericons[3];
  }
  else if (IcCo[i] == 9)
  {
    Icon[i] = weathericons[2];
  }
  else if (IcCo[i] >= 10 && IcCo[i] <= 20)
  {
    Icon[i] = weathericons[5];
  }
}

void WeatherNow() {
  Button.pressed = 0;
  delay(10);
  // LCD(45, 32, 198);
  setCpuFrequencyMhz(240);
  HTTPClient http;
  http.begin(url1);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(1000);
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
      String result = http.getString();
      Serial.println(result);
      deserializeJson(doc1, result);
      String tem = doc1["results"][0]["now"]["temperature"];
      String ico0 = doc1["results"][0]["now"]["code"];
      Tem = atoi(tem.c_str());
      IcCo[0] = atoi(ico0.c_str());
      delay(50);
      Button.pressed = 0;
      // return;
    }
  } else {
    Button.pressed = 0;
    // LCD(45, 32, 283);
    // Serial.print("failed");
    delay(1000);
  }
  http.end();
  setCpuFrequencyMhz(80);
}

void WeatherDaily() {
  Button.pressed = 0;
  delay(10);
  // LCD(45, 32, 198);
  setCpuFrequencyMhz(240);
  HTTPClient http;
  http.begin(url2);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(1000);
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
      String result = http.getString();
      Serial.println(result);
      deserializeJson(doc2, result);
      String hum = doc2["results"][0]["daily"][0]["humidity"];
      String mat0 = doc2["results"][0]["daily"][0]["high"];
      String mit0 = doc2["results"][0]["daily"][0]["low"];
      String mat1 = doc2["results"][0]["daily"][1]["high"];
      String mit1 = doc2["results"][0]["daily"][1]["low"];
      String mat2 = doc2["results"][0]["daily"][2]["high"];
      String mit2 = doc2["results"][0]["daily"][2]["low"];
      String ico1 = doc2["results"][0]["daily"][1]["code_day"];
      String ico2 = doc2["results"][0]["daily"][2]["code_day"];
      String Dat1 = doc2["results"][0]["daily"][1]["date"];
      String Dat2 = doc2["results"][0]["daily"][2]["date"];
      Hum = atoi(hum.c_str());
      MaxT[0] = atoi(mat0.c_str());
      MinT[0] = atoi(mit0.c_str());
      MaxT[1] = atoi(mat1.c_str());
      MinT[1] = atoi(mit1.c_str());
      MaxT[2] = atoi(mat2.c_str());
      MinT[2] = atoi(mit2.c_str());
      IcCo[1] = atoi(ico1.c_str());
      IcCo[2] = atoi(ico2.c_str());
      Date[1] = (Dat1[8] - 48) * 10 + (Dat1[9] - 48);
      Date[2] = (Dat2[8] - 48) * 10 + (Dat2[9] - 48);
      delay(50);
      Button.pressed = 0;
      // return;
    }
  } else {
    Button.pressed = 0;
    // LCD(45, 32, 283);
    // Serial.print("failed");
    delay(1000);
  }
  http.end();
  setCpuFrequencyMhz(80);
}

#endif

// Switch.pressed = 0;
// Button.pressed = 0;
/*int MaxT1 = 0, MinT1 = 0;
int MaxT2 = 0, MinT2 = 0;*/
// u8g2.clearBuffer();
// u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
// u8g2.drawGlyph(53, 24, 247);
// u8g2.sendBuffer();
/*if (Date[0] <= 9)
  u8g2.setCursor(18, 14);
else*/
/*if (Date[1] <= 9)
  u8g2.setCursor(80, 14);
else*/