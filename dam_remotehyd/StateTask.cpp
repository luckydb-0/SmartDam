#include "StateTask.h"

StateTask::StateTask(){
  this->state = new State();
  this->lastState = this->state->getCurrentState();
}

void StateTask::init(int period){
  Task::init(period);
}

void StateTask::tick(){
  damState curr = this->state->getCurrentState(); 
  if(curr != this->lastState) {
    this->state->updateComponents();
    this->lastState = curr;
  }
}
