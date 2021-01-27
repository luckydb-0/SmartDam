#ifndef __DAMSTATE__
#define __DAMSTATE__
#include "Arduino.h"
#include "Task.h"
#include "StateEnum.h"

#define NUM_TASK 2

class State {
public:
  State();
  damState getCurrentState();
  void setState(String msg);
  void addComponent(Task* task);
  void updateComponents();
private:
  damState currentState;
  Task* components[NUM_TASK];
  int componentsCount;
};

#endif
