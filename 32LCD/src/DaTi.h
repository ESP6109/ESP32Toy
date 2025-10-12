#ifndef DaTi_h
#define DaTi_h

#include <Arduino.h>
#include <Ticker.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WIFIset.h"

// 日期与时间
/////////////////////////////////////////
int Yea = 1970, Mon = 1, Day = 1; // 年月日
int Hou = 8, Min = 0, Sec = 0;    // 时分秒
int Wee = 1;                      // 星期
int sum[14];
char week[1];
Ticker esp_timer;                 // 时钟计时
bool G_t = 0;                     // 接入卫星时间
/////////////////////////////////////////

// HTTP
/////////////////////////////////////////
String url = "http://api.k780.com/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json";
JsonDocument doc;

/////////////////////////////////////////

void clccal();
void clksets();
void NetDT();

// 日历与时钟
/////////////////////////////////////////
void clccal()
{
  //   timer();
  if (!G_t)
    Sec = Sec + 1;
  if (Sec > 59)
  {
    Sec = 0;
    Min++;
  }
  if (Min > 59)
  {
    Min = 0;
    Hou++;
  }
  if (Hou >= 24)
  {
    Hou = 0;
    Day++;
  }
  if ((Mon == 1 || Mon == 3 || Mon == 5 || Mon == 7 || Mon == 8 || Mon == 10 || Mon == 12) && (Day > 31))
  {
    Mon++;
    Day %= 31;
  }
  else if ((Mon == 4 || Mon == 6 || Mon == 9 || Mon == 11) && (Day > 30))
  {
    Mon++;
    Day %= 30;
  }
  else if (Mon == 2)
  {
    if ((Yea % 4 == 0 || Yea % 400 == 0) && (Yea % 100 != 0) && Day > 29)
    {
      Mon++;
      Day %= 29;
    }
    else if ((Yea % 4 != 0 || Yea % 100 == 0) && Day > 28)
    {
      Mon++;
      Day %= 28;
    }
  }
  if (Mon > 12)
  {
    Yea++;
    Mon %= 12;
  }
  if (Mon == 1 || Mon == 2)
    Wee = (Day + 2 * (Mon + 12) + 3 * (Mon + 12 + 1) / 5 + (Yea - 1) + (Yea - 1) / 4 - (Yea - 1) / 100 + (Yea - 1) / 400) % 7;
  else
    Wee = (Day + 2 * Mon + 3 * (Mon + 1) / 5 + Yea + Yea / 4 - Yea / 100 + Yea / 400) % 7;
  Wee++;
  /*if (Hou == 17 && Min == 7)
    ring();*/
}
/////////////////////////////////////////

// 校时
/////////////////////////////////////////
void clksets()
{
  int a = 0, b = 0;
  while (!Button.pressed)
  {
    joystick(NULL, &b);
    b = (b + 2) % 2;
    u8g2.clearBuffer();
    u8g2.drawBox(37, 3 + 15 * b, 11, 11);
    u8g2.drawBox(75, 3 + 15 * b, 11, 11);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 20);
    u8g2.printf("校时");
    u8g2.setCursor(50, 13);
    u8g2.printf("卫星");
    u8g2.setCursor(50, 28);
    u8g2.printf("WIFI");
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    u8g2.sendBuffer();
  }
  Switch.pressed = 0;
  Button.pressed = 0;
}
/////////////////////////////////////////

/////////////////////////////////////////
void net()
{
  // LCD(45, 32, 198);
  int r = 0;
  delay(10);
  setCpuFrequencyMhz(240);
  HTTPClient http;
  http.begin(url);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  Serial.print("get");
  delay(1000);
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND)
    {
      // l1 = false;
      // l2 = true;
      String result = http.getString();
      Serial.println(result);
      deserializeJson(doc, result);
      String a = doc["result"]["datetime_2"]; // 日期时间
      String w = doc["result"]["week_1"];     // 星期
      const char *t = a.c_str();
      const char *get_week = w.c_str();
      // week[0] = get_week[0];
      if (week[0] - 48 == 0)
        week[0] = 55;
      doc.clear();
      http.end();
      setCpuFrequencyMhz(80);
      // Serial.println(a);
      for (int i = 0; i < strlen(t); ++i)
      {
        if (t[i] >= '0' && t[i] <= '9')
        {
          sum[r] = t[i] - 48;
          ++r;
        }
      }
      Day = sum[6] * 10 + sum[7];
      Mon = sum[4] * 10 + sum[5];
      Yea = sum[0] * 1000 + sum[1] * 100 + sum[2] * 10 + sum[3];
      Sec = sum[12] * 10 + sum[13] + 1;
      Min = sum[10] * 10 + sum[11];
      Hou = sum[8] * 10 + sum[9];
      Wee=week[0]-48;
      return;
    }
    else // if (httpCode != HTTP_CODE_OK || httpCode != HTTP_CODE_FOUND)
    {
      // l1 = true;
      // l2 = false;
      delay(5000);
      Serial.print("failed");
      return;
    }
  }
  // l1 = true;
  // l2 = false;
  http.end();
  setCpuFrequencyMhz(80);
}
/////////////////////////////////////////

#endif