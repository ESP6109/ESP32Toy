#include "BuSw.h"

// 按键接口
/////////////////////////////////////////
int Button = 0;
int Switch = 0;
int Left = 0, Middle = 0, Right = 0;
unsigned long ST1 = 0, ST2 = 0;
unsigned long BT1 = 0, BT2 = 0;
int timer1 = 0, timer2 = 0;
/////////////////////////////////////////

// 按键IO0
/////////////////////////////////////////
void IRAM_ATTR button()
{
    timer1 = timer2 = millis();
    analogWrite(BGL, 255);
    BT1 = millis();
    if (BT1 - BT2 > 300&& digitalRead(BUTTON))
    {
        Button = 1;
        BT2 = BT1;
    }
}
/////////////////////////////////////////

// 按键Left
/////////////////////////////////////////
void IRAM_ATTR left()
{
    timer1 = timer2 = millis();
    analogWrite(BGL, 255);
    BT1 = millis();
    if (BT1 - BT2 > 300&& digitalRead(LEFT))
    {
        Left = 1;
        BT2 = BT1;
    }
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void IRAM_ATTR middle()
{
    timer1 = timer2 = millis();
    analogWrite(BGL, 255);
    BT1 = millis();
    if (BT1 - BT2 > 300 && digitalRead(MIDDLE))
    {
        Middle = 1;
        BT2 = BT1;
    }
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void IRAM_ATTR right()
{
    timer1 = timer2 = millis();
    analogWrite(BGL, 255);
    BT1 = millis();
    if (BT1 - BT2 > 300&& digitalRead(RIGHT))
    {
        Right = 1;
        BT2 = BT1;
    }
}
//////////////////////////////////////////

//
//////////////////////////////////////////
void swclr()
{
    Button = 0;
    Left = 0;
    Middle = 0;
    Right = 0;
}
//////////////////////////////////////////

//
//////////////////////////////////////////
void wheel(int *i)
{
    while (Left)
    {
        (*i)--;
        // *i += 4;
        // *i %= 5;
        Left = 0;
    }
    Left = 0;
    while (Right)
    {
        (*i)++;
        // *i %= 5;
        Right = 0;
    }
    Right = 0;
    // swclr();
}
//////////////////////////////////////////