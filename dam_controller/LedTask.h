#ifndef __GREENLEDTASK__
#define __GREENLEDTASK__
#include "Led.h"
#include "Task.h"

class LedTask: public Task {
	
	int pin;
	Led* led;
	
public:
	LedTask(int pin);
	void init(int period, State* state);
	void tick();

};

#endif
