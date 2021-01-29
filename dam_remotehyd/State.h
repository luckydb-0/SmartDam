#ifndef __DAMSTATE__
#define __DAMSTATE__

#include "StateEnum.h"

class State {
public:
  State();

  State(const damState ds);
  
  static void setState(const damState ds);
  static const damState& getCurrentState();
  
private:
  static damState& currentState();
};

#endif
