#ifndef Weather_h
#define Weather_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "BuSW.h"
#include "Http.h"
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
int weathericons[3][5] =
    {
        {69, 66, 64, 65, 67},      // 日晴 夜晴 阴 多云 雨
        {259, 223, 127, 124, 241}, // 日晴 夜晴 阴 多云 雨
        {259, 223, 127, 124, 241}, // 日晴 夜晴 阴 多云 雨
};
int IcCo[3] = {0, 0, 0};
int Icon[3] = {0, 0, 0};
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
  static int w = 0;
  if (!w && (WiFi.status() == WL_CONNECTED))
  {
    setCpuFrequencyMhz(240);
    WeatherNow();
    WeatherDaily();
    setCpuFrequencyMhz(80);
    w = 1;
  }
  else if (!w && WiFi.status() != WL_CONNECTED)
  {
    icon(53, 24, 283);
    delay(500);
  }
  Switch = 0;
  Button = 0;
  int i = 0;
  while (!Button)
  {
    if (Switch && (WiFi.status() == WL_CONNECTED))
    {
      WeatherNow();
      WeatherDaily();
      Switch = 0;
    }
    else if (Switch && (WiFi.status() != WL_CONNECTED))
    {
      icon(53, 24, 283);
      delay(500);
    }
    Switch = 0;
    Button = 0;
    joystick(&i, &Nul);
    i += 2;
    i %= 2;
    weadisplay(i);
  }
  Switch = 0;
  Button = 0;
}
/////////////////////////////////////////

// 天气显示
/////////////////////////////////////////
void weadisplay(int s)
{
  //
  switch (s)
  {
  case 0:
  {
    weaicons(0);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
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
    u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
    u8g2.drawGlyph(45, 32, Icon[0]);
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    u8g2.clearBuffer();
    int i = 0;
    for (int i = 0; i < 2; ++i)
    {
      weaicons(i + 1);
      u8g2.setFont(u8g2_font_helvB12_te);
      if (MaxT[i + 1] <= -10)
        u8g2.setCursor(31 + i * 62, 14);
      else if (MaxT[i + 1] <= -1 && MaxT[i + 1] >= -9)
        u8g2.setCursor(40 + i * 62, 14);
      else if (MaxT[i + 1] >= 0 && MaxT[i + 1] <= 9)
        u8g2.setCursor(45 + i * 62, 14);
      else
        u8g2.setCursor(36 + i * 62, 14);
      u8g2.printf("%d", MaxT[i + 1]); // MaxT
      if (MinT[i + 1] <= -10)
        u8g2.setCursor(31 + i * 62, 30);
      else if (MinT[i + 1] <= -1 && MinT[i + 1] >= -9)
        u8g2.setCursor(40 + i * 62, 30);
      else if (MinT[i + 1] >= 0 && MinT[i + 1] <= 9)
        u8g2.setCursor(45 + i * 62, 30);
      else
        u8g2.setCursor(36 + i * 62, 30);
      u8g2.printf("%d", MinT[i + 1]); // MinT
      u8g2.drawRBox(7 + i * 62, 1, 21, 14, 1);
      u8g2.setCursor(9 + i * 62, 14);
      u8g2.setDrawColor(0);
      u8g2.printf("%02d", Date[i + 1]); // Date
      u8g2.setDrawColor(1);
      u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
      u8g2.drawGlyph(10 + i * 62, 32, Icon[1]); // Icon
    }
    u8g2.sendBuffer();
    break;
  }
  }
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void weaicons(int i)
{
  if (IcCo[i] == 0 || IcCo[i] == 2)
  {
    Icon[i] = weathericons[i][0];
  }
  else if (IcCo[i] == 1 || IcCo[i] == 3)
  {
    Icon[i] = weathericons[i][1];
  }
  else if (IcCo[i] >= 4 && IcCo[i] <= 8)
  {
    Icon[i] = weathericons[i][3];
  }
  else if (IcCo[i] == 9 || (IcCo[i] >= 26 && IcCo[i] <= 31))
  {
    Icon[i] = weathericons[i][2];
  }
  else if (IcCo[i] >= 10 && IcCo[i] <= 20)
  {
    Icon[i] = weathericons[i][4];
  }
}
/////////////////////////////////////////

// 此刻天气
/////////////////////////////////////////
void WeatherNow()
{
  delay(10);
  icon(53, 24, 125);
  HTTPClient http;
  http.begin(weanow);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(200);
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND)
    {
      String result = http.getString();
      deserializeJson(doc, result);
      String tem = doc["results"][0]["now"]["temperature"];
      String ico0 = doc["results"][0]["now"]["code"];
      Tem = atoi(tem.c_str());
      IcCo[0] = atoi(ico0.c_str());
      icon(53, 24, 115);
      delay(500);
    }
  }
  else
  {
    icon(53, 24, 283);
    delay(500);
  }
  Switch = 0;
  http.end();
  doc.clear();
}
/////////////////////////////////////////

// 多日天气
/////////////////////////////////////////
void WeatherDaily()
{
  delay(10);
  icon(53, 24, 125);
  HTTPClient http;
  http.begin(weadaily);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(200);
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND)
    {
      String result = http.getString();
      deserializeJson(doc, result);
      String hum = doc["results"][0]["daily"][0]["humidity"];
      Hum = atoi(hum.c_str());
      Serial.println(result);
      for (int i = 0; i < 3; ++i)
      {
        String mat = doc["results"][0]["daily"][i]["high"];
        String mit = doc["results"][0]["daily"][i]["low"];
        MaxT[i] = atoi(mat.c_str());
        MinT[i] = atoi(mit.c_str());
        if (i)
        {
          String ico = doc["results"][0]["daily"][i]["code_day"];
          String dat = doc["results"][0]["daily"][i]["date"];
          IcCo[i] = atoi(ico.c_str());
          Date[i] = (dat[8] - 48) * 10 + (dat[9] - 48);
        }
      }
      icon(53, 24, 115);
      delay(500);
    }
  }
  else
  {
    icon(53, 24, 283);
    delay(500);
  }
  Switch = 0;
  http.end();
  doc.clear();
}
/////////////////////////////////////////

#endif

// Switch  = 0;
// Button  = 0;
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