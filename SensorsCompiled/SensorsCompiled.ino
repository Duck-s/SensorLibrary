#include "Functions.h"
#include <IRremote.h> //Dont ask me why but Ir dosent work in the FUNCTIONS lib
                      //Some Definition error....

IRrecv irrecv(GetIrInPin());
decode_results results;

IRsend irsend;  //IRSEND




void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  IrSender.begin();

  Init(); //Needed for the thiny

}

void loop(){
 IRIn();
}


void IRSend()
{
  irsend.sendNEC(0x1, 8);
  delay(30);
}

void IRIn()
{
   if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}
