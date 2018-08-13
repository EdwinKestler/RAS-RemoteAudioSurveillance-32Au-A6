#include "arduino.h"
#include"a6modem.h"

a6modem::a6modem(int pin_off,int pin_sleep,int pin_on){
  pinMode(pin_sleep, OUTPUT);
  pinMode(pin_on, OUTPUT);
  pinMode(pin_off,OUTPUT);
  _pinsleep = pin_sleep;
  _pinon = pin_on;
  _pinoff = pin_off;
}

void a6modem::mBeggin(){
  digitalWrite(_pinsleep, HIGH); 
  digitalWrite(_pinoff, LOW); 
  digitalWrite(_pinon, LOW); 
  Serial.println(F("After 5s, modemStarted!!"));
  delay(5000);  
}

void a6modem::mOn(){
  digitalWrite(_pinon, HIGH); 
  delay(3000);       
  digitalWrite(_pinon, LOW);
  Serial.println(F("A6 Power ON!"));
  delay(1000);
}

void a6modem::mOff(){
   digitalWrite(_pinoff, HIGH); // power off A6
   delay(2000);
   digitalWrite(_pinoff, LOW);
   Serial.println(F("A6 power off!"));
   delay(1000);
}

void a6modem::mRst(){
  Serial.println(F("A6 resetting!")); 
  Serial.println(F("turning modem A6 off!")); 
  digitalWrite(_pinoff, HIGH); // power off A6
  delay(2000);
  digitalWrite(_pinoff, LOW);
  delay(1000);
  Serial.println(F("turning modem A6 back on!!!"));
  digitalWrite(_pinon, HIGH); 
  delay(3000);       
  digitalWrite(_pinon, LOW);
  Serial.println(F("A6 Power ON!"));
  Serial.println(F("You may receive the AT   OK"));
  delay(5000); 
}

void a6modem::mSleep(){
  Serial.println(F("A6 go to sleep now!"));
  digitalWrite(_pinsleep, LOW);  //sleep
  delay(2000);
}

void a6modem::mWakeup(){
  digitalWrite(_pinsleep, HIGH);   // wake up
  delay(1000);
  Serial.println(F("A6 WAKE UP!")); 
}


