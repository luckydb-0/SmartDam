#include "Scheduler.h"
#include "LedTask.h"
#include "ServoMotorTask.h"
#include "CommTask.h"

#define FREQ_1 2000
#define FREQ_2 1000
#define SERVO_PIN 5
#define LED_PIN 2

State* state;
Task* ledTask;
Task* commTask;
Task* servoTask;
Scheduler sched;

void setup() {
  
  Serial.begin(9600);

  state = new State();

  sched.init(100);

  commTask = new CommTask();
  commTask->init(100, COMM, state);
  commTask->setActive(true);
  sched.addTask(commTask);

  ledTask = new LedTask(LED_PIN);
  ledTask->init(100, LED, state);
  ledTask->setActive(true);
  sched.addTask(ledTask);

  servoTask = new ServoMotorTask(SERVO_PIN);
  servoTask->init(100, SERVO, state);
  servoTask->setActive(true);
  sched.addTask(servoTask);
}

void loop() {
  sched.schedule();
}
