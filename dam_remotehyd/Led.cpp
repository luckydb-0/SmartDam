#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
  on = false;
}

void Led::switchOn(){
  digitalWrite(pin,HIGH);
  on = true;
}

void Led::switchOff(){
  digitalWrite(pin,LOW);
  on = false;
}

bool Led::isOn() {
	return this->on;
};
