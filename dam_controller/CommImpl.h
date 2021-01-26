#include "Comms.h"

class CommImpl: public Comms {
public:
  CommImpl();
  void sendMessage(String msg);
  
};
