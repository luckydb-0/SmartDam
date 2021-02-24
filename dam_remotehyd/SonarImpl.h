#ifndef __SONARIMPL__
#define __SONARIMPL__

#include "Sonar.h"

class SonarImpl: public Sonar {
	
public:
	SonarImpl(int pinTrig, int pinEcho);
	float getDistance();
	void setTemperature(float temp);
	
private:
	int pinTrig;
	int pinEcho;
  float temp;
  
};

#endif
