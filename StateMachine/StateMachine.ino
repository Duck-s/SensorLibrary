//The EXP32-CAM is seperate from the 


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


bool idleState = 0;
uint8_t state;
String InputPassword = "";
int timeToPassword = 0;

void setup() {
  Init();         //Needed for the thiny
  //IrInit();
  Serial.begin(9600);
  RGBSet("red");  //Indicates Test Starting
  TestInit();     //Runs through basic tests to see responces not 100% accurate
  RGBSet("Green");
  state = 0;                                                                   //Running a state machine so setting state to 0
  attachInterrupt(digitalPinToInterrupt(GetDoorSensPin()), DoorOpen, RISING);  //Not tested yet may need FALLING
  attachInterrupt(digitalPinToInterrupt(GetSwitchPin()), IdleSwitch, CHANGE);  //IDLE switch
}

void loop() {
  
 
  if (state == 0) {  //State 0 is standard checks for damage/danger
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
     //UPDTE TIME ON LED SCREEN
    delay(70);
  }

  else if (state == 1) {
    //Double Check shits still hitting the fan
    //Then send data to server thingy
    delay(70);
    state = idleState;  //Even if shit hitting fan resume default scan
  }

  else if (state == 2){
    PassivebuzzerOn();
    //DISPLAY on led screen shits good you may continue.
    state = idleState;
    
  }

  else if (state == 3) {
    if (!timeToPassword) {
      timeToPassword = millis();
      SetBuzzTimer(millis());
      ActiveBuzzerOn();
      RGBSet("red");
      //TURN I2C SCREEN ON REQUESTING PASSWORD
      //Check use password
    } else {
      if (InputPassword == SET_PASSWORD) {
        state = 2;
        timeToPassword = 0;
        RGBSet("Green");

        //SendServer WHO IN BUILDING
        state = idleState;

      } else {
        if (timeToPassword - 10000 > millis()) {
          state = 4;  //INTRUDER SHIT PANIC
        }
      }
    }
    ActiveBuzzerOn();
  }

  else if (state == 4) {
    //Send signal to Server Intruder IN
    //no idea what else.....

    state = idleState;
  }


  Serial.println(state);
}


void IdleSwitch(){
  if(idleState)
  {
    idleState = 0;
  }
  else
    idleState = 5;
}


void DoorOpen() {
  state = 3;
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
  //IR SEND NEEDS TO BE ON PWM PIN 3 FOR THIS LIB
  //irsend.sendRC5(0x0, 8);
  //send 0x0 code (8 bits)
}
