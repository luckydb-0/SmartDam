#include "State.h"

State::State(){
  this->currentState = NORMAL;
}

damState State::getCurrentState(){
  return this->currentState;
}

void State::setState(damState st){
  this->currentState = st;
}

void State::setDistance(float distance){
  this->computeSpan(floor(distance*100+0.1)); // floor and +0.1 due to toFloat bug
}

bool State::isNewValueAvailable(){
  return this->valueAvailable;
}

void State::setNewValueAvailable(bool b){
  this->valueAvailable = b; 
}

int State::computeSpan(float distance){
  if(distance <= (DIST_2 - 4*DELTA_D)){
    this->span = DELTA_SPAN*5;
  } else if(distance <= (DIST_2 - 3*DELTA_D)){
    this->span = DELTA_SPAN*4;
  } else if(distance <= (DIST_2 - 2*DELTA_D)){
    this->span = DELTA_SPAN*3;
  } else if(distance <= (DIST_2 - DELTA_D)){
    this->span = DELTA_SPAN*2;
  } else if(distance <= DIST_2){
    this->span = DELTA_SPAN;
  } else {
    this->span = 0;
  }
}

int State::getSpan(){
  return this->span;  
};
