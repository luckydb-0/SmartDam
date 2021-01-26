#ifndef __DAMSTATE__
#define __DAMSTATE__
#include "Arduino.h"

enum damState{NORMAL, PRE_ALARM, ALARM};

class State {
public:
  State();
  damState getCurrentState();
  void setState(String msg);
private:
  damState currentState;
};

#endif
