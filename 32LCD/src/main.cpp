// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 5.1.9
// Building
// Release at 2026.04.01 19:56

#include "main.h"

// 主界面图标
/////////////////////////////////////////
int menuicons[2][4] =
    {{124, 209, 93, 129},
     {240, 225, 141, 235}};
/////////////////////////////////////////

// 设置图标
/////////////////////////////////////////
int settingsicons[2][3] =
    {{247, 94, 123},
     {196, 92, 188}};
/////////////////////////////////////////

/////////////////////////////////////////
void getdht(void *pvParameters)
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
}
/////////////////////////////////////////

// 初始化
/////////////////////////////////////////
void setup()
{
  Dht.setup(DhtPin, DHTesp::DHT22);
  u8g2.begin();
  u8g2.enableUTF8Print();
  pinMode(LED, OUTPUT);
  pinMode(BGL, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(MIDDLE, INPUT_PULLUP);
  pinMode(RIGHT, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT), left, FALLING);
  attachInterrupt(digitalPinToInterrupt(MIDDLE), middle, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT), right, FALLING);
  // esp_sleep_enable_ext1_wakeup(GPIO_NUM_1, 0);
  esp_deep_sleep_enable_gpio_wakeup(2, ESP_GPIO_WAKEUP_GPIO_LOW); // 2 = GPIO1 + 1
  setCpuFrequencyMhz(80);
  esp_timer.attach(1.0, SecCou);
  xTaskCreate(getdht,
              "DHTdata",
              16384,
              NULL,
              3,
              NULL);
  timer1 = timer2 = millis();
  analogWrite(BGL, Lumi);
  digitalWrite(LED, 1);
  clearscr();
  swclr();
}
/////////////////////////////////////////

// 主循环
/////////////////////////////////////////
void loop()
{
  home();
}
/////////////////////////////////////////

// 主页
/////////////////////////////////////////
void home()
{
  if (Middle)
  {
    swclr();
    menu();
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_te);
  u8g2.setCursor(18, 14);
  u8g2.printf("%4d.%02d.%02d-%d", Yea, Mon, Day, Wee);
  if (Sec < 30 && Wup)
  {
    if (Tem[0] <= -10)
      u8g2.setCursor(86, 62);
    else if (Tem[0] >= -9 && Tem[0] <= -1)
      u8g2.setCursor(95, 62);
    else if (Tem[0] >= 0 && Tem[0] <= 9)
      u8g2.setCursor(100, 62);
    else
      u8g2.setCursor(91, 62);
    u8g2.printf("%d°C", Tem[0]); // Tem
    if (Hum[0] >= 0 && Hum[0] <= 9)
      u8g2.setCursor(10, 62);
    else
      u8g2.setCursor(1, 62);
    u8g2.printf("%d %%", Hum[0]); // Hum
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(56, 64, Icon[0][0]);
  }
  else
  {
    if (int(DTem) <= -10)
      u8g2.setCursor(73, 62);
    else if (int(DTem) >= -9 && int(DTem) <= -1)
      u8g2.setCursor(82, 62);
    else if (int(DTem) >= 0 && int(DTem) <= 9)
      u8g2.setCursor(87, 62);
    else
      u8g2.setCursor(78, 62);
    u8g2.printf("%d.%d°C", int(DTem), abs(int(DTem * 10) % 10));
    if (int(DHum) >= 0 && int(DHum) <= 9)
      u8g2.setCursor(10, 62);
    else
      u8g2.setCursor(1, 62);
    u8g2.printf("%d.%d %%", int(DHum), abs(int(DHum * 10) % 10));
    u8g2.drawXBMP(56, 48, 16, 16, Therm);
  }
  u8g2.setFont(u8g2_font_helvB24_te);
  u8g2.setCursor(-1, 44);
  u8g2.printf("%02d:%02d:%02d", Hou, Min, Sec);
  u8g2.sendBuffer();
}
/////////////////////////////////////////

// 主菜单
/////////////////////////////////////////
void menu()
{
  static int a = 0, b = 0, c = 0;
  int d = 1;
  while (d)
  {
    wheel(&a);
    if (a >= 8 || a <= -1)
    {
      a = (a + 8) % 8;
      // b += 1;
    }
    b = (b + 2) % 2;
    list2x4(a, menuicons);
    c = b * 4 + (a + 1);
    if (Middle)
    {
      swclr();
      switch (c)
      {
      case 1:
        weather();
        break;
      case 2:
        gps();
        break;
        // case 3:
        // timerset();
        // break;
      case 4:
        settings();
        break;
      // case 5:
      // lab();
      // break;
      case 7:
        // manager();
        dino();
        break;
      case 8:
        power();
        break;
      default:
        building();
      }
    }
    if (Button)
    {
      swclr();
      a = b = c = d = 0;
    }
  }
  swclr();
}
/////////////////////////////////////////

// 设置
/////////////////////////////////////////
void settings()
{
  static int a = 0, c = 0;
  int d = 1;
  while (d)
  {
    wheel(&a);
    if (a >= 6 || a <= -1)
    {
      a = (a + 6) % 6;
      // b += 1;
    }
    // b = (b + H_I) % H_I;
    // b = 0;
    list2x3(a, settingsicons);
    c = a + 1;
    if (Middle)
    {
      swclr();
      switch (c)
      {
      case 1:
        WIFIconnect();
        break;
      case 3:
        clksets();
        break;
      case 4:
        Blibri();
        break;
      case 5:
        lab();
        break;
      case 6:
        esp_info();
        break;
      default:
        building();
      }
    }
    if (Button)
    {
      swclr();
      a = c = d = 0;
    }
  }
  swclr();
}
/////////////////////////////////////////

