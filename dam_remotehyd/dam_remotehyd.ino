#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "Scheduler.h"
#include "SonarTask.h"
#include "StateTask.h"
#include "LedTask.h"
#include "WifiData.h"

#define PIN_TRIG D2
#define PIN_ECHO D1
#define PIN_LED D0

#define FREQ1 1
#define FREQ2 2

Scheduler sched;
Task* sonarTask;
Task* ledTask;
Task* stateTask;

void setup() {
  Task* taskArray[NUM_TASK];
  int counter = 0;
  Serial.begin(9600);
  /*WiFi.begin(SSID_NAME, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  Serial.println("Connected: \n local IP: "+WiFi.localIP());
  */
  sched.init(1/FREQ1);

  sonarTask = new SonarTask(PIN_TRIG, PIN_ECHO);
  sonarTask->init(1/FREQ1);
  sonarTask->setActive(true);
  sched.addTask(sonarTask);
  taskArray[counter] = sonarTask;
  counter++;

  stateTask = new StateTask(taskArray, counter);
  //stateTask = new StateTask(sonarTask);
  stateTask->init(1/FREQ1);
  stateTask->setActive(true);
  sched.addTask(stateTask);
}

void loop() {
  
  sched.schedule();
  
}
