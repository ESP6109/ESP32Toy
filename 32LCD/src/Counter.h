#ifndef Counter_h
#define Counter_h

#include <Arduino.h>
#include "LCD.h"
#include "BuSw.h"
#include "Joystick.h"
// #include "DaTi.h"

// 定时器
/////////////////////////////////////////
bool reset = 0; // 定时器重置
bool r = 1;     // 蜂鸣器
/////////////////////////////////////////

// 蜂鸣器接口
/////////////////////////////////////////
#define Beep 33
/////////////////////////////////////////

void timerset();
int count(int, int, int);
void cpause();
void ring(int);
void timer();

// 定时器设置
/////////////////////////////////////////
void timerset()
{
  int h = 0, m = 0, s = 0;
  int a = 0, b = 0;
  while (!Button.pressed)
  {
    Button.pressed = 0;
    Switch.pressed = 0;
    // joystick(&a, &b);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso16_tr);
    switch (a)
    {
    case 0:
      joystick(&a, &h);
      h = (h + 100) % 100;
      u8g2.drawRBox(24, 6, 22, 20, 1);
      u8g2.setCursor(25, 24);
      u8g2.setDrawColor(0);
      u8g2.printf("%02d", h);
      u8g2.setDrawColor(1);
      u8g2.setCursor(51, 24);
      u8g2.printf("%02d", m);
      u8g2.setCursor(77, 24);
      u8g2.printf("%02d", s);
      break;
    case 1:
      joystick(&a, &m);
      m = (m + 60) % 60;
      u8g2.setCursor(25, 24);
      u8g2.printf("%02d", h);
      u8g2.drawRBox(50, 6, 22, 20, 1);
      u8g2.setCursor(51, 24);
      u8g2.setDrawColor(0);
      u8g2.printf("%02d", m);
      u8g2.setDrawColor(1);
      u8g2.setCursor(77, 24);
      u8g2.printf("%02d", s);
      break;
    case 2:
      joystick(&a, &s);
      s = (s + 60) % 60;
      u8g2.setCursor(25, 24);
      u8g2.printf("%02d", h);
      u8g2.setCursor(51, 24);
      u8g2.printf("%02d", m);
      u8g2.drawRBox(76, 6, 22, 20, 1);
      u8g2.setCursor(77, 24);
      u8g2.setDrawColor(0);
      u8g2.printf("%02d", s);
      u8g2.setDrawColor(1);
      break;
    default:
      joystick(&a, NULL);
    }
    a = (a + 3) % 3;
    u8g2.setCursor(45, 24);
    u8g2.printf(":");
    u8g2.setCursor(71, 24);
    u8g2.printf(":");
    u8g2.sendBuffer();
    if (Switch.pressed && !(h == 0 && m == 0 && s == 0))
    {
      Button.pressed = 0;
      Switch.pressed = 0;
      count(h, m, s);
      // a++;
    }
    if (reset)
    {
      reset = 0;
      h = m = s = 0;
      a = 0;
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
      u8g2.setFont(u8g2_font_logisoso16_tr);
      u8g2.setCursor(25, 24);
      u8g2.printf("%02d:%02d:%02d", h_c, m_c, s_c);
      u8g2.sendBuffer();
    }
    else
    {
      Button.pressed = 0;
      Switch.pressed = 0;
      cpause();
    }
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
      Button.pressed = 0;
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
    Button.pressed = 0;
    Switch.pressed = 0;
    u8g2.sendBuffer();
  }

  Button.pressed = 0;
  Switch.pressed = 0;
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

// 计时器
/////////////////////////////////////////
void timer()
{
  ;
  /*analogWrite(33, 0);
  analogWrite(25, 0);*/
}
/////////////////////////////////////////

#endif

/*u8g2.drawBox(29 + 23 * a, 4, 17, 4);
u8g2.drawBox(29 + 23 * a, 22, 17, 4);
u8g2.setCursor(30, 30);
u8g2.printf("%02d:%02d:%02d", h, m, s);
u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
u8g2.setCursor(0, 8);
u8g2.printf("%d", a + 1);*/

/*
u8g2.setFont(u8g2_font_logisoso16_tr);
u8g2.setCursor(25, 16);
u8g2.printf("%02d:%02d:%02d", h, m, s);
u8g2.setCursor(51, 32);
u8g2.printf("00");
u8g2.setCursor(77, 32);
u8g2.printf("00");*/