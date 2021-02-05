#include "CommTask.h"
#include <string.h>
#include <stdlib.h>     /* strtof */


CommTask::CommTask() {}

void CommTask::init(int period, State* state) {
  Task::init(period, COMM, state);
	MsgService.init();
}

void CommTask::tick() {  
	if(MsgService.isMsgAvailable()) {
    String msg = MsgService.receiveMsg();
    char state = msg[0];
    float dist = msg.substring(2,7).toFloat();

    switch(state){
      case '0':
        Serial.println("Ma come cazzo hai fatto?!?!");
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
  }
}
