#include "LCD.h"

int Lumi = 255;

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

  for (int i = 0; i < 2; i++)
  {
    u8g2.drawXBMP(24 + i * 64, 24, 16, 16, OpenIcons2x[ics[i]]);
  }
  u8g2.drawRFrame(21 + 64 * (a % 2), 22, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list1x3(int a, int ics[])
{
  u8g2.clearBuffer();

  for (int i = 0; i < 3; i++)
  {
    u8g2.drawXBMP(13 + i * 43, 24, 16, 16, OpenIcons2x[ics[i]]);
  }
  u8g2.drawRFrame(10 + 43 * (a % 3), 22, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x2(int a, int ics[][2])
{
  u8g2.clearBuffer();

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      u8g2.drawXBMP(24 + j * 64, 8 + i * 32, 16, 16, OpenIcons2x[ics[i][j]]);
    }
  }
  u8g2.drawRFrame(21 + 64 * (a % 2), 6 + (a / 2) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x3(int a, int ics[][3])
{
  u8g2.clearBuffer();

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      u8g2.drawXBMP(13 + j * 43, 8 + i * 32, 16, 16, OpenIcons2x[ics[i][j]]);
    }
  }
  u8g2.drawRFrame(10 + 43 * (a % 3), 6 + (a / 3) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void list2x4(int a, int ics[][4])
{
  u8g2.clearBuffer();

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      u8g2.drawXBMP(8 + j * 32, 8 + i * 32, 16, 16, OpenIcons2x[ics[i][j]]);
    }
  }
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
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      u8g2.drawGlyph(8 + j * 24, 24 + i * 32, ics[i][j]);
    }
  }
  u8g2.drawRFrame(5 + 24 * (a % 5), 6 + (a / 5) * 32, 22, 20, 3);
  u8g2.sendBuffer();
}
/////////////////////////////////////////
