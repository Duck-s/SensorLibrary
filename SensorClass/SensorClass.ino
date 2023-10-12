#include "SensorClass.h"
 SensorClass sensors;

void setup() {

Serial.begin(9600);
}

void loop() {
 
  // put your main code here, to run repeatedly:
Serial.print(sensors.GetTempOneWire());


}
