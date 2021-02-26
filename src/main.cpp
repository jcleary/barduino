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

void drawScreen();
void confirmationScreen();
void readJoystick();
void pour();
void welcomeScreen();

void setup()
{
  Serial.begin(115200);
  pinMode(joyClick, INPUT_PULLUP);

  welcomeScreen();
  setupPumps();
  loadDrinks();
  drawScreen();
}

void loop() 
{
  readJoystick();

  if (yPosition < upThreshold && selection > 0) {     
    selection -= 1;
    drawScreen();
    delay(500);
  } else if (yPosition > downThreshold && selection < (MAX_DRINKS - 1)) {    
    selection += 1;
    drawScreen();
    delay(500);
  } else if (clicked == 0) {
    confirmationScreen();
    drawScreen();
    delay(500);
  } else if (xPosition > rightThreshold) {
    pumpOn(0);
    pumpOn(1);
    delay(1000);

    pumpOff(0);
    pumpOff(1);
  } else if (xPosition < leftThreshold) {
    pumpReverse(0);
    pumpReverse(1);
    delay(1000);

    pumpOff(0);
    pumpOff(1);
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
        pour();
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

void drawScreen()
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
    if (drink >= 0 && drink < (MAX_DRINKS)) {
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


void pour()
{
  // TODO: rewrite
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Mixing ...");
  lcd.setCursor(0,1);
  lcd.print(drinks[selection].name);

  dispense(drinks[selection]);

  for(int i=0; i < 20; i++) {
    lcd.setCursor(i,3);
    lcd.print('>');
    delay(200);
  }
}

void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}