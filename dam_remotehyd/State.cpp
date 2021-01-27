#include "State.h"

State::State(){
  this->currentState = NORMAL;
  this->componentsCount = 0;
}

damState State::getCurrentState(){
  return this->currentState;
}

void State::setState(String msg){
  // TODO
}

void State::addComponent(Task* task) {
  this->components[this->componentsCount] = task;
  this->componentsCount++;
}

void State::updateComponents() {
  for(int i = 0; i < this->componentsCount; i++) {
    this->components[i]->updateState(this->currentState);
  }
};
