#ifndef PUMP_H_
#define PUMP_H_
include "PressureSensor.h"

class Pump
{
	private:
		int airPressure;
		int pin;
		int PressureSensorPin;

	public:
		PressureSensor* sensor;
		Pump(int pressure, int PumpPin, int SensorPin);
		int Compare();
		void KeepPressure(bool enabled);
};

#endif
