#include <Arduino.h>
#include <Pump.h>

Pump::Pump(String name, int pumpNo)
{
  this->name = name;
  this->pumpNo = pumpNo;
  pin1 = pump0pin0 + (pumpNo * 2);
  pin2 = pin1 + 1;

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void Pump::on()
{
  Serial.println("Pump " + String(pumpNo) + " on");
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void Pump::off()
{
  Serial.println("Pump " + String(pumpNo) + " off");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

void Pump::reverse()
{
  Serial.println("Pump " + String(pumpNo) + " reverse");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}
