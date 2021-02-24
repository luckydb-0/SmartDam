#ifndef __TEMPERATUREIMPL__
#define __TEMPERATUREIMPL__

#include "TemperatureSensor.h"

class TemperatureSensorImpl: public TemperatureSensor {

public:
	TemperatureSensorImpl(int pin);
	float getTemperature();
	
private:
	int pin;
	
};

#endif
