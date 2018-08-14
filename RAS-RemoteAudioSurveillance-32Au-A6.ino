#include "a6modem.h"
#include "RASsettings.h"
#include<stdio.h>
#include<string.h>
#define DEBUG true

//------------------------------------------------------------------------------------FSM Settings
#define STATE_IDLE                     0
#define STATE_POWER_MODEM_ON           1
#define STATE_DIAL_UP                  2
#define STATE_HANG_UP                  3
#define STATE_POWER_MODEM_OFF          4

#define LINE_BUSY                      1
#define LINE_FREE                      0

int fsm_state;
int call_state;
a6modem A6module(4,5,8); //define pins to set A6 modem to Sleep mode, turn On, turn Off the Modem

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8,OUTPUT);
  Serial.println(F("DIAL PROGRAM START:"));
  A6module.mBeggin();
  fsm_state = STATE_IDLE; //inciar el estado del la maquina de stado finito
  call_state = LINE_FREE;
}

 void loop() {
  switch(fsm_state){ //
  case STATE_IDLE: // hacer cuando el estado sea IDLE
  if(millis() - lastUPDATEMillis > 60*UInterval) {
    lastUPDATEMillis = millis(); //Actulizar la ultima hora de envio
    fsm_state = STATE_POWER_MODEM_ON;
  }
  break;
  
  case STATE_POWER_MODEM_ON: //
  Serial.println(F("POWERING UP MODEM!!"));
  A6module.mOn();
  delay(1000);
  fsm_state = STATE_DIAL_UP;
  break; 
  
  case STATE_DIAL_UP:
  if(call_state == LINE_FREE ){
    Serial.println(F("DIALING UP NUMBER"));
    sendData( "AT",1000,DEBUG); //TEST AND MAKE CALL
    delay(1000);
    call();    
  }
  
  if(millis() - lastCALLMillis > 2*60*UInterval) {
    lastCALLMillis = millis(); //Actulizar la ultima hora de envio
    call_state = LINE_FREE;
    fsm_state = STATE_HANG_UP; 
  }
  
  break;
  
  case STATE_HANG_UP:
  Serial.println(F("HANGIN UP THE CALL"));
  sendData( "ATH",1000,DEBUG);
  fsm_state = STATE_POWER_MODEM_OFF;
  break;   
  
  case STATE_POWER_MODEM_OFF:
  Serial.println(F("POWERING OFF THE MODEM TO SAVE BATTERY"));
  Serial.println("A6 Test complete!");
  A6module.mOff();
  fsm_state = STATE_IDLE;   
  break;
  }
 }
 

void call(void){
  sendData( "AT+CSQ",1000,DEBUG);
  delay(1000);
  sendData("AT+SNFS=0",1000,DEBUG);
  delay(1000);
  sendData("ATD50232415907;",5000,DEBUG);
  delay(1000);
  call_state = LINE_BUSY;
}

String sendData(String command, const int timeout, boolean debug){
  String response = "";
  Serial1.println(command);
  long int time = millis();
  while( (time+timeout) > millis()){
    while(Serial1.available()){
      char c = Serial1.read();
      response+=c;
    }
  }
  if(debug){
    Serial.print(response);
  }
  return response;
}

 /*if(millis() - lastUPDATEMillis > 60*UInterval) {
    A6module.mOn();
    delay(1000);
   sendData( "AT",1000,DEBUG); //TEST AND MAKE CALL
   delay(1000);
   call();
   Serial.println("A6 Test complete!");
   A6module.mOff();
   lastUPDATEMillis = millis(); //Actulizar la ultima hora de envio
   }*/


