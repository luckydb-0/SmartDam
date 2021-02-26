#include "LedTask.h"

LedTask::LedTask(int pin) {
	this->pin = pin;
  Task::setId(TASK_LED);
}

void LedTask::init(int period) {
	Task::init(period);
	led = new Led(pin);
}

void LedTask::tick() {  
	switch(State::getCurrentState()){
    case NORMAL:
      if(led->isOn()){
        led->switchOff();
      }
      break;
    case PRE_ALARM:
      if(led->isOn()){
        led->switchOff();
      } else {
        led->switchOn();
      }
      break;
    case ALARM:
      if(!led->isOn()){
        led->switchOn();
      }
      break;
    default:
      break;
	}

 Serial.println("Led Task");

};
