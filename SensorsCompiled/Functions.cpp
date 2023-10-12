#include "Functions.h"

//DETECTS IMPACTS APPARENTLY
bool ShockSens()
{
  int val = digitalRead(ShockPin);
  Serial.println(val);
  if (val == LOW)
  {
    Serial.println("Detect shock!");
    return 1;   
  }
  else 
  {
    return 0;
  }
}


//Caution Super sensitive 5V
//50/50 i had mine backwards so may neeed to swap return 0 and 1.
bool TapSens(){
  int val = digitalRead(TapPin); 
	if(val == HIGH)
	{
    Serial.println("no Tap");
    return 0;
	}
	else
	{
		
		Serial.println("Tap");
    return 1;
	}
}

//DHT11 GETS TEMP AND ERROR CHECKS
int GetTemp()
{
  int temperature = dht11.readTemperature();
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT )
    {
      return temperature;
    }
     else
    {
        if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Temperature Reading Error: ");
            Serial.println(DHT11::getErrorString(temperature));
        }
        
    }
}


//DHT11 GETS HUMIDITY AND ERROR CHECKS
int GetHumidity()
{
 int humidity = dht11.readHumidity();
  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        return humidity;
    }
     else
    {
        if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Humidity Reading Error: ");
            Serial.println(DHT11::getErrorString(humidity));
        }
    }
}


//GETS VALUE FOR FLOOD SENSOR
//ANYTHING > 100 IS PROBABLY BAD
int FloodSens()
{
  return analogRead(FloodSensPin);
}

//HC-SR04 distance sensor
long GetDistance()
{
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

//Returns the analog value of BIG SOUND
//Can be tuned in proj for db level needed
int SoundSens()
{
  return analogRead(SoundAnalogPin);
}

//Requires some setup found up top
bool IrInput()
{
  if (irrecv.decode(&results)) 
   { 
       if ( results.value == 1 )  
       {    
         return 1;
       }
       else
       {
         return 0;
       }     
    Serial.println(results.value);
    irrecv.resume(); 
   }
}

void ActiveBuzzerOn(int StartTime, int BuzPin)
{
  if(StartTime - millis() < 1000)
  { 
    digitalWrite(BuzPin,HIGH);
    delay(1);
    digitalWrite(BuzPin,LOW);
    delay(1);
  }
}
//This DOES block the code and play a little jingle
void PassivebuzzerOn(int BuzPin)
{
 
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(BuzPin, thisNote * 50, 500);
  }
}

float GetTempOneWire()
{
 sensors.requestTemperatures();
 return sensors.getTempCByIndex(0);
}

void IrOutput()
{
  irsend.sendRC5(0x1, 8);
}

void Init()
{ 
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