#include "Pump.h"

Pump::Pump(int pressure, PressureSensor sensor)
:airPressure(pressure), sensor(sensor), (pin, pin)
{}

int Pump::Compare()
{
  int sensorValue = sensor->GetPressure();
  return sensorvalue; 
}

void Pump::KeepPressure()
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
