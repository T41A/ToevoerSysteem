#ifndef PUMP_H_
#define PUMP_H_

class Pump
{
	private:
		int airPressure;
		int pin;

	public:
		Sensor* sensor;
		Pump(int pressure, PressureSensor sensor, int pin);
		int Compare();
		void KeepPressure(bool enabled);
};

#endif
