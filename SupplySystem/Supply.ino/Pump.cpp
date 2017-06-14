#include "Pump.h"
#include <arduino.h>

Pump::Pump(int pressure, int PumpPin, int SensorPin)
:airPressure(pressure), pin(PumpPin), PressureSensorPin(SensorPin)
{
	sensor = new PressureSensor(PressureSensorPin);
}

int Pump::Compare()
{
  int sensorValue = sensor->GetPressure();
  return sensorValue;
}

void Pump::KeepPressure(bool enabled) 
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
    // Serial.println("Low");
    }
    else if (pressure < airPressure)
    {
    	digitalWrite(pin, HIGH);
      //Serial.println("High");
    }
  }
}

void Pump::SetOn()
{
  digitalWrite(pin, HIGH);
}

void Pump::SetOff()
{
  digitalWrite(pin, LOW);
}

