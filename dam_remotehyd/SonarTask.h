#ifndef __SONARTASK__
#define __SONARTASK__
#include "Task.h"
#include "SonarImpl.h"
#include "State.h"

class SonarTask: public Task {
public:
  SonarTask(int pinTrig, int pinEcho);
  void init(int period);
  void tick();
  float getLastRead();

private:
  State* st;
  int pinEcho;
  int pinTrig;
  Sonar* sonar;
  float lastRead;
};

#endif
