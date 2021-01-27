#include "SonarImpl.h"
#include "Arduino.h"

SonarImpl::SonarImpl(int pinTrig, int pinEcho) {
	this->pinTrig = pinTrig;
	this->pinEcho = pinEcho;
	pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
}

float SonarImpl::getDistance() {
	float vs = 331.45 + 0.62*20;
  digitalWrite(this->pinTrig, LOW);
  delayMicroseconds(3);
  digitalWrite(this->pinTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(this->pinTrig, LOW);
  
  float tUS = pulseIn(this->pinEcho, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t*vs;
  return d;
};
