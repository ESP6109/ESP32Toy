// ESP32_LCD_GPS_Project
// Start at 2024.11.21 16:19:16
// Build Version 5.1.9
// Building
// Release at 2026.04.01 19:56

// #define ARDUINO_USB_MODE 1

// #define ARDUINO_USB_CDC_ON_BOOT 1
// #define USE_ESP_IDF_LOG 1
// #include "esp_log.h"
// const char *TAG = "MAIN";

// #if !define CORE_DEBUG_LEVEL
// #define CORE_DEBUG_LEVEL 5
// #endif
// #if !define ARDUHAL_LOG_LEVEL
// #define ARDUHAL_LOG_LEVEL 5
// #endif

#ifndef main_h
#define main_h

#include <Arduino.h>
#include <esp32-hal-cpu.h>
#include <driver/gpio.h>
#include <Freertos/Freertos.h>

#include "Backlight.h"
#include "BuSw.h"
#include "Clock.h"
#include "Dashboard.h"
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
extern int settingsicons[][3];
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

#endif