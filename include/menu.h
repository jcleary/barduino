#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Menu
{
public:  
  void start();
  void refreshMenu();
  virtual void selectItem() {} ;
  virtual void selectSecretItem() {} ;
  LiquidCrystal_I2C * lcd;

protected:
  int selection = 0;
  int menuItems = 0;
  String options[10];
  String menuTitle;
  
};