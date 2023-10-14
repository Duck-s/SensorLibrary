#include "Functions.h"


#define OneWireTempSens 0   //SEPERATE TEMP SENS ONE WIRE
#define DHT11Pin 0          //DHT11 PIN
#define ShockPin 0          //SCHOCK DEVICE IS FOR BIG IMPACTS APPARENTLY..?
#define TapPin 0            //TAP SENSOR -- SUPER SENSIIVE
#define FloodSensPin A0     //FLOOD DETECTION (ANALOG PIN)
#define RedPin 0            //RGBLED
#define GreenPin 0          //RGBLED
#define BluePin 0           //RGBLED
#define SR04TrigPin A0      //HC-SR04 DISTANCE SENSOR (Analog) 5V
#define SR04EchoPin A0      //HC-SR04 DISTANCE SENSOR (Analog) 5V
#define ProxSensPin 0       //PROXIMITY SENSOR
#define SoundAnalogPin A0   //BIG SOUND SENSOR (ANALOG)
#define ActiveBuzzerPin 0   //GUESS WHAT IT IS
#define PassiveBuzzerPin    //GUESS
#define PassiveBuzzerPin 0  //CMON GUESS
#define JoystickXPin A0     //JOYSTICK X
#define JoystickYPin A0     //JOYSTICK Y
#define JoyStickBttn 0      //JOYSTICK button
#define RelayPin 0          //RELAY PIN FOR MY G JAMIE
#define IrIn 0              //IR RECV PIN CAS LP WANTS US TO
#define DoorSensPin 0       //FOR MAGNETIC SWITCH
#define SwitchPin 0         //GENERAL TOGGLE SWITCH
int buzzerTimer;


//Testing that were receiving signals
//Not 100% accurate but should give a good sens of whats capable
void TestInit() {
  int testx, testy;
  JoystickPos(testx, testy);
  if (testx && testy) {
    Serial.println("Joystick\tYES");
  } else
    Serial.println("Joystick\tYNO");
  delay(100);

  if (GetTemp()) {
    Serial.println("DHT11Temperature \tYES");
  } else
    Serial.println("DHT11Temperature \tNO");
  delay(100);

  if (GetHumidity()) {
    Serial.println("DHT11Humidity \tYES");
  } else
    Serial.println("DHT11Temperature \tNO");
  delay(100);

  if (GetTempOneWire()) {
    Serial.println("18B20Humidity \tYES");
  } else
    Serial.println("18B20Humidity \tNO");
  delay(100);

  if (FloodSens()) {
    Serial.println("FloodSens \tYES");
  } else
    Serial.println("FloodSens \tNO");
  delay(100);

  if (MotionSens()) {
    Serial.println("MotionSens \tYES");
  } else
    Serial.println("MotionSens \tNO \tCurrently not detecting");
  delay(100);

  if (GetDistance()) {
    Serial.println("SR04Distance \tYES");
  } else
    Serial.println("SR04Distance \tYES");
  delay(100);

  if (SoundSens()) {
    Serial.println("SoundSense \tYES");
  } else
    Serial.println("SoundSense \tNO");
  delay(100);
}

//Controls... The RGB led
void RGBSet(String color) {
  color.toLowerCase();
  if (color == "red") {
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, LOW);
  } else if (color == "green") {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(BluePin, LOW);
  }
  if (color == "blue") {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
  }
  if (color == "brown") {
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(BluePin, LOW);
  }
  if (color == "magenta" || (color = "purple")) {
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
  }
  if (color == "teal" || (color = "lightblue")) {
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
  }
  if (color == "off") {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, LOW);
  }
}

//returns button needs x and y variables to change
//can be changed to return and int for direction
//requires decode tho so.... another day
bool JoystickPos(int &x, int &y) {
  x = analogRead(JoystickXPin);
  y = analogRead(JoystickYPin);
  return digitalRead(JoyStickBttn);
}

//Detects Impacts apparently
//theres a small chance its electric shock but im like 80% sure its not...
bool ShockSens() {
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
bool TapSens() {
  int val = digitalRead(TapPin);
  if (val == HIGH) {
    Serial.println("no Tap");
    return 0;
  } else {

    Serial.println("Tap");
    return 1;
  }
}

//DHT11 returns temp and debugs
int GetTemp() {
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

//DHT11 returns humidity and debugs
int GetHumidity() {
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

//Gets current on floodsensor
//ANYTHING > 100 is probably bad
int FloodSens() {
  return analogRead(FloodSensPin);
}

//Returns the digital signal for motion sensor
bool MotionSens() {
  return digitalRead(ProxSensPin);
}

bool DoorAjar(){
  return digitalRead(DoorSensPin);
}

int GetDoorSensPin(){
  return DoorSensPin;
}

//HC-SR04 distance sensor
//Returns... distance
long GetDistance() {
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
//May need to tune the sensor with the pot
int SoundSens() {
  return analogRead(SoundAnalogPin);
}

//Sets the time since activebuzzer activated
//Makes it so it last a specific time without interrupt
void SetBuzzTimer(int time) {
  buzzerTimer = time;
}

//checks
void ActiveBuzzerOn() {
  if (buzzerTimer) {
    if (buzzerTimer - millis() < 1000) {
      digitalWrite(ActiveBuzzerPin, HIGH);
      delay(1);
      digitalWrite(ActiveBuzzerPin, LOW);
      delay(1);
    } else
      SetBuzzTimer(0);
  } else {
    SetBuzzTimer(millis());
    digitalWrite(ActiveBuzzerPin, HIGH);
    delay(1);
    digitalWrite(ActiveBuzzerPin, LOW);
    delay(1);
  }
}

//This DOES block the code and play a little jingle
//Jingle is generous...
void PassivebuzzerOn() {

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //pin8 output the voice, every scale is 0.5 sencond
    tone(PassiveBuzzerPin, thisNote * 50, 500);
  }
}

//Turns relay on
//Uses like 25W of power lol
void RelayOn() {
  digitalWrite(RelayPin, HIGH);
}

//Turns relay off
//Uses like 25W of power lol
void RelayOff() {
  digitalWrite(RelayPin, LOW);
}

//Gets Temperature with the Other Temp Sensor
float GetTempOneWire() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

//Gets pin cas IRremote is dumb
int GetIrInPin() {
  return IrIn;
}

//Gets One Wire Pin cas declared in Functions.h
//Using a class from a lib is annoying af
int GetOneWireTempSensPin() {
  return OneWireTempSens;
}

//Gets DHT11 pin for class
int GetDHT11Pin() {
  return DHT11Pin;
}

int GetSwitchPin(){
  return SwitchPin;
}
//Initializes pins and starts sensors
void Init() {
  pinMode(JoyStickBttn, INPUT);
  pinMode(ShockPin, INPUT);
  pinMode(TapPin, INPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(FloodSensPin, INPUT);
  pinMode(SR04TrigPin, OUTPUT);
  pinMode(SR04EchoPin, INPUT);
  pinMode(SoundAnalogPin, INPUT);
  pinMode(ActiveBuzzerPin, OUTPUT);
  pinMode(PassiveBuzzerPin, OUTPUT);
  pinMode(ProxSensPin, INPUT);
  pinMode(DoorSensPin, INPUT);
  sensors.begin();
}