#include "Functions.h"

void setup() {
Init();
Serial.begin(9600);
}


void loop() {
  delay(100);
  IrInput();
  
}
