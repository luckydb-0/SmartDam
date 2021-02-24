#ifndef __SONAR__
#define __SONAR__

class Sonar {

public:
	virtual float getDistance() = 0;
  virtual void setTemperature(float temp) = 0;
  
};

#endif
