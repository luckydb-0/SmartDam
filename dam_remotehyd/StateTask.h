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
  //StateTask(Task** tasks, int len);
  StateTask(Task* sonar);
  void init(int period);
  void tick();
  
private:
  State* state;
  damState lastState;
  SonarTask* sonar;
  Task** components;
  int componentsCount;
  SonarTask* getSonarTask();
  damState checkState(float distance);
  void updateComponents();
  
};

#endif
