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
void icon(int, int, int);
void list2(int, int);
void list3(int, int);
void list4(int, int);
void list5(int, int);

// 清屏
/////////////////////////////////////////
void clearscr()
{
  u8g2.clearBuffer();
  u8g2.drawBox(0, 0, 122, 32);
  u8g2.sendBuffer();
  delay(10);
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
/////////////////////////////////////////

// 图标
/////////////////////////////////////////
void icon(int x, int y, int c)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(x, y, c);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2(int a, int ics[])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(23, 24, ics[0]);
  u8g2.drawGlyph(83, 24, ics[1]);
  u8g2.drawRFrame(20 + 60 * (a % 2), 6, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list3(int a, int ics[])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(13, 24, ics[0]);
  u8g2.drawGlyph(53, 24, ics[1]);
  u8g2.drawGlyph(93, 24, ics[2]);
  u8g2.drawRFrame(10 + 40 * (a % 3), 6, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list4(int a, int ics[])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(8, 24, ics[0]);
  u8g2.drawGlyph(38, 24, ics[1]);
  u8g2.drawGlyph(68, 24, ics[2]);
  u8g2.drawGlyph(98, 24, ics[3]);
  u8g2.drawRFrame(5 + 30 * (a % 4), 6, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list5(int a, int ics[])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(7, 24, ics[0]);
  u8g2.drawGlyph(30, 24, ics[1]);
  u8g2.drawGlyph(53, 24, ics[2]);
  u8g2.drawGlyph(76, 24, ics[3]);
  u8g2.drawGlyph(99, 24, ics[4]);
  u8g2.drawRFrame(4 + 23 * (a % 5), 6, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

#endif