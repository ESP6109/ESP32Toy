// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 3.5.0
// Building
// Release at 2025.09.19 23:00
#include <Arduino.h>
#include <u8g2lib.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "esp32-hal-cpu.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include <driver/gpio.h>
#include <Ticker.h>
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// LCD12232接口
/////////////////////////////////////////
#define E 5
#define RW 18
#define RS 19
U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, E, RW, RS, U8X8_PIN_NONE);
// U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, 5, 18, 19, U8X8_PIN_NONE);
/////////////////////////////////////////

// 摇杆按键接口
/////////////////////////////////////////
#define BU 0
//(0,0)
//              (4095,4095)
// GND
// 5V(3.3V)
#define X 26
#define Y 14
#define SW 13
struct Key
{
  const uint8_t Pin;
  bool pressed;
};
Key Button = {BU, 0};
Key Switch = {SW, 0};
unsigned long ST1 = 0, ST2 = 0;
unsigned long BT1 = 0, BT2 = 0;
/////////////////////////////////////////

// GPS接口
/////////////////////////////////////////
// Serial2
#define TX 17
#define RX 16
/////////////////////////////////////////

// 蜂鸣器接口
/////////////////////////////////////////
#define Beep 33
/////////////////////////////////////////

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

// 天气图标
/////////////////////////////////////////
int weathericons[4] = {259, 127, 124, 241}; // 晴 阴 云 雨
/////////////////////////////////////////

// 电源图标
/////////////////////////////////////////
int powericons[1][5] = {235, 243, 223, 240, 65};
/////////////////////////////////////////

// 日期与时间
/////////////////////////////////////////
int Yea = 1970, Mon = 1, Day = 1; // 年月日
int Hou = 8, Min = 0, Sec = 0;    // 时分秒
int Wee = 1;                      // 星期
Ticker esp_timer;                 // 时钟计时
int timer1, timer2;               // 摇杆计时
bool G_t = 0;                     // 接入卫星时间
bool reset = 0;                   // 定时器重置
bool r = 1;                       // 蜂鸣器
/////////////////////////////////////////

// 温湿度
/////////////////////////////////////////
int Tem = 0, Hum = 0;
int MaxT = 0, MinT = 0;
/////////////////////////////////////////

// 定位模块
/////////////////////////////////////////
TinyGPSPlus GPS;
TinyGPSCustom A(GPS, "GPRMC", 2);  // 有效值
TinyGPSCustom NS(GPS, "GPRMC", 4); // 南北
TinyGPSCustom WE(GPS, "GPRMC", 6); // 东西
float Lng = 0, Lat = 0;            // 经纬
int Spe = 0;                       // 速度
int Cou = 0;                       // 方向角
char Ava[2];                       // 有效值
/////////////////////////////////////////

// 定义
/////////////////////////////////////////
// int button();
// int joysw();
void IRAM_ATTR button();
void IRAM_ATTR joysw();
void clearscr();
void joystick(int *, int *);
void home();
void menu();
void clccal();
void timer();
void timerset();
int count(int, int, int);
void cpause();
void ring(int);
void weather();
void settings();
void lab();
void gps();
void gpsget();
void gpsdisplay(int);
void clksets();
void esp_info();
void building();
void manager();
void s_box();
void s_shot();
void power();
void restart();
void shutdown();
// void test();
/////////////////////////////////////////

