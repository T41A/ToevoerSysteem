#ifndef PUMP_H_
#define PUMP_H_

class pump
{
	private:
		int airPressure;

	public:
		Sensor* sensor;
		Pump(int pressure, PressureSensor sensor);
		int Compare();
		void KeepPressure();
};

#endif
