#include "Scheduler.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Ticker.h>  //Ticker Library

Ticker timer;
volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(float period){
  this->period = period;
  timerFlag = false;
  timer.attach_ms(period, timerHandler);
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

void Scheduler::updateTimer(){
  if(State::isStateChanged()){
    timer.detach();
    if(State::getCurrentState() == ALARM){
      timer.attach_ms(1/FREQ2, timerHandler);
    } else {
      timer.attach_ms(1/FREQ1, timerHandler);
    }
  }
}
 
void Scheduler::schedule(){
  this->updateTimer();
  while (!timerFlag){ yield(); }
  timerFlag = false;
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(period)){
      taskList[i]->tick();
    }
  }
};
