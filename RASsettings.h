/*
  RASsettings.h - Library for setting parameters for makiong calls with AI thinkers A6 modem.
  with Arduino Leonardo 32AU
  Created by Edwin Kestler, June 25 , 2018.
  Released into the public domain.
*/
unsigned long lastUPDATEMillis;                                       //Variable para llevar conteo del tiempo desde la ultima publicacion 
unsigned long lastCALLMillis;                                       //Variable para llevar conteo del tiempo desde la ultima publicacion 
unsigned long UInterval     = 1000UL;                                 //Variable configurable remotamente sobre el interbalo de publicacion

