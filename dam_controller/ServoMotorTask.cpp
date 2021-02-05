#include "ServoMotorTask.h"

#define MIN_PULSE_SERVO 750 // equal to 0 degrees
#define MAX_PULSE_SERVO 2250 // equal to 180 degrees

ServoMotorTask::ServoMotorTask(int pin){
  this->pin = pin;
}

void ServoMotorTask::init(int period, State* state){
  Task::init(period, SERVO, state);
  this->servo = new ServoMotorImpl(this->pin);
  this->servo->on();
  this->servo->setPosition(MIN_PULSE_SERVO);
}

void ServoMotorTask::tick(){
  int span = this->getState()->getSpan(); 
  this->servo->setPosition(this->getPulseFromSpan(span));
  Serial.println(String("Pulse: ") + this->getPulseFromSpan(span));
}

int ServoMotorTask::getPulseFromSpan(int span) {
  return MIN_PULSE_SERVO + span * (MAX_PULSE_SERVO - MIN_PULSE_SERVO) / 100;
};
