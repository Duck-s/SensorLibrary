#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <DHT11.h>  //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <IRremote.h>
#include <OneWire.h>            //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON

class SensorClass{

public:

SensorClass();
~SensorClass();



decode_results results;

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

IRrecv irrecv;
OneWire oneWire;
DallasTemperature sensors;
IRsend irsend;  //IR SEND NEEDS TO BE ON PWM PIN 3... IDK WHY
//irsend.sendRC5(0x0, 8); //send 0x0 code (8 bits)
};


#endif  //FUNCTIONS_H
