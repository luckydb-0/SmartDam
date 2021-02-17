#ifndef __MSG_H__
#define __MSG_H__

class Msg {
  String content;

public:
  Msg(String content){
    this->content = content;
  }
  
  String getContent(){
    return content;
  }
};

#endif
