#include "StateTask.h"

StateTask::StateTask(Task* sonar){
  this->state = new State();
  this->lastState = this->state->getCurrentState();
  //this->componentsCount = len;
  //this->components = tasks;
  this->sonar = (SonarTask*)sonar;
  Task::setId(TASK_STATE);
}

void StateTask::init(int period){
  Task::init(period);
}

damState StateTask::checkState(float distance){
  if(distance < DIST_2){
    this->state->setState(ALARM);
  } else if (distance >= DIST_2 && distance < DIST_1) {
    this->state->setState(PRE_ALARM);
  } else {
    this->state->setState(NORMAL);
  }

  return this->state->getCurrentState();
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
      Serial.println(String("Id trovato ") + i);
      return (SonarTask*)(this->components[i]);
    }
  }

  return NULL;
}

void StateTask::updateComponents() {
  for(int i = 0; i < this->componentsCount; i++) {
    this->components[i]->updateState(this->state->getCurrentState());
  }
};
