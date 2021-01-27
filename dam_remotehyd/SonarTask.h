#ifndef __SONARTASK__
#define __SONARTASK__
#include "Task.h"
#include "SonarImpl.h"

class SonarTask: public Task {
public:
  SonarTask(int pinTrig, int pinEcho);
  void init(int period);
  void tick();

private:
  int pinEcho;
  int pinTrig;
  Sonar* sonar;
};

#endif
