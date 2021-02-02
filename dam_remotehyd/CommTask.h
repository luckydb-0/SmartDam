#ifndef __COMMTASK__
#define __COMMTASK__

#include "Comm.h"
#include "Task.h"
#include "SonarTask.h"
#include "State.h"

class CommTask: public Task {
public:
  CommTask();
  void init(int period);
  void tick();
  void setSonarTask(SonarTask* sonar);

private:
  Comm* comm;
  State* st;
  SonarTask* sonar;
};

#endif
