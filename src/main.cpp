#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int yAxis = 7;
const int xAxis = 6;
const int joyClick = 52;
const int upThreshold = 422;
const int downThreshold = 622;
const int leftThreshold = 422;
const int rightThreshold = 622;

const int motor1pin1 = 30;
const int motor1pin2 = 31;

const int motor2pin1 = 32;
const int motor2pin2 = 33;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);  

int selection = 0;
int yPosition;
int xPosition;
int clicked;

void drawScreen();
void confirmationScreen();
void readJoystick();
void pour();

void setup()
{
  Serial.begin(115200);
  pinMode(joyClick, INPUT_PULLUP);

  lcd.init();   
  lcd.backlight();
  
  setupPumps();
  loadDrinks();
  drawScreen();

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
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
    Serial.println("pumping 1 & 2");
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    delay(1000);

    Serial.println("stopped");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor2pin1, LOW);
  } else if (xPosition < leftThreshold) {
    Serial.println("reversing 1 & 2");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    delay(1000);

    Serial.println("stopped");
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin2, LOW);
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


void pour()
{
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

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

}

void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}