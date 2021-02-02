#include "StateTask.h"
#include "Arduino.h"

StateTask::StateTask(){
  this->st = new State();
  this->lastState = State::getCurrentState();
  Task::setId(TASK_STATE);
}

void StateTask::init(int period){
  Task::init(period);
}

damState StateTask::checkState(float distance){
  if(distance < DIST_2){
    State::setState(ALARM);
  } else if (distance >= DIST_2 && distance < DIST_1) {
    State::setState(PRE_ALARM);
  } else {
    State::setState(NORMAL);
  }

  return State::getCurrentState();
}

void StateTask::tick(){
  float sonarRead = State::getValue();
  damState curr = this->checkState(sonarRead);
    
  if(curr != this->lastState) {
    this->lastState = curr;
  }
  
  Serial.println(String("Distance: ") + sonarRead);
  Serial.println(String("Stato: ") + (curr == NORMAL ? "NORMAL" : (curr == PRE_ALARM ? "PRE ALARM" : "ALARM")));
};
