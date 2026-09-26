#include <Backlight.h>

void Blibri()
{
    static int i = 32;
    while (!Button)
    {
        wheel(&i);
        if (i < 0)
        {
            i = 0;
        }
        if (i > 32)
        {
            i = 32;
        }
        Lumi = 8 * i;
        if (Lumi > 255)
        {
            Lumi = 255;
        }
        u8g2.clearBuffer();
        if (i == 1)
        {
            /*  u8g2.drawVLine(32, 29, 6);
          }
          else if (i == 2)
          {*/
            u8g2.drawVLine(32, 29, 6);
            u8g2.drawVLine(33, 28, 8);
        }
        else if (i >= 2)
        {
            u8g2.drawRBox(32, 28, 2 * i, 8, 1);
        }
        u8g2.drawRFrame(30, 26, 68, 12, 3);
        u8g2.setFont(u8g2_font_helvB12_te);
        u8g2.setCursor(1, 57);
        u8g2.printf("%d%%", i * 100 / 32);
        u8g2.drawXBMP(56, 8, 16, 16, OpenIcons2x[14]);
        /*u8g2.setFont(u8g2_font_logisoso16_tr);
        u8g2.setCursor(0, 20);
        u8g2.printf("%d", i);
        u8g2.setCursor(0, 60);
        u8g2.printf("%d", Lumi);*/
        u8g2.sendBuffer();
        if (millis() - timer1 >= Boff * 1000)
            analogWrite(BGL, 0);
        else
            analogWrite(BGL, Lumi);
    }
    swclr();
}