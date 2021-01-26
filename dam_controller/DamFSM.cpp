#include "DamFSM.h"

DamFSM::DamFSM(Led* led, ServoMotor* servo, Comm* comm){
  this->led = led;
  this->servo = servo;
  this->comm = comm;
  state = new State();
}

void DamFSM::handleEvent(Event* ev) {
  switch(this->state->getCurrentState()) {
    case NORMAL:
      // TODO
      break;
    case PRE_ALARM:
      // TODO
      break;
    case ALARM:
      // TODO
      break;
    default:
      break;
  }
};
