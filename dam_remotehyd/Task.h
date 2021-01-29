#ifndef __TASK__
#define __TASK__

#include "StateEnum.h"
#include "Arduino.h"

enum TaskId{TASK_LED, TASK_SONAR, TASK_STATE};

class Task {

private:
  int myPeriod;
  int timeElapsed;
  bool active;
  TaskId id;

protected:
  void setId(TaskId id){
    this->id = id;
  }
  
public:
  virtual void init(int period){
    this->myPeriod = period;  
    this->timeElapsed = 0;
  }

  virtual void tick() = 0;

  TaskId getTaskId(){
    return this->id;
  }

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
};

#endif
