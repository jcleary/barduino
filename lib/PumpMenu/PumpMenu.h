#pragma once
#include <Arduino.h>
#include <Menu.h>

class PumpMenu : public Menu
{
public:  
  PumpMenu(String verb);  

protected:  
  void selectItem();    
  void startPump(int pumpNo);
  String verb;
};