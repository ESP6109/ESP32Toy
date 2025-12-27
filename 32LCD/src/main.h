// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 4.4.8
// Building
// Release at 2025.11.11 15:36
#include <Arduino.h>
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
#include "WIFIset.h"

// 主界面图标
/////////////////////////////////////////
extern int menuicon[];
/////////////////////////////////////////

// 设置图标
/////////////////////////////////////////
extern int settingsicons[];
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
