#ifndef __MSGTASK__
#define __MSGTASK__

#include "MsgService.h"
#include "MsgServiceBT.h"
#include "Task.h"

class CommTask: public Task {

public:
	CommTask(int rxPin, int txPin);
  void init(int period, State* state);
	void tick();
private:
  int period;
  long timestamp;
  MsgServiceBT* msgServiceBT;
};

#endif
