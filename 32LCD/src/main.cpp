// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 4.0.9
// Building
// Release at 2025.10.11 17:14
#include <Arduino.h>
#include <u8g2lib.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "esp32-hal-cpu.h"
#include <driver/gpio.h>
#include <Ticker.h>

#include "BuSw.h"
#include "Counter.h"
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
int menuicons[2][5] =
    {{184, 93, 124, 129, 209},
     {240, 92, 240, 141, 235}};
/////////////////////////////////////////

// 设置图标
/////////////////////////////////////////
int settingsicons[1][5] = {247, 94, 123, 188, 65};
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
  pinMode(X, INPUT);         // x
  pinMode(Y, INPUT);         // y
  attachInterrupt(digitalPinToInterrupt(BU), button, FALLING);
  attachInterrupt(digitalPinToInterrupt(SW), joysw, FALLING);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 0);
  setCpuFrequencyMhz(80);
  esp_timer.attach(1.0, clccal);
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
  if (Switch.pressed)
  {
    Button.pressed = 0;
    Switch.pressed = 0;
    menu();
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_tf);
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
    if (a >= 5 || a <= -1)
    {
      a = (a + 5) % 5;
      b += 1;
    }
    b = (b + 2) % 2;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(7, 24, menuicons[b][0]);
    u8g2.drawGlyph(30, 24, menuicons[b][1]);
    u8g2.drawGlyph(53, 24, menuicons[b][2]);
    u8g2.drawGlyph(76, 24, menuicons[b][3]);
    u8g2.drawGlyph(99, 24, menuicons[b][4]);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.drawRFrame(4 + 23 * (a % 5), 6, 22, 20, 3);
    u8g2.sendBuffer();
    c = b * 5 + (a + 1);
    Serial.println(Button.pressed);
    if (Switch.pressed)
    {
      Switch.pressed = 0;
      Button.pressed = 0;
      switch (c)
      {
      case 1:
        a = b = d = 0;
        break;
      case 2:
        timerset();
        break;
      case 3:
        weather();
        break;
      case 4:
        settings();
        break;
      case 5:
        gps();
        break;
      case 7:
        lab();
        break;
      case 9:
        manager();
        break;
      case 10:
        power();
        break;
      default:
        building();
      }
    }
  }
  Button.pressed = 0;
  Switch.pressed = 0;
}
/////////////////////////////////////////

// 设置
/////////////////////////////////////////
void settings()
{
  static int a = 0, b = 0, c = 0;
  int d = 1;
  while (d)
  {
    joystick(&a, &b);
    if (a >= 5 || a <= -1)
    {
      a = (a + 5) % 5;
      // b += 1;
    }
    // b = (b + H_I) % H_I;
    b = 0;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(7, 24, settingsicons[0][0]);
    u8g2.drawGlyph(30, 24, settingsicons[0][1]);
    u8g2.drawGlyph(53, 24, settingsicons[0][2]);
    u8g2.drawGlyph(76, 24, settingsicons[0][3]);
    u8g2.drawGlyph(99, 24, settingsicons[0][4]);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.drawRFrame(4 + 23 * (a % 5), 6, 22, 20, 3);
    u8g2.sendBuffer();
    c = b * 5 + (a + 1);
    if (Switch.pressed)
    {
      Button.pressed = 0;
      Switch.pressed = 0;
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
      case 5:
        a = b = d = 0;
        break;
      default:
        building();
      }
    }
  }
  Button.pressed = 0;
  Switch.pressed = 0;
}
/////////////////////////////////////////

// 测试
/////////////////////////////////////////
void lab()
{
  setCpuFrequencyMhz(240);
  while (!Button.pressed)
  {
    // Switch.pressed = 0;
    // Button.pressed = 0;
    Serial.println(Button.pressed);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(0, 14);
    u8g2.printf("X-%04d", analogRead(X));
    u8g2.setCursor(0, 30);
    u8g2.printf("Y-%04d", analogRead(Y));
    /*u8g2.setCursor(56, 22);
    u8g2.printf("SW-%04d", analogRead(SW));
    u8g2.setCursor(56, 14);
     u8g2.printf("BU-%04d", analogRead(BU));
     u8g2.setCursor(56, 30);
     u8g2.printf("SW-%04d", analogRead(SW));*/
    u8g2.sendBuffer();
   }
  Serial.println(Button.pressed);
  Switch.pressed = 0;
  Button.pressed = 0;
  setCpuFrequencyMhz(80);
  // analogWrite(2, 0);
}
/////////////////////////////////////////

// 关于
/////////////////////////////////////////
void esp_info()
{
  while (!Button.pressed)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(13, 9);
    u8g2.printf("Built on ESP Tech.");
    u8g2.setCursor(4, 20);
    u8g2.printf("Designed by ESP6109.");
    u8g2.setCursor(25, 31);
    u8g2.printf("Version 4.0.5");
    u8g2.sendBuffer();
  }
  Switch.pressed = 0;
  Button.pressed = 0;
}
/////////////////////////////////////////

// BUILDING
/////////////////////////////////////////
void building()
{
  while (!(/*joysw() || */ Button.pressed))
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(53, 24, 282);
    u8g2.sendBuffer();
  }
  Switch.pressed = 0;
  Button.pressed = 0;
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
    // u8g2.setFont(u8g2_font_wqy16_t_gb2312);
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
  s_shot();
  Switch.pressed = 0;
  Button.pressed = 0;
}
/////////////////////////////////////////

// 电源选项
/////////////////////////////////////////
void power()
{
  static int a = 0, b = 0, c = 0;
  int d = 1;
  while (d)
  {
    joystick(&a, &b);
    if (a >= 5 || a <= -1)
    {
      a = (a + 5) % 5;
    }
    // b = (b + H_I) % H_I;
    b = 0;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(7, 24, powericons[0][0]);
    u8g2.drawGlyph(30, 24, powericons[0][1]);
    u8g2.drawGlyph(53, 24, powericons[0][2]);
    u8g2.drawGlyph(76, 24, powericons[0][3]);
    u8g2.drawGlyph(99, 24, powericons[0][4]);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.drawRFrame(4 + 23 * (a % 5), 6, 22, 20, 3);
    /*u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    u8g2.setCursor(117, 8);
    u8g2.printf("%d", a + 1);*/
    u8g2.sendBuffer();
    c = b * 5 + (a + 1);
    if (Switch.pressed)
    {
      Switch.pressed = 0;
      switch (c)
      {
      case 1:
        shutdown();
        break;
      case 2:
        restart();
        break;
      case 3:
        building();
        break;
      case 5:
        a = b = d = 0;
        break;
      default:
        building();
      }
    }
  }
}
/////////////////////////////////////////

