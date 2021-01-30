#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "State.h"

#define MAX_TASKS 5
#define FREQ1 1.0
#define FREQ2 3.0

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
