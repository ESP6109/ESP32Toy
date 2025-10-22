#ifndef DaTi_h
#define DaTi_h

#include <Arduino.h>
#include <Ticker.h>

#include "Http.h"
#include "WIFIset.h"

// 日期与时间
/////////////////////////////////////////
int Yea = 1970, Mon = 1, Day = 1; // 年月日
int Hou = 8, Min = 0, Sec = 0;    // 时分秒
int Wee = 1;                      // 星期
Ticker esp_timer;                 // 时钟计时
bool N_t = 0;                     // 接入网络时间
bool G_t = 0;                     // 接入卫星时间
int C_h = 0, C_m = 0;
int Clset = 0;
/////////////////////////////////////////

void SecCou();
void clccal();
void clksets();
void NetDT();

// 秒针走时
/////////////////////////////////////////
void SecCou()
{
  if (!G_t)
    Sec = Sec + 1;
  clccal();
  // if (Clset && Hou == C_h && Min == C_m)
    // ring(1);
}
/////////////////////////////////////////

// 日历与时钟
/////////////////////////////////////////
void clccal()
{
  //   timer();

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
  NetDT();
  /*int a = 0, b = 0;
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
  Button.pressed = 0;*/
}
/////////////////////////////////////////

// 互联网校时
/////////////////////////////////////////
void NetDT()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    icon(53, 24, 283);
    delay(300);
    return;
  }
  icon(53, 24, 198);
  delay(10);
  setCpuFrequencyMhz(240);
  HTTPClient http;
  http.begin(nettime);
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
      String date = doc["result"]["datetime_1"]; // 日期时间
      String week = doc["result"]["week_1"];     // 星期
      const char *tempdt = date.c_str();
      const char *tempwe = week.c_str();
      Serial.println(tempdt);
      Yea = (tempdt[0] - 48) * 1000 + (tempdt[1] - 48) * 100 + (tempdt[2] - 48) * 10 + (tempdt[3] - 48);
      Mon = (tempdt[5] - 48) * 10 + (tempdt[6] - 48);
      Day = (tempdt[8] - 48) * 10 + (tempdt[9] - 48);
      Hou = (tempdt[11] - 48) * 10 + (tempdt[12] - 48);
      Min = (tempdt[14] - 48) * 10 + (tempdt[15] - 48);
      Sec = (tempdt[17] - 48) * 10 + (tempdt[18] - 48) + 1;
      if (tempwe[0] - 48)
        Wee = tempwe[0] - 48;
      else
        Wee = 7;
      N_t = 1;
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
  doc.clear();
  http.end();
  setCpuFrequencyMhz(80);
}
/////////////////////////////////////////

#endif