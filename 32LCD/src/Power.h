#ifndef Power_h
#define Power_h

#include <Arduino.h>
#include "esp_system.h"
#include "esp_sleep.h"
#include "LCD.h"

// 电源图标
/////////////////////////////////////////
int powericons[2] = {235, 243};
/////////////////////////////////////////

void power(int i);

// 电源
/////////////////////////////////////////
void power(int i)
{
  icon(53, 24, powericons[i]);
  delay(500);
  clearscr();
  if (i)
    esp_restart();
  else
    esp_deep_sleep_start();
}
/////////////////////////////////////////

#endif
/*
void restart();
void shutdown();
// 重置
/////////////////////////////////////////
void restart()
{
  icon(53, 24, powericons[1]);
  delay(500);
  clearscr();
  esp_restart();
}
/////////////////////////////////////////

// 休眠
/////////////////////////////////////////
void shutdown()
{
  icon(53, 24, powericons[0]);
  delay(500);
  clearscr();
  esp_deep_sleep_start();
}
/////////////////////////////////////////
*/
