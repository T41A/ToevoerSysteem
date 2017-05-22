#include "Pump.h"

Pump::Pump(int pressure, PressureSensor sensor)
:airPressure(pressure), sensor(sensor)
{}

int Pump::Compare()
{
  int sensorValue = sensor->GetPressure();
  int difference = airPressure - sensorValue;
  return difference; 
}

void Pump::KeepPressure()
{
  int difference = Compare();
  
}
