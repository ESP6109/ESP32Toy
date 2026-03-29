#include "DHTdata.h"

float TemDH = 0, TemDT = 0;
float DHum = 0, DTem = 0;

/////////////////////////////////////////
void getdht1(void *pvParameters)
{
  while (1)
  {
    vTaskDelay(2500);
    TemDH = Dht.getHumidity();
    TemDT = Dht.getTemperature();
    if (!(isnan(TemDT) || isnan(TemDH) || TemDH > 100 || TemDH < 0))
    {
      DHum = TemDH;
      DTem = TemDT;
    }
  }
  // }
}
/////////////////////////////////////////
/*u8g2.clearBuffer();
u8g2.setFont(u8g2_font_helvB12_te);
if (int(DTem) <= -10)
u8g2.setCursor(73, 62);
else if (int(DTem) >= -9 && int(DTem) <= -1)
u8g2.setCursor(82, 62);
else if (int(DTem) >= 0 && int(DTem) <= 9)
u8g2.setCursor(87, 62);
else
u8g2.setCursor(78, 62);
u8g2.printf("%.1f°C", DTem);
if (int(DHum) >= 0 && int(DHum) <= 9)
u8g2.setCursor(10, 62);
else
u8g2.setCursor(1, 62);
u8g2.printf("%.1f %%", DHum);
u8g2.sendBuffer();
yield();*/