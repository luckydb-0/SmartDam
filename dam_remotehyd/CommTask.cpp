#include "CommTask.h"

#include "WiFiData.h"

CommTask::CommTask() {
  this->comm = new Comm(ADDRESS, SSID_NAME, WIFI_PWD);
}

void CommTask::init(int period){
  Task::init(period);
  this->comm->startConnection();
}

void CommTask::setSonarTask(SonarTask* sonar){
  this->sonar = sonar;
}

void CommTask::tick(){
  switch(State::getCurrentState()){
    case NORMAL:
      break;
    case PRE_ALARM:
    case ALARM:
      this->comm->sendNewData(State::getValue(), State::getCurrentState());
      break;
  }
  Serial.println("Comm task");
};
