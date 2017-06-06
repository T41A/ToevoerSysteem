#include "Pump.h"

// hier gebeurt iets raars. Je constructor mist de derde parameter en in de tweede lijn snap ik de (pin, pin) niet
Pump::Pump(int pressure, PressureSensor sensor)
:airPressure(pressure), sensor(sensor), (pin, pin)
{}

int Pump::Compare()
{
  int sensorValue = sensor->GetPressure();
  return sensorvalue;
}

void Pump::KeepPressure() // parameter vergeten
{
  if (!enabled)
  {
    digitalWrite(pin, LOW);
  }
  else
  {
    int pressure = Compare();
    if (pressure > airPressure)
    {
    	digitalWrite(pin, LOW);
    }
    else if (pressure < airPressure)
    {
    	digitalWrite(pin, HIGH);
    }
  }
}
