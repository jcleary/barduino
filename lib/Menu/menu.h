#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Menu
{
public:  
  void start();
  void refreshMenu();
  LiquidCrystal_I2C * lcd;

protected:
  virtual void selectItem() {} ;
  virtual void selectSecretItem() {} ;
  int offset = 0;
  int selection = 0;
  int itemCount = 0;
  int exitItemNo = -1;
  String items[10];
  String title;
  
};