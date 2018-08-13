/*
  a6modem.h - Library for makiong calls with AI thinkers A6 modem.
  with Arduino Leonardo 32AU
  Created by Edwin Kestler, June 25 , 2018.
  Released into the public domain.
*/

#ifndef a6modem_h
#define a6modem_h

#include "Arduino.h"

class a6modem{
  public:
    a6modem(int pin_sleep, int pin_on, int pin_off);
    void mBeggin();
    void mOn();
    void mOff();
    void mSleep();
    void mWakeup();
    void mRst();
 private:
 int _pinsleep;
 int _pinon;
 int _pinoff;
};

#endif


