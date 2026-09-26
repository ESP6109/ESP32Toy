#include "Weather.h"

// 温湿度
/////////////////////////////////////////
int Tem[3] = {0, 0, 0}, Hum[3] = {0, 0, 0};
int MaxT[3][3] =
    {{0, 0, 0},
     {0, 0, 0},
     {0, 0, 0}};
int MinT[3][3] =
    {{0, 0, 0},
     {0, 0, 0},
     {0, 0, 0}};
/////////////////////////////////////////

// 日期
/////////////////////////////////////////
int Date[3][3] =
    {{0, 0, 0},
     {0, 0, 0},
     {0, 0, 0}};
/////////////////////////////////////////

// 天气图标
/////////////////////////////////////////
int weathericons[5] = {29, 19, 6, 8, 25}; // 日晴 夜晴 阴 多云 雨
int IcCo[3][3] =
    {{0, 0, 0},
     {0, 0, 0},
     {0, 0, 0}};
int Icon[3][3] =
    {{0, 0, 0},
     {0, 0, 0},
     {0, 0, 0}};
/////////////////////////////////////////

//
/////////////////////////////////////////
int Wup = 0;
/////////////////////////////////////////

// 天气
/////////////////////////////////////////
void weather()
{
  static int w = 0;
  if (!w && (WiFi.status() == WL_CONNECTED))
  {
    setCpuFrequencyMhz(160);
    for (int j = 0; j < 3; ++j)
    {
      WeatherDaily(j);
      delay(10);
      WeatherNow(j);
      delay(10);
    }
    setCpuFrequencyMhz(80);
    swclr();
    w = 1;
  }
  else if (!w && WiFi.status() != WL_CONNECTED)
  {
    u8g2.clearBuffer();
    u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[33]);
    u8g2.sendBuffer();
    delay(400);
  }
  swclr();
  int i = 0;
  while (!Button)
  {
    if (Middle && (WiFi.status() == WL_CONNECTED))
    {
      setCpuFrequencyMhz(160);
      for (int j = 0; j < 3; ++j)
      {
        WeatherDaily(j);
        delay(10);
        WeatherNow(j);
        delay(10);
      }
      setCpuFrequencyMhz(80);
      swclr();
    }
    else if (Middle && (WiFi.status() != WL_CONNECTED))
    {
      u8g2.clearBuffer();
      u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[33]);
      u8g2.sendBuffer();
      delay(400);
      swclr();
    }
    wheel(&i);
    i += 3;
    i %= 3;
    weadisplay(i);
  }
  swclr();
}
/////////////////////////////////////////

// 天气显示
/////////////////////////////////////////
void weadisplay(int s)
{
  u8g2.enableUTF8Print();
  weaicons(s, 0);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_te);

  if (MaxT[s][0] <= -10)
    u8g2.setCursor(86, 14);
  else if (MaxT[s][0] >= -9 && MaxT[s][0] <= -1)
    u8g2.setCursor(95, 14);
  else if (MaxT[s][0] >= 0 && MaxT[s][0] <= 9)
    u8g2.setCursor(100, 14);
  else
    u8g2.setCursor(91, 14);
  u8g2.printf("%d°C", MaxT[s][0]); // MaxT

  if (MinT[s][0] <= -10)
    u8g2.setCursor(86, 30);
  else if (MinT[s][0] >= -9 && MinT[s][0] <= -1)
    u8g2.setCursor(95, 30);
  else if (MinT[s][0] >= 0 && MinT[s][0] <= 9)
    u8g2.setCursor(100, 30);
  else
    u8g2.setCursor(91, 30);
  u8g2.printf("%d°C", MinT[s][0]); // MinT

  u8g2.drawXBMP(48, 0, 32, 32, OpenIcons4x[Icon[s][0]]); // Icon

  if (Tem[s] <= -10)
    u8g2.setCursor(1, 14);
  else if (Tem[s] >= -9 && Tem[s] <= -1)
    u8g2.setCursor(10, 14);
  else if (Tem[s] >= 0 && Tem[s] <= 9)
    u8g2.setCursor(15, 14);
  else
    u8g2.setCursor(6, 14);
  u8g2.printf("%d°C", Tem[s]); // Tem

  if (Hum[s] >= 0 && Hum[s] <= 9)
    u8g2.setCursor(15, 30);
  else
    u8g2.setCursor(6, 30);
  u8g2.printf("%d %%", Hum[s]); // Hum

  for (int i = 1; i < 3; ++i)
  {
    weaicons(s, i);
    u8g2.setFont(u8g2_font_helvB12_te);

    if (MaxT[s][i] <= -10)
      u8g2.setCursor(-33 + i * 66, 46);
    else if (MaxT[s][i] <= -1 && MaxT[s][i] >= -9)
      u8g2.setCursor(-24 + i * 66, 46);
    else if (MaxT[s][i] >= 0 && MaxT[s][i] <= 9)
      u8g2.setCursor(-19 + i * 66, 46);
    else
      u8g2.setCursor(-28 + i * 66, 46);
    u8g2.printf("%d", MaxT[s][i]); // MaxT

    if (MinT[s][i] <= -10)
      u8g2.setCursor(-33 + i * 66, 62);
    else if (MinT[s][i] <= -1 && MinT[s][i] >= -9)
      u8g2.setCursor(-24 + i * 66, 62);
    else if (MinT[s][i] >= 0 && MinT[s][i] <= 9)
      u8g2.setCursor(-19 + i * 66, 62);
    else
      u8g2.setCursor(-28 + i * 66, 62);
    u8g2.printf("%d", MinT[s][i]); // MinT

    u8g2.drawRBox(-59 + i * 66, 33, 21, 14, 1);
    u8g2.setCursor(-57 + i * 66, 46);
    u8g2.setDrawColor(0);
    u8g2.printf("%02d", Date[s][i]); // Date

    u8g2.setDrawColor(1);
    u8g2.drawXBMP(-56 + i * 66, 48, 16, 16, OpenIcons2x[Icon[s][i]]); // Icon
  }
  u8g2.drawXBMP(59, 35, 12, 26, City[s]); // City
  u8g2.sendBuffer();
}
/////////////////////////////////////////

