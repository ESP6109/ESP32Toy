
#include <GPS.h>

// 定位数据
/////////////////////////////////////////
float Lng = 0, Lat = 0; // 经纬
float Spe = 0;          // 速度
int Deg = 0;            // 方向角
int Alt = 0;            // 海拔
int Nsat = 0;           // 卫星数
char Cou[3];            // 方向
char Ava[2];            // 有效值
/////////////////////////////////////////

// 定位
/////////////////////////////////////////
void gps()
{
  u8g2.enableUTF8Print();
  Serial.begin(9600);
  int a = 0;
  setCpuFrequencyMhz(160);
  while (!Button)
  {
    gpsget();
    // joystick(&a, &Nul);
    wheel(&a);
    a = (a + 4) % 4;
    a %= 4;
    if (Ava[0] == 'V') // 无效
    {
      digitalWrite(LED, 1);
      G_t = 0;
    }
    else if (Ava[0] == 'A') // 有效
    {
      digitalWrite(LED, 0);
      G_t = 1;
    }
    gpsdisplay(a);
  }
  swclr();
  setCpuFrequencyMhz(80);
  G_t = 0;
  digitalWrite(LED, 1);
  Ava[0] == 'V';
  Serial.end();
}
/////////////////////////////////////////

// 卫星数据
/////////////////////////////////////////
void gpsget()
{
  for (unsigned long m = millis(); millis() - m <= 300;)
  {
    while (Serial.available())
    {
      GPS.encode(Serial.read());
    }
  }
  gpsdata();
}
/////////////////////////////////////////

// 卫星数据
/////////////////////////////////////////
void gpsdata()
{
  strcpy(Ava, A.value());
  if (!N_t && (Ava[0] == 'A'))
  {
    Yea = GPS.date.year();   // 年
    Mon = GPS.date.month();  // 月
    Day = GPS.date.day();    // 日
    Hou = GPS.time.hour();   // 时
    Min = GPS.time.minute(); // 分
    Sec = GPS.time.second(); // 秒
    Hou += 8;
    clccal();
  }
  Lng = GPS.location.lng();    // 经度
  Lat = GPS.location.lat();    // 纬度
  Spe = GPS.speed.kmph();      // 速度
  Deg = GPS.course.deg();      // 方向角
  Alt = GPS.altitude.meters(); // 卫星数
  Nsat = GPS.satellites.value();
  if ((Deg > 338 && Deg < 360) || (Deg >= 0 && Deg < 22)) // N
  {
    strcpy(Cou, "N");
  }
  else if (Deg >= 22 && Deg <= 68) // NE
  {
    strcpy(Cou, "NE");
  }
  else if (Deg > 68 && Deg < 112) // E
  {
    strcpy(Cou, "E");
  }
  else if (Deg >= 112 && Deg <= 158) // SE
  {
    strcpy(Cou, "SE");
  }
  else if (Deg > 158 && Deg < 202) // S
  {
    strcpy(Cou, "S");
  }
  else if (Deg >= 202 && Deg <= 248) // SW
  {
    strcpy(Cou, "SW");
  }
  else if (Deg > 248 && Deg < 292) // W
  {
    strcpy(Cou, "W");
  }
  if (Deg >= 292 && Deg <= 338) // NW
  {
    strcpy(Cou, "NW");
  }
}
/////////////////////////////////////////

// 定位显示
/////////////////////////////////////////
void gpsdisplay(int s)
{
  switch (s)
  {
  case 0:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso16_tr);
    u8g2.setCursor(1, 20);
    u8g2.printf("%02d.%02d.%02d-%d", (Yea % 100), Mon, Day, Wee);
    u8g2.setCursor(98, 20);
    u8g2.printf("%3d", int(Spe) + int((int(Spe * 10) % 10) / 5));
    u8g2.setCursor(4, 40);
    u8g2.printf("%02d:%02d", Hou, Min);
    u8g2.setCursor(63, 40);
    u8g2.printf("%2d %3d", int(Lat) + int((int(Lat * 10) % 10) / 5), int(Lng) + int((int(Lat * 10) % 10) / 5));
    u8g2.setCursor(0, 60);
    u8g2.printf("%3d", Deg);
    u8g2.setCursor(40, 60);
    u8g2.printf("%4dm", Alt);
    u8g2.setCursor(108, 60);
    u8g2.printf("%2d", Nsat);
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(1, 14);
    u8g2.printf("%02d.%02d", Mon, Day);
    u8g2.setCursor(64, 14);
    u8g2.printf("%02d %02d %02d", Hou, Min, Sec);
    u8g2.setCursor(81, 12);
    u8g2.printf(":");
    u8g2.setCursor(104, 12);
    u8g2.printf(":");
    u8g2.setCursor(18, 30);
    u8g2.printf("%dm", Alt);
    if (Nsat >= 0 && Nsat <= 9)
      u8g2.setCursor(104, 30);
    else
      u8g2.setCursor(95, 30);
    u8g2.printf("%d", Nsat);
    u8g2.setCursor(1, 46);
    u8g2.printf("%d°", Deg);
    u8g2.setCursor(1, 62);
    u8g2.printf("%s", Cou);
    u8g2.setFont(u8g2_font_logisoso32_tr);
    u8g2.setCursor(37, 64);
    u8g2.printf("%3d.%d", int(Spe), int(Spe * 10) % 10);
    u8g2.drawXBMP(1, 16, 16, 16, Mount);
    u8g2.drawXBMP(112, 16, 16, 16, Satellite);
    u8g2.sendBuffer();
    break;
  }
  case 2:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(18, 14);
    u8g2.printf("%4d.%02d.%02d-%d", Yea, Mon, Day, Wee);
    u8g2.setCursor(33, 30);
    u8g2.printf("%02d %02d %02d", Hou, Min, Sec);
    u8g2.setCursor(50, 28);
    u8g2.printf(":");
    u8g2.setCursor(73, 28);
    u8g2.printf(":");
    if (int(Lat) >= 0 && int(Lat) <= 9)
      u8g2.setCursor(29, 46);
    else
      u8g2.setCursor(20, 46);
    u8g2.printf("%d.%06d°%s", int(Lat), int((Lat * 1000000)) % 1000000, NS.value());
    if (int(Lng) >= 0 && int(Lng) <= 9)
      u8g2.setCursor(29, 62);
    else if (int(Lng) >= 10 && int(Lng) <= 99)
      u8g2.setCursor(20, 62);
    else
      u8g2.setCursor(11, 62);
    u8g2.printf("%d.%06d°%s", int(Lng), int((Lng * 1000000)) % 1000000, WE.value());
    // u8g2.setCursor(100, 46);
    // u8g2.printf("%s", NS.value());
    // u8g2.setCursor(100, 62);
    // u8g2.printf("%s", WE.value());
    u8g2.sendBuffer();
    break;
  }
  case 3:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso62_tn);
    if (Spe < 10)
      u8g2.setCursor(44, 63);
    else if (Spe >= 10 && Spe < 100)
      u8g2.setCursor(24, 63);
    else if (Spe >= 100)
      u8g2.setCursor(4, 63);
    u8g2.printf("%d", int(Spe) + int((int(Spe * 10) % 10) / 5));
    u8g2.sendBuffer();
    break;
  }
  }
}
/////////////////////////////////////////

