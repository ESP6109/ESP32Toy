#include "WiFiset.h"



//
/////////////////////////////////////////
int wifiicons[2] = {0, 15};
int wifichsicons[2] = {22, 12};
/////////////////////////////////////////

//
/////////////////////////////////////////
void WIFIchs(int *i)
{
    while (!Middle || !Button)
    {
        u8g2.clearBuffer();
        wheel(&*i);
        if (*i >= 2 || *i <= -1)
        {
            *i = (*i + 2) % 2;
        }

        list1x2(*i, wifichsicons);
        u8g2.sendBuffer();
    }
    swclr();
}
/////////////////////////////////////////

// WIFI连接
/////////////////////////////////////////
void WIFIconnect()
{
    static int a = 0, c = 0;
    int d = 0;
    int t = 0, i = 0;
    if (WiFi.status() != WL_CONNECTED)
    {
        while (!Middle /*|| !Button*/)
        {
            u8g2.clearBuffer();
            wheel(&i);
            if (i >= 2 || i <= -1)
            {
                i = (i + 2) % 2;
            }

            list1x2(i, wifichsicons);
            u8g2.sendBuffer();
            if (Button)
            {
                swclr();
                setCpuFrequencyMhz(80);
                return;
            }
        }
        swclr();
    }
    setCpuFrequencyMhz(160);
    swclr();
    WiFi.mode(WIFI_MODE_STA);
    t = millis();
    if (WiFi.status() != WL_CONNECTED)
    {
        u8g2.clearBuffer();
        u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[27]);
        u8g2.setFont(u8g2_font_helvB12_te);
        u8g2.setCursor(1, 14);
        u8g2.println(ssid[i]);
        u8g2.sendBuffer();
        WiFi.begin(ssid[i], pwd[i]);
        delay(150);
    }
    while (WiFi.status() != WL_CONNECTED)
    {
        // u8g2.clearBuffer();
        // u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[27]);
        // u8g2.sendBuffer();
        delay(5);
        Serial.printf("%d", WiFi.status());
        Serial.println("");
        if (Button)
        {
            swclr();
            WiFi.mode(WIFI_OFF);
            setCpuFrequencyMhz(80);
            return;
        }
        if (millis() - t >= 15000)
        {
            u8g2.clearBuffer();
            u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[33]);
            u8g2.sendBuffer();
            delay(400);
            swclr();
            WiFi.mode(WIFI_OFF);
            setCpuFrequencyMhz(80);
            return;
        }
    }
    setCpuFrequencyMhz(160);
    if (WiFi.status() == WL_CONNECTED)
        d = 1;
    swclr();
    while (!(Button || Middle))
    {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_helvB12_te);
        int len = strlen(WiFi.localIP().toString().c_str());
        u8g2.setCursor((128 - 3 * 4 - (len - 3) * 9) / 2, 38);
        u8g2.println(WiFi.localIP().toString().c_str());
        u8g2.sendBuffer();
    }
    swclr();
    while (d)
    {
        wheel(&a);
        if (a >= 2 || a <= -1)
        {
            a = (a + 2) % 2;
        }
        // b = (b + H_I) % H_I;
        // b = 0;
        c = a + 1;
        list1x2(a, wifiicons);
        if (Middle)
        {
            if (a)
            {
                WiFi.disconnect();
                WiFi.mode(WIFI_OFF);
            }
            a = c = d = 0;
            swclr();
            setCpuFrequencyMhz(80);
            // Serial.end();
            return;
        }
        else if (Button)
        {
            a = c = d = 0;
            swclr();
            setCpuFrequencyMhz(80);
            // Serial.end();
            return;
        }
    }
    setCpuFrequencyMhz(80);
    // Serial.end();
    swclr();
}
/////////////////////////////////////////
