#ifndef __DAMFSM__
#define __DAMFSM__

#include "async_fsm.h"
#include "State.h"
#include "ServoMotorImpl.h"
#include "Led.h"
#include "Comms.h"

class DamFSM: public AsyncFSM {
public:
  DamFSM(Led* led, ServoMotor* servo, Comm* comm);
  void handleEvent(Event* ev);

private:
  Led* led;
  ServoMotor* servo;
  Comm* comm;
  State* state;
  
};

#endif