// 日历与时钟
/////////////////////////////////////////
void clccal()
{
  timer();
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

// 计时器
/////////////////////////////////////////
void timer()
{
  ;
  /*analogWrite(33, 0);
  analogWrite(25, 0);*/
}
/////////////////////////////////////////

// 按键IO0
/////////////////////////////////////////
void IRAM_ATTR button()
{
  BT1 = millis();
  if (BT1 - BT2 > 250)
  {
    Button.pressed = 1;
    BT2 = BT1;
  }
}
/////////////////////////////////////////

// 按键SW
/////////////////////////////////////////
void IRAM_ATTR joysw()
{
  ST1 = millis();
  if (ST1 - ST2 > 250)
  {
    Switch.pressed = 1;
    ST2 = ST1;
  }
}
/////////////////////////////////////////

// 初始化
/////////////////////////////////////////
void setup()
{
  u8g2.begin();
  Serial.begin(115200);
  Serial2.begin(9600);
  u8g2.enableUTF8Print();
  // test();
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
  // clearscr();
  // manager();
}
/////////////////////////////////////////

// 清屏
/////////////////////////////////////////
void clearscr()
{
  u8g2.clearBuffer();
  u8g2.drawBox(0, 0, 122, 32);
  u8g2.sendBuffer();
  delay(100);
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
/////////////////////////////////////////

// 摇杆
/////////////////////////////////////////
void joystick(int *C_x, int *C_y)
{
  int VRX = analogRead(X);
  int VRY = analogRead(Y);
  // int VSW = analogRead(SW);//!!!!
  if (millis() - timer1 >= 250)
  {
    if (VRX >= 2870)
      (*C_x)++;
    else if (VRX <= 890)
      (*C_x)--;
    if (VRY >= 2870)
      (*C_y)++;
    else if (VRY <= 890)
      (*C_y)--;
    timer1 = millis();
  }
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
  if (/*Button.pressed  ||()*/ Switch.pressed)
  {
    // Serial.println(Button.pressed);
    Button.pressed = 0;
    Switch.pressed = 0;
    menu();
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.setCursor(14, 14);
  u8g2.printf("%04d.%02d.%02d %d\n", Yea, Mon, Day, Wee);
  u8g2.setCursor(29, 30);
  u8g2.printf("%02d:%02d:%02d\n", Hou, Min, Sec);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

// 主菜单
/////////////////////////////////////////
void menu()
{
  // Switch.pressed = 0;
  // Serial.printf("Menu\n");
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
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    u8g2.setCursor(117, 8);
    u8g2.printf("%d", a + 1);
    u8g2.sendBuffer();
    c = b * 5 + (a + 1);
    Serial.println(Button.pressed);
    if (Switch.pressed /*joysw() ||button() Button.pressed*/)
    {
      // Serial.println(Button.pressed);
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
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    u8g2.setCursor(117, 8);
    u8g2.printf("%d", a + 1);
    u8g2.sendBuffer();
    c = b * 5 + (a + 1);
    if (/*joysw button() Button.pressed*/ Switch.pressed)
    {
      Button.pressed = 0;
      Switch.pressed = 0;
      switch (c)
      {
      case 3:
        clksets();
        break;
      case 4:
        esp_info();
        break;
      case 5:
        a = b = d = 0;
        break;
      case 10:
        power();
        break;
      default:
        building();
      }
    }
    // Serial.printf("%d %d \n", button(), joysw());
  }
}
/////////////////////////////////////////

// 定时器设置
/////////////////////////////////////////
void timerset()
{
  int h = 0, m = 0, s = 0;
  int a = 0, b = 0;
  while (!Button.pressed)
  {
    // joystick(&a, &b);
    u8g2.clearBuffer();
    switch (a)
    {
    case 0:
      joystick(&a, &h);
      h = (h + 100) % 100;
      break;
    case 1:
      joystick(&a, &m);
      m = (m + 60) % 60;
      break;
    case 2:
      joystick(&a, &s);
      s = (s + 60) % 60;
      break;
    default:
      joystick(&a, NULL);
    }
    a = (a + 3) % 3;
    if (a < 2)
    {
      u8g2.drawBox(29 + 23 * a, 4, 17, 4);
      u8g2.drawBox(29 + 23 * a, 22, 17, 4);
    }
    else
      u8g2.drawBox(0, 22, 22, 4);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(29, 21);
    u8g2.printf("%02d:%02d:%02d", h, m, s);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", a + 1);
    /*u8g2.setCursor(117, 8);
    u8g2.printf("%d", a)
    button()*/
    u8g2.sendBuffer();
    if (/*a == 3 && */ Switch.pressed && !(h == 0 && m == 0 && s == 0))
    {
      Button.pressed = 0;
      Switch.pressed = 0;
      count(h, m, s);
      a++;
    }
    if (reset)
    {
      reset = 0;
      h = m = s = 0;
    }
  }
  Switch.pressed = 0;
  Button.pressed = 0;
}
/////////////////////////////////////////

// 倒计时
/////////////////////////////////////////
int count(int h_c, int m_c, int s_c)
{
  int c = 1, t = 0;
  while (h_c != 0 || m_c != 0 || s_c != 0 && c)
  {
    if (reset)
    {
      return 0;
    }
    if (!(Button.pressed || Switch.pressed))
    {

      Button.pressed = 0;
      Switch.pressed = 0;
      s_c -= 1;
      if (s_c < 0)
      {
        m_c--;
        s_c += 60;
      }
      if (m_c < 0)
      {
        h_c--;
        m_c += 60;
      }
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_helvB12_tf);
      u8g2.setCursor(29, 21);
      u8g2.printf("%02d:%02d:%02d", h_c, m_c, s_c);
      u8g2.sendBuffer();
    }
    else
      cpause();
  }
  Button.pressed = 0;
  Switch.pressed = 0;
  if (!reset)
    ring(1);
  return 0;
}
/////////////////////////////////////////

// 计时器暂停
/////////////////////////////////////////
void cpause()
{
  int a = 0, b = 0, c = 1;
  while (c && !reset)
  {
    joystick(NULL, &b);
    b = (b + 2) % 2;
    u8g2.clearBuffer();
    u8g2.drawBox(37, 3 + 15 * b, 11, 11);
    u8g2.drawBox(75, 3 + 15 * b, 11, 11);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(50, 13);
    u8g2.printf("继续");
    u8g2.setCursor(50, 28);
    u8g2.printf("重置");
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    if (Button.pressed)
    {
      Button.pressed =0;
      c = 0;
      reset = 1;
    }
    else if (Switch.pressed)
    {
      Switch.pressed = 0;
      switch (b)
      {
      case 0:
        c = 0;
        break;
      case 1:
        c = 0;
        reset = 1;
        break;
      }
    }
    u8g2.sendBuffer();
  }
}
/////////////////////////////////////////

// 蜂鸣器响铃
/////////////////////////////////////////
void ring(int b)
{
  int i = 0, t = 0, a = 0;
  while (!(Button.pressed || Switch.pressed) && b)
  {

    /*analogWrite(33, 255);
    analogWrite(25, 255);*/
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(53, 24, 93);
    u8g2.sendBuffer();
    if (a < 6)
    {
      if (millis() - t >= 100)
      {
        i = !i;
        digitalWrite(Beep, i);
        digitalWrite(2, i);
        t = millis();
        ++a;
      }
    }
    else if (a >= 6 && a <= 10)
    {
      digitalWrite(Beep, 0);
      digitalWrite(2, 0);
      if (millis() - t >= 100)
      {

        t = millis();
        ++a;
        a %= 10;
      }
    }
    Serial.println(a);
  }
  digitalWrite(Beep, 0);
  digitalWrite(2, 0);
  Button.pressed = 0;
  Switch.pressed = 0;
}
/////////////////////////////////////////

// 天气
//
void weather()
{
  int i = 0;
  //
  while (!Button.pressed)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_all_4x_t); // 设定字体
    u8g2.drawGlyph(45, 32, weathericons[i]);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(0, 14);
    u8g2.printf("-%02d°C", MinT);
    u8g2.setCursor(0, 30);
    u8g2.printf("-%02d°C", MaxT);
    u8g2.setCursor(80, 14);
    u8g2.printf("-%02d°C", Tem);
    u8g2.setCursor(88, 30);
    u8g2.printf("%02d", Hum);
    u8g2.drawUTF8(108, 30, "%");
    u8g2.sendBuffer();
  }
  Switch.pressed = 0;
  Button.pressed = 0;
}
//

// 定位
/////////////////////////////////////////
void gps()
{
  int i = 0;
  int a = 0, b = 0;
  setCpuFrequencyMhz(240);
  while (!Button.pressed)
  {
    while (Serial2.available())
    {
      GPS.encode(Serial2.read());
      // Serial.printf("%c",Serial2.read());
    }
    Serial.printf("\n");
    joystick(&a, &b);
    a = a + 4;
    a %= 4;
    /*while (joysw())
    {
      i++;
      i %= 4;
    }*/
    strcpy(Ava, A.value());
    // digitalWrite(2, 1);
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
    gpsget();
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
  Yea = GPS.date.year();    // 年
  Mon = GPS.date.month();   // 月
  Day = GPS.date.day();     // 日
  Hou = GPS.time.hour();    // 时
  Min = GPS.time.minute();  // 分
  Sec = GPS.time.second();  // 秒
  Lng = GPS.location.lng(); // 经度
  Lat = GPS.location.lat(); // 纬度
  Spe = GPS.speed.kmph();   // 速度
  Cou = GPS.course.deg();   // 方向角
  Hou += 8;
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
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(0, 14);
    u8g2.printf("%02d.%02d.%02d  %d  %3d\n", (Yea % 100), Mon, Day, Wee, Spe);
    u8g2.setCursor(0, 30);
    u8g2.printf("%02d:%02d %3d %3d\n", Hou, Min, int(Lat), int(Lng));
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(14, 14);
    u8g2.printf("%4d.%02d.%02d %d\n", Yea, Mon, Day, Wee);
    u8g2.setCursor(29, 30);
    u8g2.printf("%02d:%02d:%02d\n", Hou, Min, Sec);
    u8g2.sendBuffer();
    break;
  }
  case 2:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(0, 14);
    u8g2.printf("%2d%f\n", (int(Lat) / 10), (Lat - int(Lat) / 10 * 10));
    u8g2.setCursor(100, 14);
    u8g2.printf("%s", NS.value());
    u8g2.setCursor(0, 30);
    u8g2.printf("%2d%f\n", (int(Lng) / 10), (Lng - int(Lng) / 10 * 10));
    u8g2.setCursor(100, 30);
    u8g2.printf("%s", WE.value());
    u8g2.sendBuffer();
    break;
  }
  case 3:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    if ((Cou > 338 && Cou < 360) || (Cou >= 0 && Cou < 22)) // N
    {

      u8g2.setCursor(0, 30);
      u8g2.printf("N");
    }
    else if (Cou >= 22 && Cou <= 68) // NE
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("NE");
    }
    else if (Cou > 68 && Cou < 112) // E
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("E");
    }
    else if (Cou >= 112 && Cou <= 158) // SE
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("SE");
    }
    else if (Cou > 158 && Cou < 202) // S
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("S");
    }
    else if (Cou >= 202 && Cou <= 248) // SW
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("SW");
    }
    else if (Cou > 248 && Cou < 292) // W
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("W");
    }
    if (Cou >= 292 && Cou <= 338) // NW
    {
      u8g2.setCursor(0, 30);
      u8g2.printf("NW");
    }
    u8g2.setCursor(0, 14);
    u8g2.printf("%d\n", Cou);
    u8g2.setFont(u8g2_font_logisoso32_tn);
    u8g2.setCursor(64, 32);
    u8g2.printf("%03d\n", Spe);
    u8g2.sendBuffer();
    break;
  }
  }
}
/////////////////////////////////////////

