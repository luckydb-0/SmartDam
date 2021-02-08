#ifndef __GREENLEDTASK__
#define __GREENLEDTASK__
#include "Led.h"
#include "Task.h"

class LedTask: public Task {
private:
	int pin;
	Led* led;
  enum {ON, OFF} ledState;

public:
	LedTask(int pin);
	void init(int period, State* state);
	void tick();

};

#endif
