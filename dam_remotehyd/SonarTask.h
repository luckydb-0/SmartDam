#ifndef __SONARTASK__
#define __SONARTASK__
#include "Task.h"
#include "SonarImpl.h"
#include "State.h"
#include "TemperatureSensorImpl.h"

class SonarTask: public Task {
public:
  SonarTask(int pinTrig, int pinEcho, int pinTemperature);
  void init(int period);
  void tick();
  float getLastRead();

private:
  State* st;
  int pinEcho;
  int pinTrig;
  int pinTemp;
  TemperatureSensor* tempSensor;
  Sonar* sonar;
  float lastRead;
};

#endif
