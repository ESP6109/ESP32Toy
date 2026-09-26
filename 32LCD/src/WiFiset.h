#ifndef WIFI_h
#define WIFI_h

#include <Arduino.h>
#include <LCD.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "BuSw.h"
#include "Joystick.h"

// WIFI列表
/////////////////////////////////////////
extern const char *ssid[];
extern const char *pwd[];
/////////////////////////////////////////

//
/////////////////////////////////////////
// int W_con = 0;
extern int wifiicons[];
/////////////////////////////////////////

void WIFIchs(int *);
void WIFIconnect();

#endif