// 测试
/////////////////////////////////////////
void lab()
{
  setCpuFrequencyMhz(240);
  while (!Button.pressed /* || !Switch.pressed !joysw()*/)
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
    /*if (analogRead(SW) == 0)
      analogWrite(2, 255);
    else
      analogWrite(2, 0);*/
    // Serial.printf("%d,%d\n", analogRead(BU), analogRead(SW));
  }
  Serial.println(Button.pressed);
  Switch.pressed = 0;
  Button.pressed = 0;
  setCpuFrequencyMhz(80);
  // analogWrite(2, 0);
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
    u8g2.printf("Version 3.5.0");
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

// 界面1
/////////////////////////////////////////
void s_box()
{
  int i, j;
  for (i = 1; i <= 7; ++i)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(13, 10);
    u8g2.printf("Built on ESP Tech.");
    for (j = -2; j <= i; ++j)
      u8g2.drawBox(-13 + 17 * j, 18, 12, 14);
    u8g2.sendBuffer();
    delay(100);
  }
  clearscr();
}
/////////////////////////////////////////

// 界面2
/////////////////////////////////////////
void s_shot()
{
  clearscr();
  int i = 45, j = 0;
  u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
  u8g2.setFontDirection(0);
  while (i <= 152)
  {
    u8g2.clearBuffer();
    u8g2.setCursor(70, 9);
    u8g2.printf("PENIS");
    u8g2.setCursor(65, 32);
    u8g2.printf("CUMING");
    u8g2.drawDisc(8, 8, 8, U8G2_DRAW_ALL);
    u8g2.drawDisc(8, 23, 8, U8G2_DRAW_ALL);
    u8g2.drawBox(3, 10, 45, 14);
    u8g2.drawFilledEllipse(45, 16, 8, 9);
    u8g2.drawDisc(i, 16, 3, U8G2_DRAW_ALL);
    u8g2.drawDisc(i - 25, 16, 3, U8G2_DRAW_ALL);
    if (i >= 90)
    {
      u8g2.drawDisc(i - 50, 16, 3, U8G2_DRAW_ALL);
      u8g2.drawDisc(i - 75, 16, 3, U8G2_DRAW_ALL);
    }
    i += 2;
    /*if (i == 143)
      i -= 24;
    else
    if (button())
      break;*/
    u8g2.sendBuffer();
  }
  clearscr();
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
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", b + 1);
    u8g2.setCursor(117, 8);
    u8g2.printf("%d", a + 1);
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

// 重置
/////////////////////////////////////////
void restart()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(53, 24, powericons[0][1]);
  u8g2.sendBuffer();
  delay(750);
  clearscr();
  esp_restart();
}
/////////////////////////////////////////

