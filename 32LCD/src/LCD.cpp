#include "LCD.h"

// 清屏
/////////////////////////////////////////
void clearscr()
{
  u8g2.clearBuffer();
  u8g2.drawBox(0, 0, 128, 64);
  u8g2.sendBuffer();
  delay(5);
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
void list1x2(int a, int ics[])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(24, 40, ics[0]);
  u8g2.drawGlyph(88, 40, ics[1]);
  u8g2.drawRFrame(21 + 64 * (a % 2), 22, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x2(int a, int ics[][2])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(24, 24, ics[0][0]);
  u8g2.drawGlyph(88, 24, ics[0][1]);
  u8g2.drawGlyph(24, 56, ics[1][0]);
  u8g2.drawGlyph(88, 56, ics[1][1]);
  u8g2.drawRFrame(21 + 64 * (a % 2), 6+ (a / 2) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x3(int a, int ics[][3])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(13, 24, ics[0][0]);
  u8g2.drawGlyph(56, 24, ics[0][1]);
  u8g2.drawGlyph(99, 24, ics[0][2]);
  u8g2.drawGlyph(13, 56, ics[1][0]);
  u8g2.drawGlyph(56, 56, ics[1][1]);
  u8g2.drawGlyph(99, 56, ics[1][2]);
  u8g2.drawRFrame(10 + 43 * (a % 3), 6 + (a / 3) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x4(int a, int ics[][4])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(8, 24, ics[0][0]);
  u8g2.drawGlyph(40, 24, ics[0][1]);
  u8g2.drawGlyph(72, 24, ics[0][2]);
  u8g2.drawGlyph(104, 24, ics[0][3]);
  u8g2.drawGlyph(8, 56, ics[1][0]);
  u8g2.drawGlyph(40, 56, ics[1][1]);
  u8g2.drawGlyph(72, 56, ics[1][2]);
  u8g2.drawGlyph(104, 56, ics[1][3]);
  u8g2.drawRFrame(5 + 32 * (a % 4), 6 + (a / 4) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x5(int a, int ics[][5])
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
  u8g2.drawGlyph(8, 24, ics[0][0]);
  u8g2.drawGlyph(32, 24, ics[0][1]);
  u8g2.drawGlyph(56, 24, ics[0][2]);
  u8g2.drawGlyph(80, 24, ics[0][3]);
  u8g2.drawGlyph(104, 24, ics[0][4]);
  u8g2.drawGlyph(8, 24, ics[1][0]);
  u8g2.drawGlyph(32, 24, ics[1][1]);
  u8g2.drawGlyph(56, 24, ics[1][2]);
  u8g2.drawGlyph(80, 24, ics[1][3]);
  u8g2.drawGlyph(104, 24, ics[1][4]);
  u8g2.drawRFrame(5 + 24 * (a % 5), 6 + (a / 4) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

/*
// LCD12232接口
/////////////////////////////////////////
#define EN 5
#define RW 18
#define RS 19
U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, EN, RW, RS, U8X8_PIN_NONE);
// U8G2_ST7920_128X32_F_SW_SPI u8g2(U8G2_R0, 5, 18, 19, U8X8_PIN_NONE);
/////////////////////////////////////////*/

// #include <U8g2lib.h>