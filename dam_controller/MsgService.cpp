#include "Arduino.h"
#include "MsgService.h"

String content;
MsgService msgService;

bool MsgService::isMsgAvailable(){
  return msgAvailable;
}

Msg* MsgService::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;  
  } else {
    return new Msg(" "); 
  }
}

void MsgService::init(){
  Serial.begin(9600);
  content.reserve(256);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;
}

void MsgService::sendMsg(Msg msg){
  Serial.println(msg.getContent());  
}

void serialEvent() {
  /* reading the content */
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\n'){
      msgService.currentMsg = new Msg(content);
      msgService.msgAvailable = true;      
    } else {
      content += ch;      
    }
  }
}
