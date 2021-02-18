#include "CommTask.h"

#define MAX_TIME 1.0/FREQ_1
#define MAX_DISTANCE 4

CommTask::CommTask(int rxPin, int txPin) {
  msgService.init();
  msgServiceBT = new MsgServiceBT(rxPin, txPin);
  msgServiceBT->init();
}

void CommTask::init(int period, State* state) {
  Task::init(period, state);
  this->timestamp = millis();
}

void CommTask::tick() {
  long now = millis();
	if(msgService.isMsgAvailable()) {
    Msg* message = msgService.receiveMsg();
    String msg = message->getContent();
    char state = msg[0];
    float dist = msg.substring(2,7).toFloat();

    switch(state){
      case '0':
        break;
      case '1':
        this->getState()->setState(PRE_ALARM);
        this->getState()->setDistance(dist);
        msgServiceBT->sendMsg(Msg(state + String(":") + dist + String(":") + this->getState()->getSpan() + String(":")));
        msgService.sendMsg(Msg(state + String(":") + dist + String(":") + this->getState()->getSpan() + String(":")));
        break;
      case '2':
        this->getState()->setState(ALARM);
        if(this->getState()->getCurrentMode() == AUTO) {
          this->getState()->setDistance(dist);
        }
        msgServiceBT->sendMsg(Msg(state + String(":") + dist + String(":") + this->getState()->getSpan() + String(":")));
        msgService.sendMsg(Msg(state + String(":") + dist + String(":") + this->getState()->getSpan() + String(":")));
        break;
      default:
        break;
    }

    this->getState()->setNewValueAvailable(true);
    this->timestamp = millis();

    delete message;
  } else if (now - timestamp >= MAX_TIME*1000) {
    if(this->getState()->getCurrentState() != NORMAL){
      this->getState()->setNewValueAvailable(true);
      this->getState()->setState(NORMAL);
      this->getState()->setDistance(MAX_DISTANCE);
      this->getState()->setMode(AUTO);
      msgServiceBT->sendMsg(Msg("0:0:0:"));
      msgService.sendMsg(Msg("0:0:0:"));
    } else {
      this->getState()->setNewValueAvailable(false);
    }
  } else {
    this->getState()->setNewValueAvailable(false);
  }

  if(msgServiceBT->isMsgAvailable()) {
    Msg* msg = msgServiceBT->receiveMsg();
      if(msg->getContent().equals("M")) {
        this->getState()->setMode(MANUAL);
      } else if(msg->getContent().equals("A")){
        this->getState()->setMode(AUTO);
      } else {
        this->getState()->setSpan(msg->getContent().toInt());
      } 
    delete msg;
  }
}
