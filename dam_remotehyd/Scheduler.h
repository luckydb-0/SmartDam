#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 10

class Scheduler {
  
  int period;
  int nTasks;
  Task* taskList[MAX_TASKS];  

public:
  void init(float period);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif
