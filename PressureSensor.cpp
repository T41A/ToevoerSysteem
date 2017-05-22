#include "PressureSensor.h"

PressureSensor::PressureSensor(int Pin)
:pin(Pin)
{}

bool PressureSensor::Calibrate()
{
  //what is the best way to calibrate?
    return false;
}

int PressureSensor::GetPressure()
{
  int pressureValue = analogRead(pin); 
  //evt calculate to a more usable value
  return pressureValue;
}
