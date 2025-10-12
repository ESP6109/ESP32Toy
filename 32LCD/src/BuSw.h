#ifndef BuSw_h
#define BuSw_h

#include <Arduino.h>

// 按键接口
/////////////////////////////////////////
#define BU 0
#define SW 13
struct Key
{
    const uint8_t Pin;
    bool pressed;
};
Key Button = {BU, 0};
Key Switch = {SW, 0};
unsigned long ST1 = 0, ST2 = 0;
unsigned long BT1 = 0, BT2 = 0;
/////////////////////////////////////////

void IRAM_ATTR button();
void IRAM_ATTR joysw();

// 按键IO0
/////////////////////////////////////////
void IRAM_ATTR button()
{
    BT1 = millis();
    if (BT1 - BT2 > 250)
    {
        Button.pressed = 1;
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
        Switch.pressed = 1;
        ST2 = ST1;
    }
}
/////////////////////////////////////////

#endif