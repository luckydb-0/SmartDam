#ifndef __TASK__
#define __TASK__

#include "State.h"
#include "Globals.h"

class Task {
  int myPeriod;
  int timeElapsed;
  bool active;
  State* state;
  
public:
  virtual void init(int period, State* state){
    myPeriod = period;  
    timeElapsed = 0;
    this->state = state;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool isActive(){
    return active;
  }

  void setActive(bool active){
    this->active = active;
  }

  State* getState(){
    return this->state;
  }

};

#endif
