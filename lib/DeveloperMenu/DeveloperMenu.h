#pragma once
#include <Arduino.h>
#include <Menu.h>

class DeveloperMenu : public Menu
{
public:  
  DeveloperMenu();
  
protected:    
  void selectItem();  
  void showPumpMenu(String verb);
};