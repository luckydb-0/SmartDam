#ifndef __STATETASK__
#define __STATETASK__
#include "State.h"
#include "Task.h"

class StateTask: public Task {

public:
  StateTask();
  void init(int period);
  void tick();

private:
  State* state;
  damState lastState;
};

#endif
