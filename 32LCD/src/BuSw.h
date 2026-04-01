#ifndef BuSw_h
#define BuSw_h

#include <Arduino.h>

#include "LCD.h"

// 按键接口
/////////////////////////////////////////
#define LED 8
#define BGL 10
#define BUTTON 9
#define LEFT 0
#define MIDDLE 1
#define RIGHT 2

extern int Button;
extern int Switch;
extern int Left, Middle, Right;
extern int Lp, Rp;
extern unsigned long ST1, ST2;
extern unsigned long BT1, BT2;
extern int timer1, timer2;
/////////////////////////////////////////

void IRAM_ATTR button();
void IRAM_ATTR left();
void IRAM_ATTR middle();
void IRAM_ATTR right();
void swclr();
void wheel(int *);
#endif

/*
// 按键IO0
/////////////////////////////////////////
void IRAM_ATTR button()
{
    BT1 = millis();
    if (BT1 - BT2 > 250)
    {
        Button = 1;
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
        Switch = 1;
        ST2 = ST1;
    }
}
/////////////////////////////////////////

*/