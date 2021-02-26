#include "SonarTask.h"

SonarTask::SonarTask(int pinTrig, int pinEcho, int pinTemperature) {
  this->pinTrig = pinTrig;
  this->pinEcho = pinEcho;
  this->pinTemp = pinTemperature;
  this->st = new State();
  Task::setId(TASK_SONAR);
}

void SonarTask::init(int period) {
  Task::init(period);
  this->sonar = new SonarImpl(this->pinTrig, this->pinEcho);
  this->tempSensor = new TemperatureSensorImpl(this->pinTemp);
}

void SonarTask::tick(){
  this->sonar->setTemperature(this->tempSensor->getTemperature());
  this->lastRead = this->sonar->getDistance();
  State::setValue(this->lastRead);
}

float SonarTask::getLastRead(){
  return this->lastRead;
};