// 关机
/////////////////////////////////////////
void shutdown()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(53, 24, powericons[0][0]);
  u8g2.sendBuffer();
  delay(750);
  clearscr();
  esp_deep_sleep_start();
}
/////////////////////////////////////////

/*u8g2.clearBuffer();
u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
u8g2.drawGlyph(53, 24, 0);
u8g2.sendBuffer();*/
// esp_sleep_enable_timer_wakeup(1000000 * 15); // 5分钟后唤醒
/*int i = 64, j = 4;
void lcd();
void lcd()
{

  while (i < 280)
  {
    ++i;
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 30);
    u8g2.printf("%2d", i);
    u8g2.sendBuffer();
    break;
  }
  if (i <= 280)
  {
    u8g2.clearBuffer();
    // u8g2.setFont(u8g2_font_siji_t_6x10);
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(7, 24, i);
    u8g2.drawGlyph(30, 24, i + 1);
    u8g2.drawGlyph(53, 24, i + 2);
    u8g2.drawGlyph(76, 24, i + 3);
    u8g2.drawGlyph(99, 24, i + 4);
    u8g2.drawRFrame(j, 6, 22, 20, 3);
    u8g2.setFontDirection(0);
    j += 23;
    if (j >= 119)
    {
      j = 4;
      i += 5;
    }
    if (i >= 280)
      i = 64;

    // digitalWrite(2, j % 2);
  }

  delay(750);
}*/

