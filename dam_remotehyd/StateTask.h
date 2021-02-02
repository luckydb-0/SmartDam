#ifndef __STATETASK__
#define __STATETASK__

#include "State.h"
#include "Task.h"
#include "SonarTask.h"

#define NUM_TASK 2
#define DIST_1 1.0
#define DIST_2 0.4

class StateTask: public Task {

public:
  StateTask();
  void init(int period);
  void tick();
  
private:
  State* st;
  damState lastState;
  damState checkState(float distance);
  
};

#endif
