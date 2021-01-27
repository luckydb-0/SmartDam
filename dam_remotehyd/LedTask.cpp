#include "LedTask.h"

LedTask::LedTask(int pin) {
	this->pin = pin;
}

void LedTask::init(int period) {
	Task::init(period);
	led = new Led(pin);
}

void LedTask::tick() {  
	

};
