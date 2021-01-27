#ifndef __TASK__
#define __TASK__

#include "StateEnum.h"

class Task {
  int myPeriod;
  int timeElapsed;
  bool active;
  damState state;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
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

  void updateState(damState state){
    this->state = state;
  }

};

#endif
