#include "WiFiset.h"

// WIFI列表
/////////////////////////////////////////
// const char* ssid = "H4749";
// const char* pwd = "18807724749";
const char *ssid[] = {"Xiaomi Civi 4 Pro"};
const char *pwd[] = {"k9qb1600"};
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
    Serial.begin(115200);
    setCpuFrequencyMhz(160);
    swclr();
    t = millis();
    WiFi.mode(WIFI_MODE_STA);
    while (WiFi.status() != WL_CONNECTED)
    {
        icon(56, 40, 247);
        // WiFi.scanNetworks();
        WiFi.begin(ssid[0], pwd[0]);
        if (WiFi.status() == WL_CONNECTED)
            break;
        // Serial.printf("%d-%d\n", WiFi.status(), WiFi.scanNetworks());
        Serial.printf("%d", WiFi.status());
        Serial.println("");
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
            Serial.end();
            return;
        }
        else if (Button)
        {
            a = c = d = 0;
            swclr();
            setCpuFrequencyMhz(80);
            Serial.end();
            return;
        }
    }
    setCpuFrequencyMhz(80);
    Serial.end();
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