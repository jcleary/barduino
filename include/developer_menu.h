#pragma once
#include <Arduino.h>
#include "menu.h"

class DeveloperMenu : public Menu
{
public:  
  DeveloperMenu();
  
protected:    
  void selectItem();  
  void primeAllPumps();
  void purgeAllPumps();  
};