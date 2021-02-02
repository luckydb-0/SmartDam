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
  State::setValue(this->lastRead);
  Serial.println(String("SONAR Stato: ") + (this->st->getCurrentState() == NORMAL ? "NORMAL" : (this->st->getCurrentState() == PRE_ALARM ? "PRE ALARM" : "ALARM")));
}

float SonarTask::getLastRead(){
  return this->lastRead;
};
