#include "LedTask.h"

LedTask::LedTask(int pin) {
	this->pin = pin;
}

void LedTask::init(int period, State* state) {
	Task::init(period, LED, state);
	led = new Led(this->pin);
}

void LedTask::tick() {  
	switch (this->getState()->getCurrentState()){
	  
	}

};
