#ifndef __TASK__
#define __TASK__

#include "State.h"

enum TaskId{LED, COMM, SERVO, MSG};

class Task {
  int myPeriod;
  int timeElapsed;
  bool active;
  TaskId id;
  State* state;
  
public:
  virtual void init(int period, TaskId id, State* state){
    myPeriod = period;  
    timeElapsed = 0;
    this->id = id;
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

  TaskId getId() {
    return this->id;
  }

  State* getState(){
    return this->state;
  }

};

#endif
