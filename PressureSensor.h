#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

class PressureSensor
{
private:
  int pin;
public:
	PressureSensor(int Pin);
	bool Calibrate();
	int GetPressure();
};

#endif
