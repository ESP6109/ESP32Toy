#ifndef LCD_h
#define LCD_h

#include <U8g2lib.h>

// LCD12232接口
/////////////////////////////////////////
#define EN 5
#define RW 18
#define RS 19
U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, EN, RW, RS, U8X8_PIN_NONE);
// U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, 5, 18, 19, U8X8_PIN_NONE);
/////////////////////////////////////////

void clearscr();

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

#endif