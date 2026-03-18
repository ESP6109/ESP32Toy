// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 5.0.1
// Building
// Release at 2026.03.09 21:06
#include <Arduino.h>
#include "esp32-hal-cpu.h"
#include <driver/gpio.h>

#include "BuSw.h"
#include "Clock.h"
#include "DaTi.h"
#include "GPS.h"
#include "Joy.h"
// #include "Joystick.h"
#include "LCD.h"
#include "Power.h"
#include "Weather.h"
// #include "Wheel.h"
#include "WIFIset.h"

// 主界面图标
/////////////////////////////////////////
extern int menuicon[][4];
/////////////////////////////////////////

// 设置图标
/////////////////////////////////////////
extern int settingsicons[][2];
/////////////////////////////////////////

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
void setup();
void loop();
/////////////////////////////////////////
