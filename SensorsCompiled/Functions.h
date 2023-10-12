#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <DHT11.h>  //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <IRremote.h>     //ONLY 3.00 works for thios lib apparently
#include <OneWire.h>            //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON

static decode_results results;

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
static IRrecv irrecv(GetIrInPin());
static OneWire oneWire(GetOneWireTempSensPin());
static DallasTemperature sensors(&oneWire);
static IRsend irsend;  //IR SEND NEEDS TO BE ON PWM PIN 3... IDK WHY
//irsend.sendRC5(0x0, 8); //send 0x0 code (8 bits)



#endif  //FUNCTIONS_H