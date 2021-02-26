#include "Comm.h"

Comm::Comm(String address, String ssid, String pwd){
  this->address = address;
  this->ssid = ssid;
  this->pwd = pwd;
}

bool Comm::startConnection(){
  WiFi.begin(this->ssid, this->pwd);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected.");
}

int Comm::sendNewData(float value, damState st){
  int code = -1;
  if (WiFi.status()== WL_CONNECTED){          
   Serial.print("sending "+String(value)+"...");    
   code = sendData(value, st);

   if (code == 200){
     Serial.println("ok");   
   } else {
     Serial.println(String("error: ") + code);
    }
  }

  return code;
}

int Comm::sendData(float value, damState st){
   HTTPClient http;    
   http.begin(this->address + "/api/data");      
   http.addHeader("Content-Type", "application/json");     
   String msg = 
    String("{ \"value\": ") + String(value) + 
    ", \"state\": \"" + String(st) +"\" }";
   int retCode = http.POST(msg);   
   http.end();
 
   return retCode;
};
