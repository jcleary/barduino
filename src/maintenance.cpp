#include <Arduino.h>
#include "maintenance.h"
#include "lcd.h"

void maintenanceMenu()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Maintenance Menu");
  delay(3000);
}