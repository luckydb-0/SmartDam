#ifndef __SERVOMOTORTASK__
#define __SERVOMOTORTASK__

#include "Task.h"
#include "ServoMotorImpl.h"
#include "State.h"

class ServoMotorTask: public Task {

private:
  int pin;
  ServoMotor* servo;
  int getPulseFromSpan(int span);
  
public:
  ServoMotorTask(int pin);
  void init(int period, State* state);
  void tick();
};

#endif
