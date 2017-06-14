#include "Valve.h"
Valve::Valve(int pin): valvePin(pin)
{
  pinMode(valvePin, OUTPUT);
  //Serial.println("In valve class");
  isOpen = true;
}
void Valve::Open(void)
{
  if (isOpen == false)
  {
    digitalWrite(valvePin, LOW);
    isOpen = true;
  }

}
void Valve::Close(void)
{
  if (isOpen == true)
  {
    digitalWrite(valvePin, HIGH);
    isOpen = false;
  }
}
