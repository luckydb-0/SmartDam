#include "Scheduler.h"
#include <ESP8266WiFi.h>
#include <Ticker.h>  //Ticker Library

Ticker blinker;
volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(float period){
  this->period = period;
  timerFlag = false;
  blinker.attach(period, timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){   
  while (!timerFlag){ yield(); }
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(period)){
      taskList[i]->tick();
    }
  }
};