// void drawicon(int, int, int);
// 图标
/////////////////////////////////////////
/*void drawicon(int x, int y, int a)
{
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t); // 设定字体
  u8g2.clearBuffer();
  u8g2.drawGlyph(x, y, a);
  u8g2.sendBuffer();
}*/

/*
 */
/*int h = 0, mi = 0, s = 0; // 时分秒
char h_str[3], mi_str[3], s_str[3];
int y = 0, mo = 0, d = 0; // 年月日
char y_str[5], mo_str[3], d_str[3];
int week = 0; // 星期
char week_str[2];*/
/*u8g2.clearBuffer();
u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
u8g2.drawGlyph(53, 24, 184);
u8g2.sendBuffer();*/
/*strcpy(s_str, u8x8_u8toa(s, 2));
strcpy(mi_str, u8x8_u8toa(mi, 2));
strcpy(h_str, u8x8_u8toa(h, 2));
strcpy(y_str, u8x8_u8toa(y, 4));
strcpy(mo_str, u8x8_u8toa(mo, 2));
strcpy(d_str, u8x8_u8toa(d, 2));
strcpy(week_str, u8x8_u8toa(week, 1));
// week[0] = 65;
Serial.println(week);
u8g2.clearBuffer();
u8g2.setFont(u8g2_font_logisoso16_tn);
u8g2.firstPage();
do
{
  // u8g2.drawStr(24, 16, y_str);
  // u8g2.drawStr(49, 16, ".");
  u8g2.drawStr(20, 16, mo_str);
  u8g2.drawStr(48, 16, ".");
  u8g2.drawStr(60, 16, d_str);
  u8g2.drawStr(100, 16, week_str);

  u8g2.drawStr(0, 32, h_str);
  u8g2.drawStr(28, 32, ":");
  u8g2.drawStr(40, 32, mi_str);
  u8g2.drawStr(68, 32, ":");
  u8g2.drawStr(80, 32, s_str);
  // Serial.printf("%s",y_str);
} while (u8g2.nextPage());*/

