#include "Functions.h"
#include <IRremote.h>
#include "Secrets.h"
//Dont ask me why but Ir dosent work in the FUNCTIONS lib
//Some Definition error....

IRrecv irrecv(GetIrInPin());
decode_results results;
IRsend irsend;  //IRSEND

void IRSend();
void IRIn();
void IRInit();


void setup() {
  Init();  //Needed for the thiny
  Serial.begin(9600);
  RGBSet("red");  //Indicates Test Starting

  //test should take about a second
  //Runs through basic tests to see see functions respond not 100% accurate
  //Should give rough idea if sensors are working
  TestInit();  

  //IrInit(); //For Ir stuff lp WANTS :( 

  RGBSet("Green");
}

void loop() {

    if (FloodSens() > 150) {
      RGBSet("red");
      Serial.print("FloodSensor \t");
      Serial.println(FloodSens());
      state = 1;
    }
    if (SoundSens() > 900) {
      RGBSet("red");
      Serial.print("SoundSens \t");
      Serial.println(SoundSens());
      state = 1;
    }
    if (GetHumidity() > 40) {
      RGBSet("red");
      Serial.print("Humidity \t");
      Serial.println(GetHumidity());
      state = 1;
    }
    if (GetTemp() > 25) {
      RGBSet("red");
      Serial.print("Temperature \t");
      Serial.println(GetTemp());
      state = 1;
    }
    delay(70);
 
}



void IRSend(uint32_t message, uint8_t LengthInBits) {
  irsend.sendRC5(message, LengthInBits);  //Uses RC5 protocall
  delay(30);
}

void IRIn() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

void IrInit() {
  irrecv.enableIRIn();
  irrecv.blink13(true);
  IrSender.begin(3);
  //IR SEND NEEDS TO BE ON PWM PIN 3 FOR THIS LIBRARY
  //irsend.sendRC5(0x0, 8); //sends 0x0 code (8 bits)
  
}
