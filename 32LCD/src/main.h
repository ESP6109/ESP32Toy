// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 5.1.5
// Building
// Release at 2026.03.29 19:35
#include <Arduino.h>
#include <esp32-hal-cpu.h>
#include <driver/gpio.h>
#include <Freertos/Freertos.h>

#include "BuSw.h"
#include "Clock.h"
#include "DaTi.h"
#include "DHTdata.h"
#include "Dino.h"
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

//
/////////////////////////////////////////
PROGMEM const uint8_t Therm[32] =
    {0x80, 0x01, 0x80, 0x07, 0x80, 0x07, 0x80, 0x01, 0x80, 0x07, 0x80, 0x07, 0x80, 0x01, 0x80, 0x07,
     0x80, 0x07, 0x80, 0x01, 0xC0, 0x03, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xC0, 0x03};
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
