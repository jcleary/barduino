
#include <Arduino.h>
#include "lcd.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void setupLcd()
{
  lcd.init();
  lcd.backlight();
}