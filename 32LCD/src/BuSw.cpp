#include "BuSw.h"

// 按键接口
/////////////////////////////////////////
int Button = 0;
int Switch = 0;
int Left = 0, Middle = 0, Right = 0;
int Lp = 0, Rp = 0;
unsigned long ST1 = 0, ST2 = 0;
unsigned long BT1 = 0, BT2 = 0;
int timer1 = 0, timer2 = 0;
/////////////////////////////////////////

// 按键IO0
/////////////////////////////////////////
void IRAM_ATTR button()
{
    timer1 = timer2 = millis();
    analogWrite(BGL, Lumi);
    BT1 = millis();
    if (BT1 - BT2 > 300 && digitalRead(BUTTON))
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
    analogWrite(BGL, Lumi);
    BT1 = millis();
    if (BT1 - BT2 > 300 && digitalRead(LEFT))
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
    analogWrite(BGL, Lumi);
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
    analogWrite(BGL, Lumi);
    BT1 = millis();
    if (BT1 - BT2 > 300 && digitalRead(RIGHT))
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
    if (Lp)
    {
        (*i) -= (!digitalRead(LEFT));
    }
    if (Rp)
    {
        (*i) += (!digitalRead(RIGHT));
    }
    if (Left && !Lp)
    {
        (*i) -= Left;
        Lp = 1;
    }
    if (Right && !Rp)
    {
        (*i) += Right;
        Rp = 1;
    }
    if (digitalRead(LEFT))
    {
        Lp = 0;
    }
    if (digitalRead(RIGHT))
    {
        Rp = 0;
    }
    Left = 0;
    Right = 0;
}
//////////////////////////////////////////
/*while (Left)
{
    (*i)--;
    Left = 0;
}
while (Right)
{
    (*i)++;
    Right = 0;
}*/