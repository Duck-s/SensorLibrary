#include "SensorClass.h"

#define OneWireTempSens 2   //SEPERATE TEMP SENS ONE WIRE
#define ShockPin 0          //SCHOCK DEVICE IS FOR BIG IMPACTS APPARENTLY..?
#define TapPin 0            //TAP SENSOR -- SUPER SENSIIVE
#define RedPin 0            //RGBLED
#define GreenPin 0          //RGBLED
#define bluePin 0           //RGBLED
#define FloodSensPin A0     //FLOOD DETECTION (ANALOG PIN)
#define SR04TrigPin A0      //HC-SR04 DISTANCE SENSOR (Analog) 5V
#define SR04EchoPin 0       //HC-SR04 DISTANCE SENSOR (Analog) 5V
#define SoundAnalogPin A0   //BIG SOUND SENSOR (ANALOG)
#define IrIn 0              //IR RECV PIN CAS LP WANTS US TO
#define ActiveBuzzerPin 0   // GUESS WHAT IT IS
#define PassiveBuzzerPin 0  // CMON GUESS
#define DHT11Pin 0

SensorClass::SensorClass(){
Init();
  IRrecv irrecv(GetIrInPin());
  OneWire oneWire(GetOneWireTempSensPin());
  DallasTemperature sensors(&oneWire);
  DHT11 dht11(DHT11Pin); //TEMP HUMIDITY SENSOR CHANGE PIN FROM 0
}
SensorClass::~SensorClass(){}

//DETECTS IMPACTS APPARENTLY
bool SensorClass::ShockSens() {
  int val = digitalRead(ShockPin);
  Serial.println(val);
  if (val == LOW) {
    Serial.println("Detect shock!");
    return 1;
  } else {
    return 0;
  }
}

//Caution Super sensitive 5V
//50/50 i had mine backwards so may neeed to swap return 0 and 1.
bool SensorClass::TapSens() {
  int val = digitalRead(TapPin);
  if (val == HIGH) {
    Serial.println("no Tap");
    return 0;
  } else {

    Serial.println("Tap");
    return 1;
  }
}






//GETS VALUE FOR FLOOD SENSOR
//ANYTHING > 100 IS PROBABLY BAD
int SensorClass::FloodSens() {
  return analogRead(FloodSensPin);
}

//HC-SR04 distance sensor
long SensorClass::GetDistance() {
  long duration, d;
  digitalWrite(SR04TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(SR04TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(SR04TrigPin, LOW);
  duration = pulseIn(SR04EchoPin, HIGH);
  d = (duration / 2) / 29.1;

  //DEBUG CAN BE REMOVED LATER
  Serial.print("Distance: ");
  Serial.print(d);
  Serial.println(" cm");

  //DO NOT REMOVE
  return d;
}

//Returns the analog value of BIG SOUND -- SMALL SOUND
//Can be tuned in proj for db level needed
int SensorClass::SoundSens() {
  return analogRead(SoundAnalogPin);
}

bool SensorClass::IrInput() {
  if (irrecv.decode(&results)) {
    if (results.value == 1) {
      return 1;
    } else {
      return 0;
    }
    Serial.println(results.value);
    irrecv.resume();
  }
}

void SensorClass::ActiveBuzzerOn(int StartTime, int BuzPin) {
  if (StartTime - millis() < 1000) {
    digitalWrite(BuzPin, HIGH);
    delay(1);
    digitalWrite(BuzPin, LOW);
    delay(1);
  }
}
//This DOES block the code and play a little jingle
void SensorClass::PassivebuzzerOn(int BuzPin) {

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(BuzPin, thisNote * 50, 500);
  }
}

float SensorClass::GetTempOneWire() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void SensorClass::IrOutput() {
  irsend.sendRC5(0x1, 8);
}

int SensorClass::GetIrInPin() {
  return IrIn;
}

int SensorClass::GetOneWireTempSensPin() {
  return OneWireTempSens;
}

void SensorClass::Init() {
  pinMode(ShockPin, INPUT);
  pinMode(TapPin, INPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(FloodSensPin, INPUT);
  pinMode(SR04TrigPin, OUTPUT);
  pinMode(SR04EchoPin, INPUT);
  pinMode(SoundAnalogPin, INPUT);
  pinMode(IrIn, INPUT);
  pinMode(ActiveBuzzerPin, OUTPUT);
  pinMode(PassiveBuzzerPin, OUTPUT);
  sensors.begin();
  
}


/*

//DHT11 GETS TEMP AND ERROR CHECKS
int SensorClass::GetTemp() {
  int temperature = dht11.readTemperature();
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
    return temperature;
  } else {
    if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM) {
      Serial.print("Temperature Reading Error: ");
      Serial.println(DHT11::getErrorString(temperature));
    }
  }
}


//DHT11 GETS HUMIDITY AND ERROR CHECKS
int SensorClass::GetHumidity() {
  int humidity = dht11.readHumidity();
  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
    return humidity;
  } else {
    if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM) {
      Serial.print("Humidity Reading Error: ");
      Serial.println(DHT11::getErrorString(humidity));
    }
  }
}

*/


