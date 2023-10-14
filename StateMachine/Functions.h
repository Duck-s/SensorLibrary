#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <DHT11.h>              //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <OneWire.h>            //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON



void Init();  //FOR ANYTHING THAT NEEDS INITIALIZATION
void TestInit();
void PassivebuzzerOn();
void ActiveBuzzerOn();
void RelayOn();
void RelayOff();
void SetBuzzTimer(int time);
void RGBSet(String color);

bool JoystickPos(int &x, int &y);
bool MotionSens();
bool TapSens();
bool ShockSens();
bool DoorAjar();

int FloodSens();
int SoundSens();
int GetHumidity();
int GetTemp();
int GetIrInPin();             //GetPinFor for troubleshooting
int GetOneWireTempSensPin();  //GetPinFor for troubleshooting
int GetDHT11Pin();            //GetPinFor for troubleshooting
int GetDoorSensPin();
int GetSwitchPin();

float GetTempOneWire();

long GetDistance();

static DHT11 dht11(GetDHT11Pin());
static OneWire oneWire(GetOneWireTempSensPin());
static DallasTemperature sensors(&oneWire);     


#endif  //FUNCTIONS_H