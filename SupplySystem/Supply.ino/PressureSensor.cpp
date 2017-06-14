#include "PressureSensor.h"
#include <arduino.h>

PressureSensor::PressureSensor(int Pin)
:pin(Pin)
{}

int PressureSensor::GetPressure()
{
  int measuredValue = analogRead(pin); 
  int pressureValue = map(measuredValue, 0, 921, 0, 25000); //calculated to Pa from datasheet
  return pressureValue;
}
