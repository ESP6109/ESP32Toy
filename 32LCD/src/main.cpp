// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 4.3.8
// Building
// Release at 2025.10.14 19:03
#include <Arduino.h>
#include "esp32-hal-cpu.h"
#include <driver/gpio.h>

#include "BuSw.h"
#include "Clock.h"
#include "DaTi.h"
#include "GPS.h"
#include "Joy.h"
#include "Joystick.h"
#include "LCD.h"
#include "Power.h"
#include "Weather.h"
#include "WIFIset.h"

// 主界面图标
/////////////////////////////////////////
int menuicons[2][4] =
    {{124, 209, 93, 129},
     {92, 240, 141, 235}};
/////////////////////////////////////////

// 设置图标
/////////////////////////////////////////
int settingsicons[4] = {247, 94, 123, 188};
/////////////////////////////////////////

// 定义
/////////////////////////////////////////
void home();
void menu();
void weather();
void settings();
void lab();
void esp_info();
void building();
void manager();
void power();
/////////////////////////////////////////

// 初始化
/////////////////////////////////////////
void setup()
{
  u8g2.begin();
  Serial.begin(115200);
  Serial2.begin(9600);
  u8g2.enableUTF8Print();
  pinMode(2, OUTPUT);
  pinMode(Beep, OUTPUT);
  pinMode(BU, INPUT);
  pinMode(SW, INPUT_PULLUP); // z_PULLUP
  pinMode(JX, INPUT);        // x
  pinMode(JY, INPUT);        // y
  attachInterrupt(digitalPinToInterrupt(BU), button, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW), joysw, FALLING);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 0);
  setCpuFrequencyMhz(80);
  esp_timer.attach(1.0, SecCou);
  timer1 = timer2 = millis();
  clearscr();
}
/////////////////////////////////////////

// 主循环
/////////////////////////////////////////
void loop()
{
  home();
}
/////////////////////////////////////////

// 主页
/////////////////////////////////////////
void home()
{
  if (Switch)
  {
    Button = 0;
    Switch = 0;
    menu();
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_te);
  u8g2.setCursor(15, 14);
  u8g2.printf("%04d.%02d.%02d-%d\n", Yea, Mon, Day, Wee);
  u8g2.setCursor(30, 30);
  u8g2.printf("%02d:%02d:%02d\n", Hou, Min, Sec);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

// 主菜单
/////////////////////////////////////////
void menu()
{
  static int a = 0, b = 0, c = 0;
  int d = 1;
  while (d)
  {
    joystick(&a, &b);
    if (a >= 4 || a <= -1)
    {
      a = (a + 4) % 4;
      b += 1;
    }
    b = (b + 2) % 2;
    list4(a, menuicons[b]);
    c = b * 4 + (a + 1);
    if (Switch)
    {
      Switch = 0;
      Button = 0;
      switch (c)
      {
      case 1:
        weather();
        break;
      case 2:
        gps();
        break;
      case 3:
        timerset();
        break;
      case 4:
        settings();
        break;
      case 5:
        lab();
        break;
      case 7:
        manager();
        break;
      case 8:
        power();
        break;
      default:
        building();
      }
    }
    if (Button)
    {
      Button = 0;
      Switch = 0;
      a = b = c = d = 0;
    }
  }
  Button = 0;
  Switch = 0;
}
/////////////////////////////////////////

// 设置
/////////////////////////////////////////
void settings()
{
  static int a = 0, c = 0;
  int d = 1;
  while (d)
  {
    joystick(&a, &Nul);
    if (a >= 4 || a <= -1)
    {
      a = (a + 4) % 4;
      // b += 1;
    }
    // b = (b + H_I) % H_I;
    // b = 0;
    list4(a, settingsicons);
    c = a + 1;
    if (Switch)
    {
      Button = 0;
      Switch = 0;
      switch (c)
      {
      case 1:
        WIFIconnect();
        break;
      case 3:
        clksets();
        break;
      case 4:
        esp_info();
        break;
      default:
        building();
      }
    }
    if (Button)
    {
      Button = 0;
      Switch = 0;
      a = c = d = 0;
    }
  }
  Button = 0;
  Switch = 0;
}
/////////////////////////////////////////

// 测试
/////////////////////////////////////////
void lab()
{
  setCpuFrequencyMhz(240);
  while (!Button)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(4, 22);
    u8g2.printf("X-%04d", analogRead(JX));
    u8g2.setCursor(66, 22);
    u8g2.printf("Y-%04d", analogRead(JY));
    /*u8g2.setCursor(56, 22);
    u8g2.printf("SW-%04d", analogRead(SW));
    u8g2.setCursor(56, 14);
     u8g2.printf("BU-%04d", analogRead(BU));
     u8g2.setCursor(56, 30);
     u8g2.printf("SW-%04d", analogRead(SW));*/
    u8g2.sendBuffer();
  }
  Switch = 0;
  Button = 0;
  setCpuFrequencyMhz(80);
}
/////////////////////////////////////////

// 关于
/////////////////////////////////////////
void esp_info()
{
  while (!Button)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    /*static int i = 0;
    joystick(&Nul, &i);
    i %= (i + 2);
    u8g2.setCursor(13, 9);
    u8g2.printf("Built on ESP Tech.");
    u8g2.setCursor(4, 20);
    u8g2.printf("Designed by ESP6109.");*/
    u8g2.setCursor(10, 22);
    u8g2.printf("Version 4.3.8");
    u8g2.sendBuffer();
  }
  Switch = 0;
  Button = 0;
}
/////////////////////////////////////////

// BUILDING
/////////////////////////////////////////
void building()
{
  while (!Button)
  {
    icon(53, 24, 282);
  }
  Switch = 0;
  Button = 0;
}
/////////////////////////////////////////

// 管理器
/////////////////////////////////////////
void manager()
{
  /*unsigned int i, j = 0;
  i = millis() / 1000;
  while ((millis() / 1000) - i > 0)
  {
    if (button())
      j = (j + 1) % 2;
    i = millis() / 1000;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_t0_16_mf);
    u8g2.setCursor(10, 10);
    u8g2.printf("Start Manager");
    u8g2.setCursor(105, 30);
    u8g2.printf("%d", 3 - i);
    u8g2.setCursor(21, 30);
    u8g2.printf("%d", j + 1);
    u8g2.sendBuffer();
    delay(1);
  }
  if (3 - i <= 0)
    switch (j)
    {
    case 0:
      s_box();
      break;
    case 1:
      s_shot();
      break;
    }*/
  s_box();
  clearscr();
  s_shot();
  Switch = 0;
  Button = 0;
}
/////////////////////////////////////////

// 电源选项
/////////////////////////////////////////
void power()
{
  static int a = 0, c = 0;
  int d = 1;
  while (d)
  {
    joystick(&a, &Nul);
    if (a >= 2 || a <= -1)
    {
      a = (a + 2) % 2;
    }
    // b = (b + H_I) % H_I;
    // b = 0;
    list2(a, powericons);
    c = a + 1;
    if (Switch)
    {
      Switch = 0;
      power(a);
    }
  }
  if (Button)
  {
    Button = 0;
    Switch = 0;
    a = c = d = 0;
  }
}
/////////////////////////////////////////
