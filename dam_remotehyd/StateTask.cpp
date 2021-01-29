#include "StateTask.h"
#include "Arduino.h"

StateTask::StateTask(Task** tasks, int len){
  this->st = new State();
  this->lastState = State::getCurrentState();
  this->componentsCount = len;
  this->components = tasks;
  this->sonar = this->getSonarTask();
  Task::setId(TASK_STATE);
}

void StateTask::init(int period){
  Task::init(period);
}

damState StateTask::checkState(float distance){
  if(distance < DIST_2){
    State::setState(ALARM);
  } else if (distance >= DIST_2 && distance < DIST_1) {
    State::setState(PRE_ALARM);
  } else {
    State::setState(NORMAL);
  }

  return State::getCurrentState();
}

void StateTask::tick(){
  float sonarRead;
  damState curr;
  sonarRead = this->sonar->getLastRead();
  curr = this->checkState(sonarRead);
    
  if(curr != this->lastState) {
    this->updateComponents();
    this->lastState = curr;
  }
  
  Serial.println(String("Distance: ") + sonarRead);
  Serial.println(String("Stato: ") + (curr == NORMAL ? "NORMAL" : (curr == PRE_ALARM ? "PRE ALARM" : "ALARM")));
}

SonarTask* StateTask::getSonarTask(){
  for(int i = 0; i < this->componentsCount; i++){
    if(this->components[i]->getTaskId() == TASK_SONAR) {
      return (SonarTask*)(this->components[i]);
    }
  }

  //return NULL;
}

void StateTask::updateComponents() {
 /* for(int i = 0; i < this->componentsCount; i++) {

    this->components[i]; 

    damState st = State::getCurrentState();    

    //task->updateState(st);

  }*/
};
