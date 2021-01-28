#include "State.h"

State::State(){
  this->currentState = NORMAL;
}

damState State::getCurrentState(){
  return this->currentState;
}

void State::setState(damState state){
  this->currentState = state;
};
