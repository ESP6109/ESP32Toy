#ifndef DHTdata_h
#define DHTdata_h

#include <Arduino.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
#include <DHTesp.h>
#include <Freertos/Freertos.h>

#define DhtPin 3

static DHTesp Dht;

extern float TemDH, TemDT;
extern float DHum, DTem;

void getdht1(void *pvParameters);

#endif