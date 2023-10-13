#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <DHT11.h>              //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <OneWire.h>            //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON

extern int buzzerTimer;

void Init();  //FOR ANYTHING THAT NEEDS INITIALIZATION
void TestInit();
void PassivebuzzerOn(int BuzPin);
void ActiveBuzzerOn(int StartTime, int BuzPin);
void RelayOn();
void RelayOff();
void SetBuzzTimer();

bool JoystickPos(int &x, int &y);
bool MotionSens();
bool TapSens();
bool ShockSens();

int FloodSens();
int SoundSens();
int GetHumidity();
int GetTemp();
int GetIrInPin();             //GetPinFor for troubleshooting
int GetOneWireTempSensPin();  //GetPinFor for troubleshooting
int GetDHT11Pin();            //GetPinFor for troubleshooting

float GetTempOneWire();

long GetDistance();

static DHT11 dht11(GetDHT11Pin());
static OneWire oneWire(GetOneWireTempSensPin());
static DallasTemperature sensors(&oneWire);     


#endif  //FUNCTIONS_H