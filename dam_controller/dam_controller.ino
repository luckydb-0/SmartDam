#include "DamFSM.h"

#define FREQ_1 2000
#define FREQ_2 1000
#define SERVO_PIN 3
#define LED_PIN 2

DamFSM* damFSM;

void setup() {
  Led* led = new Led(LED_PIN);
  Comms* comm = new Comms(); // TODO
  ServoMotor* servo = new ServoMotorImpl(SERVO_PIN);
  damFSM = new DamFSM(led, servo, comm);
}

void loop() {
  damFSM->checkEvents();
}
