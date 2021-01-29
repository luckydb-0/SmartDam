#include "SonarTask.h"

SonarTask::SonarTask(int pinTrig, int pinEcho) {
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
  this->st = new State();
  Task::setId(TASK_SONAR);
}

void SonarTask::init(int period) {
  Task::init(period);
  this->sonar = new SonarImpl(this->pinTrig, this->pinEcho); 
}

void SonarTask::tick(){
  this->lastRead = this->sonar->getDistance();
  Serial.println(String("SONAR Stato: ") + (this->st->getCurrentState() == NORMAL ? "NORMAL" : (this->st->getCurrentState() == PRE_ALARM ? "PRE ALARM" : "ALARM")));

  /*switch(this->getState()){
    case NORMAL:
      break;
    case PRE_ALARM:
      break;
    case ALARM:
      break;
    default:
      break;
  }*/
}

float SonarTask::getLastRead(){
  return this->lastRead;
};
