#ifndef Power_h
#define Power_h

#include <Arduino.h>
#include "esp_system.h"
#include "esp_sleep.h"
#include "LCD.h"

// 电源图标
/////////////////////////////////////////
int powericons[1][5] = {235, 243, 223, 240, 65};
/////////////////////////////////////////

void restart();
void shutdown();

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

// 休眠
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

#endif