#include "Scheduler.h"
#include "LedTask.h"
#include "ServoMotorTask.h"
#include "CommTask.h"
#include "Globals.h"

State* state;
Task* ledTask;
Task* commTask;
Task* servoTask;
Scheduler sched;

void setup() {
  
  Serial.begin(9600);

  state = new State();

  sched.init(500);

  commTask = new CommTask(BT_RX_PIN, BT_TX_PIN);
  commTask->init(1/FREQ_2, state);
  commTask->setActive(true);
  sched.addTask(commTask);

  ledTask = new LedTask(LED_PIN);
  ledTask->init(500, state);
  ledTask->setActive(true);
  sched.addTask(ledTask);

  servoTask = new ServoMotorTask(SERVO_PIN);
  servoTask->init(1/FREQ_2, state);
  servoTask->setActive(true);
  sched.addTask(servoTask);
}

void loop() {
  sched.schedule();
}
