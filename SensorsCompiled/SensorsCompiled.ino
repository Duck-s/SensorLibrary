#include "Functions.h"
#include <IRremote.h>  
//Dont ask me why but Ir dosent work in the FUNCTIONS lib
//Some Definition error....

IRrecv irrecv(GetIrInPin());
decode_results results;
IRsend irsend;  //IRSEND

void IRSend();
void IRIn();
void IRInit();


void setup() {
  Serial.begin(9600);
  Init();         //Needed for the thiny
  TestInit();     //Runs through basic tests not 100% accurate
}

void loop() {

delay(100);
}




void IRSend(uint32_t message, uint8_t LengthInBits) {
  irsend.sendRC5(message, LengthInBits);      //Uses RC5 protocall
  delay(30);
}

void IRIn() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

void IrInit(){
  irrecv.enableIRIn();
  irrecv.blink13(true);
  IrSender.begin(3);
  //IR SEND NEEDS TO BE ON PWM PIN 3 FOR THIS LIB
  //irsend.sendRC5(0x0, 8);
  //send 0x0 code (8 bits)
}
