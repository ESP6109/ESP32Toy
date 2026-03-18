#include "WiFiset.h"

// WIFI列表
/////////////////////////////////////////
const char *ssid[] = {""};
const char *pwd[] = {""};
/////////////////////////////////////////

//
/////////////////////////////////////////
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
    swclr();
    t = millis();
    WiFi.mode(WIFI_MODE_STA);
    while (WiFi.status() != WL_CONNECTED)
    {
        icon(56, 40, 247);
        WiFi.begin(ssid[0], pwd[0]);
        delay(125);
        if (Button)
        {
            swclr();
            WiFi.mode(WIFI_OFF);
            setCpuFrequencyMhz(80);
            return;
        }
        if (millis() - t >= 15000)
        {
            icon(56, 40, 283);
            delay(400);
            swclr();
            WiFi.mode(WIFI_OFF);
            setCpuFrequencyMhz(80);
            return;
        }
    }
    setCpuFrequencyMhz(240);
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
        // u8g2.println(len);
        // u8g2.setFont(u8g2_font_logisoso16_tr);
        // u8g2.setCursor(0, 54);
        // u8g2.println(WiFi.macAddress().c_str());
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
            }
            WiFi.mode(WIFI_OFF);
            a = c = d = 0;
            swclr();
            setCpuFrequencyMhz(80);
            return;
        }
        else if (Button)
        {
            swclr();
            setCpuFrequencyMhz(80);
            return;
        }
    }
    setCpuFrequencyMhz(80);
    swclr();
}
/////////////////////////////////////////

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
