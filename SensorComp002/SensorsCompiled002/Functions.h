#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <DHT11.h>  //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <OneWire.h>            //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON



void Init();  //FOR ANYTHING THAT NEEDS INITIALIZATION

int FloodSens();

float GetTempOneWire();

void PassivebuzzerOn(int BuzPin);

void ActiveBuzzerOn(int StartTime, int BuzPin);

int SoundSens();

long GetDistance();

int GetHumidity();

int GetTemp();

bool TapSens();

bool ShockSens();

bool IrInput();

void IrOutput();

int GetIrInPin();

int GetOneWireTempSensPin();

int GetDHT11Pin();

static DHT11 dht11(GetDHT11Pin());

static OneWire oneWire(GetOneWireTempSensPin());
static DallasTemperature sensors(&oneWire);




#endif  //FUNCTIONS_H