// 测试
/////////////////////////////////////////
void lab()
{
  setCpuFrequencyMhz(160);
  static char st = 'N';
  delay(50);
  while (!Button)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso16_tr);
    if (!digitalRead(LEFT))
      st = 'L';
    else if (!digitalRead(MIDDLE))
      st = 'M';
    else if (!digitalRead(RIGHT))
      st = 'R';
    else
      st = 'N';
    switch (st)
    {
    case 'L':
    {
      u8g2.drawRBox(27, 22, 22, 20, 1);
      u8g2.setCursor(28, 40);
      u8g2.setDrawColor(0);
      u8g2.printf("LL");
      u8g2.setDrawColor(1);
      u8g2.setCursor(54, 40);
      u8g2.printf("MM");
      u8g2.setCursor(80, 40);
      u8g2.printf("RR");
      break;
    }
    case 'M':
    {
      u8g2.setCursor(28, 40);
      u8g2.printf("LL");
      u8g2.drawRBox(53, 22, 22, 20, 1);
      u8g2.setCursor(54, 40);
      u8g2.setDrawColor(0);
      u8g2.printf("MM");
      u8g2.setDrawColor(1);
      u8g2.setCursor(80, 40);
      u8g2.printf("RR");
      break;
    }
    case 'R':
    {
      u8g2.setCursor(28, 40);
      u8g2.printf("LL");
      u8g2.setCursor(54, 40);
      u8g2.printf("MM");
      u8g2.drawRBox(79, 22, 22, 20, 1);
      u8g2.setCursor(80, 40);
      u8g2.setDrawColor(0);
      u8g2.printf("RR");
      u8g2.setDrawColor(1);
      break;
    }
    default:
    {
      u8g2.setCursor(28, 40);
      u8g2.printf("LL");
      u8g2.setCursor(54, 40);
      u8g2.printf("MM");
      u8g2.setCursor(80, 40);
      u8g2.printf("RR");
    }
    }
    u8g2.sendBuffer();
  }
  swclr();
  setCpuFrequencyMhz(80);
}
/////////////////////////////////////////

// 关于
/////////////////////////////////////////
void esp_info()
{
  while (!Button)
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    /*static int i = 0;
    joystick(&Nul, &i);
    i %= (i + 2);
    u8g2.setCursor(4, 20);
    u8g2.printf("Designed by ESP6109.");*/
    u8g2.setCursor(4, 22);
    u8g2.printf("Espressif Tech.");
    u8g2.setCursor(14, 54);
    u8g2.printf("Version 5.1.9");
    u8g2.sendBuffer();
  }
  swclr();
}
/////////////////////////////////////////

// BUILDING
/////////////////////////////////////////
void building()
{
  while (!Button)
  {
    icon(56, 40, 282);
  }
  swclr();
}
/////////////////////////////////////////

// 管理器
/////////////////////////////////////////
void manager()
{
  /*unsigned int i, j = 0;
  i = millis() / 1000;
  while ((millis() / 1000) - i > 0)
  {
    if (button())
      j = (j + 1) % 2;
    i = millis() / 1000;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_t0_16_mf);
    u8g2.setCursor(10, 10);
    u8g2.printf("Start Manager");
    u8g2.setCursor(105, 30);
    u8g2.printf("%d", 3 - i);
    u8g2.setCursor(21, 30);
    u8g2.printf("%d", j + 1);
    u8g2.sendBuffer();
    delay(1);
  }
  if (3 - i <= 0)
    switch (j)
    {
    case 0:
      s_box();
      break;
    case 1:
      s_shot();
      break;
    }*/
  s_box();
  clearscr();
  s_shot();
  swclr();
}
/////////////////////////////////////////

// 电源选项
/////////////////////////////////////////
void power()
{
  static int a = 0, c = 0;
  int d = 1;
  while (d)
  {
    wheel(&a);
    if (a >= 2 || a <= -1)
    {
      a = (a + 2) % 2;
    }
    // b = (b + H_I) % H_I;
    // b = 0;
    list1x2(a, powericons);
    c = a + 1;
    if (Middle)
    {
      swclr();
      power(a);
    }
    if (Button)
    {
      swclr();
      a = c = d = 0;
      return;
    }
  }
  swclr();
}
/////////////////////////////////////////

/*while (Left)
{
  a--;
  // *i += 4;
  // *i %= 5;
  Left = 0;
}
Left = 0;
while (Right)
{
  a++;
  // *i %= 5;
  Right = 0;
}
Right = 0;*/
/*#include <Arduino.h>
#include "esp32-hal-cpu.h"
#include <driver/gpio.h>

#include "BuSw.h"
#include "Clock.h"
#include "DaTi.h"
#include "GPS.h"
#include "Joy.h"
#include "Joystick.h"
#include "LCD.h"
#include "Power.h"
#include "Weather.h"
#include "WIFIset.h"*/
/*
// 定义
/////////////////////////////////////////
void home();
void menu();
void weather();
void settings();
void lab();
void esp_info();
void building();
void manager();
void power();
/////////////////////////////////////////*/