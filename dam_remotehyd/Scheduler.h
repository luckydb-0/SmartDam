#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "State.h"

#define MAX_TASKS 5
#define FREQ1 0.25
#define FREQ2 0.5

class Scheduler {

private:
  int period;
  int nTasks;
  Task* taskList[MAX_TASKS];
  void updateTimer();

public:
  void init(float period);
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif
