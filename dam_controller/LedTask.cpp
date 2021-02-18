#include "LedTask.h"

LedTask::LedTask(int pin) {
	this->pin = pin;
}

void LedTask::init(int period, State* state) {
	Task::init(period, state);
	this->led = new Led(this->pin);
  this->ledState = OFF;
}

void LedTask::tick() {
	if(this->getState()->getCurrentState() == ALARM){
    if(this->getState()->getCurrentMode() == AUTO) {
      switch (this->ledState){
        case OFF:
          this->led->switchOn();
          this->ledState = ON; 
          break;
        case ON:
          this->led->switchOff();
          this->ledState = OFF;
          break;
        default:
          break;
      }
    } else {
      if(this->ledState == OFF) {
        this->led->switchOn();
        this->ledState = ON;
      }
    }
	} else {
    if(this->ledState == ON){
      this->led->switchOff();
      this->ledState = OFF;
    }
	}
};
