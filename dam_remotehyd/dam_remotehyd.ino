#include "Scheduler.h"
#include "SonarTask.h"
#include "StateTask.h"
#include "LedTask.h"
#include "CommTask.h"

#define PIN_TRIG D2
#define PIN_ECHO D1
#define PIN_LED D0

Scheduler sched;
Task* sonarTask;
Task* ledTask;
Task* stateTask;
Task* commTask;

void setup() {
  Serial.begin(9600);

  sched.init(1/FREQ1);

  sonarTask = new SonarTask(PIN_TRIG, PIN_ECHO);
  sonarTask->init(1/FREQ1);
  sonarTask->setActive(true);
  sched.addTask(sonarTask);
  
  ledTask = new LedTask(PIN_LED);
  ledTask->init(1/FREQ1);
  ledTask->setActive(true);
  sched.addTask(ledTask);
  
  stateTask = new StateTask();
  stateTask->init(1/FREQ1);
  stateTask->setActive(true);
  sched.addTask(stateTask);

  commTask = new CommTask();
  commTask->init(1/FREQ1);
  commTask->setActive(true);
  sched.addTask(commTask);
}

void loop() {
  sched.schedule();
}