/*
void cpause(int *, int *, int *);
void cpause(int *h, int *m, int *s)
{
  int a = 0;
  while (!button())
  {
    u8g2.clearBuffer();
    switch (a)
    {
    case 0:
      joystick(&a, &*h);
      *h = (*h + 100) % 100;
      break;
    case 1:
      joystick(&a, &*m);
      *m = (*m + 60) % 60;
      break;
    case 2:
      joystick(&a, &*s);
      *s = (*s + 60) % 60;
      break;
    }
    a = (a + 3) % 3;
    u8g2.drawBox(29 + 23 * a, 4, 17, 4);
    u8g2.drawBox(29 + 23 * a, 22, 17, 4);
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(29, 21);
    u8g2.printf("%02d:%02d:%02d", *h, *m, *s);
    u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
    u8g2.setCursor(0, 8);
    u8g2.printf("%d", a + 1);
    u8g2.sendBuffer();
  }
}
*/

/*u8g2.clearBuffer();
u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
u8g2.setCursor(30, 19);
u8g2.printf("WIFI 卫星");
u8g2.setCursor(90, 30);
u8g2.printf("返回");*/

/*#define H_I 2
#define W_I 5*/
/*  lab();
     gps();settings();power();*/
/*int button()
{
static bool bu_st = 1;
delay(5);
if (digitalRead(BU) && !bu_st)
{
bu_st = digitalRead(BU);
return 1;
}
else
{
bu_st = digitalRead(BU);
return 0;
}
}*/
/*int joysw()
{

  static bool sw_st = 1;
  // static int a = 0;
  // Serial.println(analogRead(13));
  delay(5);
  if (digitalRead(SW) && !sw_st)
  {
    // digitalWrite(2, 0);
    // ++a;
    sw_st = 1;
    // Serial.println(a);
    return 1;
  }
  else // if (!digitalRead(SW) || !sw_st)
  {
    sw_st = digitalRead(SW);
    // digitalWrite(2, 1);
    return 0;
  }
}*/

/*gpio_pad_select_gpio(GPIO_NUM_0);
gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);
gpio_set_pull_mode(GPIO_NUM_0, GPIO_PULLUP_ONLY);
gpio_pad_select_gpio(GPIO_NUM_13);
gpio_set_direction(GPIO_NUM_13, GPIO_MODE_INPUT);
gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLUP_ONLY);*/
// test();
// Serial.printf("Home\n");
// if (joysw() || button())
// menu();
// power();
/*u8g2.clearBuffer();
u8g2.setFont(u8g2_font_helvB12_tf);
u8g2.setCursor(14, 14);
u8g2.printf("%04d.%02d.%02d %d\n", Yea, Mon, Day, Wee);
u8g2.setCursor(29, 30);
u8g2.printf("%02d:%02d:%02d\n", Hou, Min, Sec);
u8g2.sendBuffer();*/