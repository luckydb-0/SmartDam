#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Globals.h"
#include "Msg.h"

class MsgService {
    
public: 
  
  Msg* currentMsg;
  bool msgAvailable;
  void init();  
  bool isMsgAvailable();
  Msg* receiveMsg();
  void sendMsg(Msg msg);
};

extern MsgService msgService;

#endif
