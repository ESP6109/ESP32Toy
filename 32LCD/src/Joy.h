#ifndef Joy_h
#define Joy_h

#include "LCD.h"

void s_box();
void s_shot();

// 界面1
/////////////////////////////////////////
void s_box()
{
  int i, j;
  for (i = 1; i <= 7; ++i)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setCursor(23, 14);
    u8g2.printf("ESP Tech.");
    for (j = -2; j <= i; ++j)
      u8g2.drawBox(-13 + 17 * j, 18, 12, 14);
    u8g2.sendBuffer();
    delay(100);
  }
}
/////////////////////////////////////////

// 界面2
/////////////////////////////////////////
void s_shot()
{
  int i = 45, j = 0;
  // u8g2.setFont(u8g2_font_wqy12_t_chinese1);
  u8g2.setFontDirection(0);
  while (i <= 152)
  {
    u8g2.clearBuffer();
    /*u8g2.setCursor(70, 9);
    u8g2.printf("PENIS");
    u8g2.setCursor(65, 32);
    u8g2.printf("CUMING");*/
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
}
/////////////////////////////////////////

#endif