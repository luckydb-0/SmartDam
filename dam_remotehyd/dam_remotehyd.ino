#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "Scheduler.h"
#include "SonarTask.h"
#include "StateTask.h"
#include "LedTask.h"
#include "WifiData.h"

#define PIN_TRIG D2
#define PIN_ECHO D1
#define PIN_LED D0

Scheduler sched;
Task* sonarTask;
Task* ledTask;
Task* stateTask;

void setup() {
  Task* taskArray[NUM_TASK];
  int counter = 0;
  Serial.begin(9600);
  WiFi.begin(SSID_NAME, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  
  sched.init(1/FREQ1);

  sonarTask = new SonarTask(PIN_TRIG, PIN_ECHO);
  sonarTask->init(1/FREQ1);
  sonarTask->setActive(true);
  sched.addTask(sonarTask);
  taskArray[counter] = sonarTask;
  counter++;

  ledTask = new LedTask(PIN_LED);
  ledTask->init(1/FREQ1);
  ledTask->setActive(true);
  sched.addTask(ledTask);
  taskArray[counter] = ledTask;
  counter++;

  stateTask = new StateTask(taskArray, counter);
  stateTask->init(1/FREQ1);
  stateTask->setActive(true);
  sched.addTask(stateTask);
}

int sendData(String address, float value, damState st){  
   HTTPClient http;    
   http.begin(address + "/api/data");      
   http.addHeader("Content-Type", "application/json");     
   String msg = 
    String("{ \"value\": ") + String(value) + 
    ", \"state\": \"" + 0 +"\" }";
   int retCode = http.POST(msg);   
   http.end();  
      
   // String payload = http.getString();  
   // Serial.println(payload);      
   return retCode;
}


void loop() {
  sched.schedule();
  if (WiFi.status()== WL_CONNECTED){   
    SonarTask* sonar = (SonarTask*)sonarTask;
   /* read sensor */
   float value = sonar->getLastRead();
   
   /* send data */
   Serial.print("sending "+String(value)+"...");    
   int code = sendData(ADDRESS, value, State::getCurrentState());

   /* log result */
   if (code == 200){
     Serial.println("ok");   
   } else {
     Serial.println(String("error: ") + code);
   }
 } else { 
   Serial.println("Error in WiFi connection");   
 }
}
