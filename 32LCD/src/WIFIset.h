#ifndef WIFI_h
#define WIFI_h

#include <Arduino.h>
#include <LCD.h>
#include <WiFi.h>

#include "BuSw.h"
#include "Joystick.h"

// WIFI列表
/////////////////////////////////////////
// const char* ssid = "H4749";
// const char* pwd = "18807724749";
const char *ssid[] = {"Xiaomi Civi 4 Pro"};
const char *pwd[] = {"k9qb1600"};
/////////////////////////////////////////

//
/////////////////////////////////////////
// int W_con = 0;
int wifiicons[2] = {64, 197};
/////////////////////////////////////////

void WIFIconnect();

// WIFI连接
/////////////////////////////////////////
void WIFIconnect()
{
    static int a = 0, c = 0;
    int d = 0;
    int t = 0;
    setCpuFrequencyMhz(240);
    Button = 0;
    Switch = 0;
    t = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid[0], pwd[0]);
        icon(53, 24, 247);
        delay(50);
        if (Button)
        {
            Button = 0;
            return;
        }
        if (millis() - t >= 300000)
        {
            icon(53, 24, 283);
            delay(500);
            return;
        }
    }
    if (WiFi.status() == WL_CONNECTED)
        d = 1;
    Button = 0;
    Switch = 0;
    while (!(Button || Switch))
    {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_helvB12_te);
        u8g2.setCursor(1, 22);
        u8g2.println(WiFi.localIP());
        u8g2.sendBuffer();
    }
    while (d)
    {
        Button = 0;
        Switch = 0;
        joystick(&a, &Nul);
        if (a >= 2 || a <= -1)
        {
            a = (a + 2) % 2;
        }
        // b = (b + H_I) % H_I;
        // b = 0;
        c = a + 1;
        list2(a, wifiicons);
        if (Switch)
        {
            if (a)
                WiFi.disconnect();
            a = c = d = 0;
            Button = 0;
            Switch = 0;
            return;
        }
        else if (Button)
        {
            Button = 0;
            Switch = 0;
            return;
        }
    }
}
/////////////////////////////////////////

#endif

/*Button = 0;
Switch = 0;
switch (c)
        {
        case 1:
            a = c = d = 0;
            Button = 0;
            Switch = 0;
            return;
        case 2:


setCpuFrequencyMhz(80);*/