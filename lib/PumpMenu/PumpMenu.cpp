#include <Arduino.h>
#include <Mixer.h>
#include <Joystick.h>
#include <PumpMenu.h>
#include <Pumps.h>

PumpMenu::PumpMenu(String verb) {
  this->verb = verb;
  title = verb + " menu";

  for(byte i=0; i < PUMPS; i++) {
    items[itemCount++] = verb + " " + String(i);
  }
  items[itemCount++] = verb + " all";
  items[itemCount++] = "Exit";
  exitItemNo = itemCount - 1;
}

void PumpMenu::selectItem()
{
  lcd->clear();
  lcd->setCursor(6, 1);
  lcd->print(items[selection]);

  lcd->setCursor(6, 3);
  lcd->print("[ Stop ]");

  if (selection < PUMPS) {
    pumpOn(selection);
  } else {
    for (byte i = 0; i < PUMPS; i++) {
      if (verb == "Prime") {         
        pumpOn(i);
      } else {
        pumpReverse(i);
      }
    }
  }

  do
  {
    readJoystick();
  } while (clicked != 0);
  waitForDepress();

  allPumpOff();
}

