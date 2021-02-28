#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// pins
const int yAxis = 7;
const int xAxis = 6;
const int joyClick = 52;

// thresholds
const int upThreshold = 422;
const int downThreshold = 622;
const int leftThreshold = 422;
const int rightThreshold = 622;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);  

int selection = 0;
int yPosition;
int xPosition;
int clicked;

void selectDrinkScreen();
void confirmationScreen();
void readJoystick();
void welcomeScreen();

void setup()
{
  Serial.begin(115200);
  pinMode(joyClick, INPUT_PULLUP);

  welcomeScreen();
  setupPumps();
  loadDrinks();
  selectDrinkScreen();
}

void loop() 
{
  readJoystick();

  if (yPosition < upThreshold && selection > 0) {     
    selection -= 1;
    selectDrinkScreen();
    delay(500);
  } else if (yPosition > downThreshold && selection < lastDrinkId()) {    
    selection += 1;
    selectDrinkScreen();
    delay(500);
  } else if (clicked == 0) {
    confirmationScreen();
    selectDrinkScreen();
    delay(500);
  } else if (xPosition > rightThreshold) {
    for(int i = 0; i < PUMPS; i++) pumpOn(i);
    delay(1000);
    for(int i = 0; i < PUMPS; i++) pumpOff(i);
  } else if (xPosition < leftThreshold) {
    for(int i = 0; i < PUMPS; i++) pumpReverse(i);
    delay(1000);
    for(int i = 0; i < PUMPS; i++) pumpOff(i);
  }

  delay(10);
}

void confirmationScreen()
{
  int select = 1;

  lcd.clear();

  lcd.setCursor((20 - drinks[selection].name.length()) / 2, 0);
  lcd.print(drinks[selection].name);

  lcd.setCursor(3, 2);
  lcd.print("[Hit me] Back ");

  delay(500);
  while (true) {
    readJoystick();

    if (clicked == 0) {
      if (select == 1) {
        pour(drinks[selection], lcd);
      }
      return;
    } else if (xPosition > rightThreshold) {
      select = 0;
      lcd.setCursor(3, 2);
      lcd.print(" Hit me [Back]");
    } else if (xPosition < leftThreshold) {
      select = 1;
      lcd.setCursor(3, 2);
      lcd.print("[Hit me] Back ");
    }

    delay(50);
  }
}

void selectDrinkScreen()
{
  int drink;

  // debug info
  Serial.print("Selection: ");
  Serial.print(selection);
  Serial.println(" " + drinks[selection].name);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select a drink:");

  lcd.setCursor(0, 2);
  lcd.print(">");
  for(int i = 0; i < 3; i++) {
    drink = selection - 1 + i;
    if (drink >= 0 && drink <= lastDrinkId()) {
      lcd.setCursor(1, i+1);
      lcd.print(drinks[drink].name);
    }
  }
}

void welcomeScreen()
{
  lcd.init();   
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Barduino v0.8");
  for(byte i=0; i < 3; i++) {
    lcd.setCursor(i+8,2);
    lcd.print(".");
    delay(1000);
  }
}



void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}