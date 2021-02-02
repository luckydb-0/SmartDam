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
  static void setValue(const float value);
  static const float& getValue();
  
private:
  static damState& currentState();
  static damState& prevState();
  static void setPrevState(const damState ds);
  static const damState& getPrevState();
  static float& sonarValue();
};

#endif
