#ifndef __DAMSTATE__
#define __DAMSTATE__

#include "StateEnum.h"

class State {
public:
  State();

  State(const damState ds);
  static bool isStateChanged();
  static void setState(const damState ds);
  static const damState& getCurrentState();
  
private:
  static damState& currentState();
  static damState& prevState();
  static void setPrevState(const damState ds);
  static const damState& getPrevState();
};

#endif