//
/////////////////////////////////////////
void weaicons(int i, int j)
{
  if (IcCo[i][j] == 0 || IcCo[i][j] == 2)
  {
    Icon[i][j] = weathericons[0];
  }
  else if (IcCo[i][j] == 1 || IcCo[i][j] == 3)
  {
    Icon[i][j] = weathericons[1];
  }
  else if (IcCo[i][j] >= 4 && IcCo[i][j] <= 8)
  {
    Icon[i][j] = weathericons[3];
  }
  else if (IcCo[i][j] == 9 || (IcCo[i][j] >= 26 && IcCo[i][j] <= 31))
  {
    Icon[i][j] = weathericons[2];
  }
  else if (IcCo[i][j] >= 10 && IcCo[i][j] <= 20)
  {
    Icon[i][j] = weathericons[4];
  }
}
/////////////////////////////////////////

// 此刻天气
/////////////////////////////////////////
void WeatherNow(int i)
{
  delay(10);
  u8g2.clearBuffer();
  u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[7]);
  u8g2.sendBuffer();
  HTTPClient http;
  http.begin(weanow[i]);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(100);
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND)
    {
      String result = http.getString();
      deserializeJson(doc, result);
      String tem = doc["results"][0]["now"]["temperature"];
      String ico0 = doc["results"][0]["now"]["code"];
      Tem[i] = atoi(tem.c_str());
      IcCo[i][0] = atoi(ico0.c_str());
      Wup = 1;
      u8g2.clearBuffer();
      u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[4]);
      u8g2.sendBuffer();
      delay(400);
    }
  }
  else
  {
    u8g2.clearBuffer();
    u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[33]);
    u8g2.sendBuffer();
    delay(400);
  }
  swclr();
  http.end();
  doc.clear();
}
/////////////////////////////////////////

// 多日天气
/////////////////////////////////////////
void WeatherDaily(int i)
{
  delay(10);
  u8g2.clearBuffer();
  u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[7]);
  u8g2.sendBuffer();
  HTTPClient http;
  http.begin(weadaily[i]);
  http.setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36");
  int httpCode = 0;
  httpCode = http.GET();
  delay(100);
  if (httpCode > 0)
  {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND)
    {
      String result = http.getString();
      deserializeJson(doc, result);
      String hum = doc["results"][0]["daily"][0]["humidity"];
      Hum[i] = atoi(hum.c_str());
      Serial.println(result);
      for (int j = 0; j < 3; ++j)
      {
        String mat = doc["results"][0]["daily"][j]["high"];
        String mit = doc["results"][0]["daily"][j]["low"];
        String ico = doc["results"][0]["daily"][j]["code_day"];
        String dat = doc["results"][0]["daily"][j]["date"];
        MaxT[i][j] = atoi(mat.c_str());
        MinT[i][j] = atoi(mit.c_str());
        IcCo[i][j] = atoi(ico.c_str());
        Date[i][j] = (dat[8] - 48) * 10 + (dat[9] - 48);
      }
      u8g2.clearBuffer();
      u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[4]);
      u8g2.sendBuffer();
      delay(400);
    }
  }
  else
  {
    u8g2.clearBuffer();
    u8g2.drawXBMP(56, 24, 16, 16, OpenIcons2x[33]);
    u8g2.sendBuffer();
    delay(400);
  }
  swclr();
  http.end();
  doc.clear();
}
/////////////////////////////////////////
