#ifndef Gps_h
#define GPS_h

#include <Arduino.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "DaTi.h"
#include "LCD.h"

// GPS接口
/////////////////////////////////////////
// Serial2
#define TX 17
#define RX 16
/////////////////////////////////////////

// 定位
/////////////////////////////////////////
TinyGPSPlus GPS;
TinyGPSCustom A(GPS, "GPRMC", 2);  // 有效值
TinyGPSCustom NS(GPS, "GPRMC", 4); // 南北
TinyGPSCustom WE(GPS, "GPRMC", 6); // 东西
/////////////////////////////////////////

// 定位数据
/////////////////////////////////////////
float Lng = 0, Lat = 0; // 经纬
int Spe = 0;            // 速度
int Deg = 0;            // 方向角
char Cou[3];            // 方向
char Ava[2];            // 有效值
/////////////////////////////////////////

void gps();
void gpsget();
void gpsdata();
void gpsdisplay(int);

// 定位
/////////////////////////////////////////
void gps()
{
  int a = 0;
  setCpuFrequencyMhz(240);
  while (!Button.pressed)
  {
    gpsget();
    joystick(&a, NULL);
    a = a + 4;
    a %= 4;
    if (Ava[0] == 'V') // 无效
    {
      digitalWrite(2, 0);
      G_t = 0;
    }
    else if (Ava[0] == 'A') // 有效
    {
      digitalWrite(2, 1);
      G_t = 1;
    }
    gpsdisplay(a);
  }
  Switch.pressed = 0;
  Button.pressed = 0;
  setCpuFrequencyMhz(80);
  G_t = 0;
  digitalWrite(2, 0);
}
/////////////////////////////////////////

// 卫星数据
/////////////////////////////////////////
void gpsget()
{
  for (unsigned long m = millis(); millis() - m <= 500;)
  {
    while (Serial2.available())
    {
      GPS.encode(Serial2.read());
      // Serial.printf("%c",Serial2.read());
    }
  }
  gpsdata();
}
/////////////////////////////////////////

// 卫星数据
/////////////////////////////////////////
void gpsdata()
{
  Yea = GPS.date.year();   // 年
  Mon = GPS.date.month();  // 月
  Day = GPS.date.day();    // 日
  Hou = GPS.time.hour();   // 时
  Min = GPS.time.minute(); // 分
  Sec = GPS.time.second(); // 秒
  Hou += 8;
  Lng = GPS.location.lng(); // 经度
  Lat = GPS.location.lat(); // 纬度
  Spe = GPS.speed.kmph();   // 速度
  Deg = GPS.course.deg();   // 方向角
  strcpy(Ava, A.value());
  if ((Deg > 338 && Deg < 360) || (Deg >= 0 && Deg < 22)) // N
  {
    strcpy(Cou, "N");
  }
  else if (Deg >= 22 && Deg <= 68) // NE
  {
    strcpy(Cou, "NE");
  }
  else if (Deg > 68 && Deg < 112) // E
  {
    strcpy(Cou, "E");
  }
  else if (Deg >= 112 && Deg <= 158) // SE
  {
    strcpy(Cou, "SE");
  }
  else if (Deg > 158 && Deg < 202) // S
  {
    strcpy(Cou, "S");
  }
  else if (Deg >= 202 && Deg <= 248) // SW
  {
    strcpy(Cou, "SW");
  }
  else if (Deg > 248 && Deg < 292) // W
  {
    strcpy(Cou, "W");
  }
  if (Deg >= 292 && Deg <= 338) // NW
  {
    strcpy(Cou, "NW");
  }
}
/////////////////////////////////////////

// 定位显示
/////////////////////////////////////////
void gpsdisplay(int s)
{
  switch (s)
  {
  case 0:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tr);
    u8g2.setCursor(2, 14);
    u8g2.printf("%02d.%02d.%02d-%d\n", (Yea % 100), Mon, Day, Wee);
    u8g2.setCursor(10, 30);
    u8g2.printf("%02d:%02d\n", Hou, Min);
    if (Spe <= 9)
      u8g2.setCursor(112, 14);
    else if (Spe >= 10 && Spe <= 99)
      u8g2.setCursor(103, 14);
    else
      u8g2.setCursor(94, 14);
    u8g2.printf("%d\n", Spe);
    if (Lat <= 9)
      u8g2.setCursor(71, 30);
    else
      u8g2.setCursor(62, 30);
    u8g2.printf("%d\n", int(Lat));
    if (Lng <= 9)
      u8g2.setCursor(104, 30);
    else if (Lng >= 10 && Lng <= 99)
      u8g2.setCursor(95, 30);
    else
      u8g2.setCursor(86, 30);
    u8g2.printf("%d\n", int(Lng));
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tr);
    u8g2.setCursor(15, 14);
    u8g2.printf("%4d.%02d.%02d-%d\n", Yea, Mon, Day, Wee);
    u8g2.setCursor(30, 30);
    u8g2.printf("%02d:%02d:%02d\n", Hou, Min, Sec);
    u8g2.sendBuffer();
    break;
  }
  case 2:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tr);
    if (int(Lat) >= 10 && int(Lat) <= 99)
      u8g2.setCursor(10, 14);
    else
      u8g2.setCursor(19, 14);
    u8g2.printf("%d.%06d", int(Lat), int((Lat * 1000000)) % 1000000);
    if (int(Lng) >= 0 && int(Lng) <= 9)
      u8g2.setCursor(19, 30);
    else if (int(Lng) >= 10 && int(Lng) <= 99)
      u8g2.setCursor(10, 30);
    else
      u8g2.setCursor(1, 30);
    u8g2.printf("%d.%06d", int(Lng), int((Lng * 1000000)) % 1000000);
    u8g2.setCursor(100, 14);
    u8g2.printf("%s", NS.value());
    u8g2.setCursor(100, 30);
    u8g2.printf("%s", WE.value());
    u8g2.sendBuffer();
    break;
  }
  case 3:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(1, 30);
    u8g2.printf("%s", Cou);
    u8g2.setCursor(1, 14);
    u8g2.printf("%d\n", Deg);
    u8g2.setFont(u8g2_font_logisoso32_tn);
    u8g2.setCursor(63, 32);
    u8g2.printf("%03d\n", Spe);
    u8g2.sendBuffer();
    break;
  }
  }
}
/////////////////////////////////////////

#endif