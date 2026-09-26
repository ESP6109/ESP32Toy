#ifndef DHTdata_h
#define DHTdata_h

#include <Arduino.h>
#include <DHTesp.h>
#include <Freertos/Freertos.h>

#include "BuSw.h"
#include "LCD.h"

#define DhtPin 3

static DHTesp Dht;

static TaskHandle_t *DHTTask;

extern float TemDH, TemDT;
extern float DHum, DTem;
extern float MaxHum, MinHum;
extern float MaxTem, MinTem;
extern int DHTdelay;
extern int DhtFlag;
void HTdata();

#endif