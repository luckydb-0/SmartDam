#ifndef __DAMSTATE__
#define __DAMSTATE__
#include "Arduino.h"

#define DELTA_SPAN 20
#define DIST_1 100 // In cm
#define DIST_2 40
#define DELTA_D 4

enum damState{NORMAL, PRE_ALARM, ALARM};
enum mode{AUTO, MANUAL};

class State {
public:
  State();
  damState getCurrentState();
  void setState(damState st);
  void setDistance(float distance);
  int getSpan();
  void setSpan(int span);
  bool isNewValueAvailable();
  void setNewValueAvailable(bool b);
  mode getCurrentMode();
  void setMode(mode m);
  
private:
  damState currentState;
  mode currentMode;
  int span;
  int computeSpan(float distance);
  bool valueAvailable;
};

#endif
