#ifndef __LEDTASK__
#define __LEDTASK__
#include "Led.h"
#include "Task.h"
#include "State.h"

class LedTask: public Task {
public:
	LedTask(int pin);
	void init(int period);
	void tick();

private:
  int pin;
  Led* led;
  State* st;
};

#endif
