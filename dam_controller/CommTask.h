#ifndef __MSGTASK__
#define __MSGTASK__

#include "MsgService.h"
#include "Task.h"

class CommTask: public Task {

public:
  	CommTask();
    void init(int period, State* state);
  	void tick();
private:
  int period;
  TaskId id;
};

#endif
