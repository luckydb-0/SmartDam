#ifndef __COMMDAM__
#define __COMMDAM__

#include "State.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Comm {
public:
  Comm(String address, String ssid, String pwd);
  bool startConnection();
  int sendNewData(float value, damState st);

private:
  String address;
  String ssid;
  String pwd;
  int sendData(float value, damState st);
};

#endif
