#include "Power.h"

// 电源图标
/////////////////////////////////////////
int powericons[2] = {23, 26};
/////////////////////////////////////////

// 电源
/////////////////////////////////////////
void power(int i)
{
  u8g2.clearBuffer();
  u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[powericons[i]]);
  u8g2.sendBuffer();
  delay(500);
  clearscr();
  if (i)
    esp_restart();
  else
    esp_deep_sleep_start();
}
/////////////////////////////////////////

