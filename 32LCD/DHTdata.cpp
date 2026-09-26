#include "DHTdata.h"

//
/////////////////////////////////////////
// TaskHandle_t *DHTTask;
/////////////////////////////////////////

//
/////////////////////////////////////////
float TemDH = 0, TemDT = 0;
float DHum = 0, DTem = 0;
float MaxHum = 0, MinHum = 0;
float MaxTem = 0, MinTem = 0;
int DHTdelay = 3;
int DhtFlag = 0;
/////////////////////////////////////////

//
/////////////////////////////////////////
void HTdata()
{
    // vTaskSuspend(DHTTask);
    while (!Button)
    {
        u8g2.enableUTF8Print();
        u8g2.setFont(u8g2_font_helvB12_te);
        u8g2.clearBuffer();
        if (int(MinTem) <= -10)
            u8g2.setCursor(73, 14);
        else if (int(MinTem) >= -9 && int(MinTem) <= -1)
            u8g2.setCursor(82, 14);
        else if (int(MinTem) >= 0 && int(MinTem) <= 9)
            u8g2.setCursor(87, 14);
        else
            u8g2.setCursor(78, 14);
        u8g2.printf("%d.%d°C", int(MinTem), abs(int(MinTem * 10) % 10));
        if (int(MaxTem) <= -10)
            u8g2.setCursor(73, 62);
        else if (int(MaxTem) >= -9 && int(MaxTem) <= -1)
            u8g2.setCursor(82, 62);
        else if (int(MaxTem) >= 0 && int(MaxTem) <= 9)
            u8g2.setCursor(87, 62);
        else
            u8g2.setCursor(78, 62);
        u8g2.printf("%d.%d°C", int(MaxTem), abs(int(MaxTem * 10) % 10));
        if (int(DTem) <= -10)
            u8g2.setCursor(73, 38);
        else if (int(DTem) >= -9 && int(DTem) <= -1)
            u8g2.setCursor(82, 38);
        else if (int(DTem) >= 0 && int(DTem) <= 9)
            u8g2.setCursor(87, 38);
        else
            u8g2.setCursor(78, 38);
        u8g2.printf("%d.%d°C", int(DTem), abs(int(DTem * 10) % 10));
        if (MinHum >= 0 && MinHum <= 9)
            u8g2.setCursor(10, 14);
        else
            u8g2.setCursor(1, 14);
        u8g2.printf("%d.%d %%", int(MinHum), abs(int(MinHum * 10) % 10));
        if (MaxHum >= 0 && MaxHum <= 9)
            u8g2.setCursor(10, 62);
        else
            u8g2.setCursor(1, 62);
        u8g2.printf("%d.%d %%", int(MaxHum), abs(int(MaxHum * 10) % 10));
        if (int(DHum) >= 0 && int(DHum) <= 9)
            u8g2.setCursor(10, 38);
        else
            u8g2.setCursor(1, 38);
        u8g2.printf("%d.%d %%", int(DHum), abs(int(DHum * 10) % 10));
        // u8g2.drawXBMP(0, 16, 32, 32, OpenIcons4x[30]);
        u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[30]);
        u8g2.sendBuffer();
    }
    // vTaskResume(DHTTask);
    swclr();
}
/////////////////////////////////////////