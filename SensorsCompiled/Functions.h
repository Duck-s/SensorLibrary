#include <DHT11.h>  //SPECIFICALLY THE LIBRARY BY DHRUBA SAHA
#include <IRremote.h>
#include <OneWire.h>  //SEPERATE DIGITAL TEMP SENSOR
#include <DallasTemperature.h>  //ONE WIRE ADDON

DHT11 dht11(0); //TEMP HUMIDITY SENSOR CHANGE PIN FROM 0
#define OneWireTempSens 2 //SEPERATE TEMP SENS ONE WIRE
#define ShockPin 0      //SCHOCK DEVICE IS FOR BIG IMPACTS APPARENTLY..?
#define TapPin 0        //TAP SENSOR SUPER SENSIIVE
#define RedPin 0        //RGBLED
#define GreenPin 0      //RGBLED
#define bluePin 0       //RGBLED
#define FloodSensPin A0 //FLOOD DETECTION (ANALOG PIN)
#define SR04TrigPin A0   //HC-SR04 DISTANCE SENSOR (Analog) 5V
#define SR04EchoPin 0   //(Analog) 5V
#define SoundAnalogPin A0 //BIG SOUND SENSOR (ANALOG)
#define IrIn 0        //IR RECV PIN CAS LP WANTS US TO
#define ActiveBuzzerPin 0  //
#define PassiveBuzzerPin 0 //


IRrecv irrecv(IrIn);
decode_results results;

IRsend irsend;  //IR SEND NEEDS TO BE ON PWM PIN 3... IDK WHY THO
//irsend.sendRC5(0x0, 8); //send 0x0 code (8 bits)


OneWire oneWire(OneWireTempSens);
DallasTemperature sensors(&oneWire);
//NEEDS sensors.begin(); //in setup

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

//Requires some setup found up top
bool IrInput();

void IrOutput();



