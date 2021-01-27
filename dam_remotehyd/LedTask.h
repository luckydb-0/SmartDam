#ifndef __LEDTASK__
#define __LEDTASK__
#include "Led.h"
#include "Task.h"
#include "State.h"

class LedTask: public Task {
	
	int pin;
	Led* led;
	
public:
	LedTask(int pin);
	void init(int period);
	void tick();

};

#endif
