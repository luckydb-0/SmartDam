#include <ESP8266WiFi.h>

#include "Scheduler.h"
#include "SonarTask.h"
#include "LedTask.h"

#define PIN_TRIG D2
#define PIN_ECHO D1
#define PIN_LED D0

Scheduler sched;
Task* sonarTask;
Task* ledTask;

void setup() {
  sched.init(0.5);

  sonarTask = new SonarTask(PIN_TRIG, PIN_ECHO);
  sonarTask->init(0.5);
  sched.addTask(sonarTask);
  
}

void loop() {
  
  sched.schedule();
  yield();
}