/*
case 0:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(2, 14);
    u8g2.printf("%02d.%02d.%02d-%d\n", (Yea % 100), Mon, Day, Wee);
    u8g2.setCursor(10, 30);
    u8g2.printf("%02d %02d\n", Hou, Min);
    u8g2.setCursor(27, 28);
    u8g2.printf(":");
    if (Spe <= 9)
      u8g2.setCursor(112, 14);
    else if (Spe >= 10 && Spe <= 99)
      u8g2.setCursor(103, 14);
    else
      u8g2.setCursor(94, 14);
    u8g2.printf("%d\n", Spe);
    if (Lat <= 9)
      u8g2.setCursor(71, 30);
    else
      u8g2.setCursor(62, 30);
    u8g2.printf("%d\n", int(Lat));
    if (Lng <= 9)
      u8g2.setCursor(104, 30);
    else if (Lng >= 10 && Lng <= 99)
      u8g2.setCursor(95, 30);
    else
      u8g2.setCursor(86, 30);
    u8g2.printf("%d\n", int(Lng));
    u8g2.sendBuffer();
    break;
  }
  case 1:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(15, 14);
    u8g2.printf("%4d.%02d.%02d-%d\n", Yea, Mon, Day, Wee);
    u8g2.setCursor(30, 30);
    u8g2.printf("%02d %02d %02d\n", Hou, Min, Sec);
    u8g2.setCursor(47, 28);
    u8g2.printf(":");
    u8g2.setCursor(70, 28);
    u8g2.printf(":");
    u8g2.sendBuffer();
    break;
  }
  case 2:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    if (int(Lat) >= 10 && int(Lat) <= 99)
      u8g2.setCursor(10, 14);
    else
      u8g2.setCursor(19, 14);
    u8g2.printf("%d.%06d", int(Lat), int((Lat * 1000000)) % 1000000);
    if (int(Lng) >= 0 && int(Lng) <= 9)
      u8g2.setCursor(19, 30);
    else if (int(Lng) >= 10 && int(Lng) <= 99)
      u8g2.setCursor(10, 30);
    else
      u8g2.setCursor(1, 30);
    u8g2.printf("%d.%06d", int(Lng), int((Lng * 1000000)) % 1000000);
    u8g2.setCursor(100, 14);
    u8g2.printf("%s", NS.value());
    u8g2.setCursor(100, 30);
    u8g2.printf("%s", WE.value());
    u8g2.sendBuffer();
    break;
  }
  case 3:
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_te);
    u8g2.setCursor(1, 30);
    u8g2.printf("%s", Cou);
    u8g2.setCursor(1, 14);
    u8g2.printf("%d\n", Deg);
    u8g2.setFont(u8g2_font_logisoso32_tn);
    u8g2.setCursor(63, 32);
    u8g2.printf("%3d\n", Spe);
    u8g2.sendBuffer();
    break;
  }*/
/*u8g2.setFont(u8g2_font_logisoso16_tr);
   u8g2.setCursor(9, 24);
   u8g2.printf("%4d.%02d.%02d-%d", Yea, Mon, Day, Wee);
   u8g2.setCursor(28, 56);
   u8g2.printf("%02d:%02d:%02d", Hou, Min, Sec);*/
/*{
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_logisoso16_tr);
   u8g2.setCursor(1, 24);
   u8g2.printf("%3d.%06d", int(Lat), int((Lat * 1000000)) % 1000000);
   u8g2.setCursor(1, 56);
   u8g2.printf("%3d.%06d", int(Lng), int((Lng * 1000000)) % 1000000);
   u8g2.setFont(u8g2_font_helvB18_tr);
   u8g2.setCursor(100, 25);
   u8g2.printf("%s", NS.value());
   u8g2.setCursor(100, 57);
   u8g2.printf("%s", WE.value());
   u8g2.sendBuffer();
   break;
 }
 case 4:*/