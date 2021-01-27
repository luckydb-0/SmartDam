#include "SonarTask.h"

SonarTask::SonarTask(int pinTrig, int pinEcho) {
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
}

void SonarTask::init(int period) {
  Task::init(period);
  this->sonar = new SonarImpl(this->pinTrig, this->pinEcho); 
}

void SonarTask::tick(){
  // TODO
};
