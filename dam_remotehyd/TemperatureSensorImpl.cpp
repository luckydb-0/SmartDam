#include "TemperatureSensorImpl.h"
#include "Arduino.h"

#define VCC ((float)5)

TemperatureSensorImpl::TemperatureSensorImpl(int pin) {
	this->pin = pin;
	pinMode(pin, INPUT);	
}

float TemperatureSensorImpl::getTemperature() {
	int value = analogRead(this->pin);
  float valueInVolt = value*VCC/1023;  
  float valueInCelsius = valueInVolt/0.01;
	return valueInCelsius;
};
