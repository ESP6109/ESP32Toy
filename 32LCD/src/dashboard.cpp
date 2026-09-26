#include <dashboard.h>

// int Hou = 0, Min = 0;
int SpeR = 0, RspR = 0;
int Oil = 0, CooT = 0;
int BatV = 0;
int Odo = 0;
float Trip = 0;
float CurO = 0, AvaO = 0, Oph = 0;
char Gear;

void dashboard()
{
    while (!Button)
    {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_logisoso32_tn);
        if (SpeR >= 0 && SpeR <= 9)
            u8g2.setCursor(22, 48);
        else if (SpeR >= 10 && SpeR <= 99)
            u8g2.setCursor(12, 48);
        else
            u8g2.setCursor(2, 48);
        u8g2.printf("%d", SpeR);
        u8g2.setCursor(70, 48);
        u8g2.printf("%01d.%01d", (RspR / 1000), (RspR % 1000 / 100));
        for (int i = 4; i < 66; i++)
        {
            if (i % 4 == 0)
            {
                u8g2.drawVLine(i - 4, 57, 1);
                u8g2.drawVLine(i - 4, 62, 1);
            }
            if (i % 5 == 0)
            {
                u8g2.drawVLine(i + 62, 57, 1);
                u8g2.drawVLine(i + 62, 62, 1);
            }
        }
        // u8g2.drawFrame(-1, 56, 61, 8);
        // u8g2.drawFrame(132, 56, 61, 8);
        u8g2.drawHLine(0, 56, 61);
        u8g2.drawHLine(0, 63, 61);
        u8g2.drawHLine(67, 56, 61);
        u8g2.drawHLine(67, 63, 61);
        u8g2.drawBox(0, 58, SpeR * 64 / 160 + 1, 4);
        u8g2.drawBox(127 - (RspR / 100), 58, RspR / 100 + 1, 4);

        u8g2.drawRFrame(20, 2, 39, 13, 3);
        u8g2.drawRFrame(69, 2, 39, 13, 3);
        if (Oil * 36 / 100 == 1)
        {
            u8g2.drawVLine(22, 5, 7);
        }
        else if (Oil * 36 / 100 == 2)
        {
            u8g2.drawVLine(22, 5, 7);
            u8g2.drawVLine(23, 5, 7);
        }
        else if (Oil * 36 / 100 >= 3 && Oil * 36 / 100 <= 35)
        {
            u8g2.drawRBox(22, 4, Oil * 36 / 100, 9, 1);
        }
        else if (Oil * 36 / 100 == 36)
        {
            u8g2.drawRBox(22, 4, 35, 9, 1);
        }
        if (CooT >= 50 && CooT <= 129)
        {
            if ((CooT - 50) * 36 / 80 == 1)
            {
                u8g2.drawVLine(105, 5, 7);
            }
            else if ((CooT - 50) * 36 / 80 == 2)
            {
                u8g2.drawVLine(104, 5, 7);
                u8g2.drawVLine(105, 5, 7);
            }
            else if ((CooT - 50) * 36 / 80 >= 3)
            {
                u8g2.drawRBox(104 - ((CooT - 50) * 36 / 80), 4, (CooT - 50) * 36 / 80, 9, 1);
            }
        }
        else if (CooT >= 130)
        {
            u8g2.drawRBox(71, 4, 35, 9, 1);
        }
        for (int i = 0; i < 5; ++i)
        {
            u8g2.drawVLine(i * 6 + 27, 3, 1);
            u8g2.drawVLine(i * 6 + 76, 3, 1);
            u8g2.drawVLine(i * 6 + 27, 13, 1);
            u8g2.drawVLine(i * 6 + 76, 13, 1);
        }
        u8g2.drawXBMP(16, 6, 3, 5, EMPTY);
        u8g2.drawXBMP(60, 6, 3, 5, FULL);
        u8g2.drawXBMP(1, 2, 14, 12, FUEL);
        u8g2.drawXBMP(109, 6, 3, 5, COOL);
        u8g2.drawXBMP(65, 6, 3, 5, HOT);
        u8g2.drawXBMP(113, 2, 14, 12, WATEM);
        // u8g2.drawXBMP(118, 57, 10, 6, KM);
        u8g2.drawXBMP(22, 49, 19, 6, KPH);
        u8g2.drawXBMP(83, 49, 25, 6, KRPM);
        // u8g2.drawVLine(64, 10, 44);
        // u8g2.drawVLine(127, 10, 44);
        u8g2.sendBuffer();
    }
    swclr();
}