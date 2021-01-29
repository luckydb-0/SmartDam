#include "State.h"
/*
State::State(){
  State::currentState = NORMAL;
}*/

  State::State() {
    setState(NORMAL);  
  }

  State::State(const damState ds){
    setState(ds);
  }
  
  void State::setState(const damState ds){
    currentState() = ds;
  }

  const damState& State::getCurrentState(){
    return currentState();
  }
  
  damState& State::currentState(){
    static damState ds = NORMAL;
    return ds;
  }
