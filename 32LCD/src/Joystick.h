#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>

void joystick(int *, int *);

// 摇杆接口
/////////////////////////////////////////
//(0,0)
//              (4095,4095)
// GND
// 5V(3.3V)
#define X 34
#define Y 32
/////////////////////////////////////////

// 计时
/////////////////////////////////////////
int timer1, timer2; // 摇杆计时
/////////////////////////////////////////

// 摇杆
/////////////////////////////////////////
void joystick(int *C_x, int *C_y)
{
  int VRX = analogRead(X);
  int VRY = analogRead(Y);
  // int VSW = analogRead(SW);//!!!!
  if (millis() - timer1 >= 250)
  {
    if (VRX >= 2870)
      (*C_x)++;
    else if (VRX <= 890)
      (*C_x)--;
    if (VRY >= 2870)
      (*C_y)++;
    else if (VRY <= 890)
      (*C_y)--;
    timer1 = millis();
  }
}
/////////////////////////////////////////

#endif