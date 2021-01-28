#ifndef __DAMSTATE__
#define __DAMSTATE__
#include "Arduino.h"
#include "Task.h"
#include "StateEnum.h"

class State {
public:
  State();
  damState getCurrentState();
  void setState(damState state);

private:
  damState currentState;

};

#endif
