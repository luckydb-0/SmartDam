#define __DAMCOMM__
#ifndef __DAMCOMM__

#include "Arduino.h"

// TODO
class Comms {
public:
  virtual void sendMessage(String msg) = 0;
};

#endif
