#pragma once
#include <Arduino.h>

class Pump
{
public:  
  Pump(String name, int pumpNo);
  String name;  
  int pumpNo;  
  void on();
  void off();
  void reverse();
  
protected:  
  int pin1;
  int pin2;
  const byte pump0pin0 = 30;  

};