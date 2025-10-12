#ifndef WIFI_h
#define WIFI_h

#include <Arduino.h>
#include <LCD.h>
#include <WiFi.h>

#include "BuSw.h"

// WIFI列表
/////////////////////////////////////////
// const char* ssid = "H4749";
// const char* pwd = "18807724749";
const char *ssid[] = {"Xiaomi Civi 4 Pro"};
const char *pwd[] = {"k9qb1600"};
/////////////////////////////////////////

//
/////////////////////////////////////////
int W_con = 0;
/////////////////////////////////////////

void WIFIconnect();

// WIFI连接
/////////////////////////////////////////
void WIFIconnect()
{
    setCpuFrequencyMhz(240);
    while (!Button.pressed)
    {
        if (!W_con)
            WiFi.begin(ssid[0], pwd[0]);
        while (WiFi.status() != WL_CONNECTED && !Button.pressed)
        {
            u8g2.clearBuffer();
            u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
            u8g2.drawGlyph(53, 24, 247);
            u8g2.sendBuffer();
            delay(500);
        }
        if (WiFi.status() == WL_CONNECTED)
            W_con = 1;
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_helvB12_tf);
        u8g2.setCursor(1, 22);
        u8g2.println(WiFi.localIP());
        u8g2.sendBuffer();
    }
    Button.pressed = 0;
    Switch.pressed = 0;
    setCpuFrequencyMhz(80);
}
/////////////////////////////////////////

#endif

/*u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_helvB12_tf);
        u8g2.setCursor(0, 14);
        u8g2.printf("X-%04d", analogRead(14));
        u8g2.setCursor(0, 30);
        u8g2.printf("Y-%04d", analogRead(26));
        u8g2.sendBuffer();
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_helvB12_tf);
        u8g2.setCursor(0, 22);*/