#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "joystick.h"
#include "lcd.h"
#include "drinks_menu.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "selection_1.h"

int selection = 0;

void selectDrinkScreen();
void confirmationScreen();
void readJoystick();
void welcomeScreen();

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");
  pinMode(joyClick, INPUT_PULLUP);

  setupPumps();
  loadDrinks();
  setupLcd();
  welcomeScreen();
}

void loop()
{
  DrinksMenu drinksMenu;
  drinksMenu.lcd = &lcd;  
  for(int i=0; i <= lastDrinkId(); i++) 
    drinksMenu.addDrink(drinks[i]);  
  drinksMenu.start();
}

void welcomeScreen()
{
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("Barduino v1.0");
  for (byte i = 0; i < 3; i++)
  {
    lcd.setCursor(i + 8, 2);
    lcd.print(".");
    delay(500);
  }
}
