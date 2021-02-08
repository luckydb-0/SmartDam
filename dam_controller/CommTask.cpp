#include "CommTask.h"

#define MAX_TIME 1.0/FREQ_1
#define MAX_DISTANCE 4

CommTask::CommTask() {}

void CommTask::init(int period, State* state) {
  Task::init(period, state);
	MsgService.init();
  this->timestamp = millis();
}

void CommTask::tick() {
  long now = millis();
	if(MsgService.isMsgAvailable()) {
    String msg = MsgService.receiveMsg();
    char state = msg[0];
    float dist = msg.substring(2,7).toFloat();

    switch(state){
      case '0':
        break;
      case '1':
        this->getState()->setState(PRE_ALARM);
        this->getState()->setDistance(dist);
        break;
      case '2':
        this->getState()->setState(ALARM);
        this->getState()->setDistance(dist);
        break;
      default:
        break;
    }

    this->getState()->setNewValueAvailable(true);
    this->timestamp = millis();
  } else if (now - timestamp >= MAX_TIME*1000) {
    if(this->getState()->getCurrentState() != NORMAL){
      this->getState()->setNewValueAvailable(true);
      this->getState()->setState(NORMAL);
      this->getState()->setDistance(MAX_DISTANCE); 
    } else {
      this->getState()->setNewValueAvailable(false);
    }
  } else {
    this->getState()->setNewValueAvailable(false);
  }
}
