
#ifndef Compass_h
#define Compass_h

#include "Arduino.h"

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>

class Compass
{
	public:
		Compass (void);
                float findAngle(void);
                
                float desiredValue;
	private:
                float angles[3];
                FreeSixIMU sixDOF;
                HMC5883L compass;
};

#endif
