#include "State.h"
/*
State::State(){
  State::currentState = NORMAL;
}*/

State::State() {
  setState(NORMAL);
  setPrevState(NORMAL);
}

State::State(const damState ds){
  setState(ds);
  setPrevState(ds);
}

void State::setState(const damState ds){
  setPrevState(getCurrentState());
  currentState() = ds;
}

const damState& State::getCurrentState(){
  return currentState();
}

damState& State::currentState(){
  static damState ds = NORMAL;
  return ds;
}

damState& State::prevState(){
  static damState prev = NORMAL;
  return prev;
}

void State::setPrevState(const damState ds){
  prevState() = ds;
}

const damState& State::getPrevState(){
  return prevState();
}

bool State::isStateChanged(){
  if(getPrevState() != getCurrentState()){
    setPrevState(getCurrentState());
    return true;
  } else {
    return false;
  }
}
