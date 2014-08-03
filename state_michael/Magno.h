
#ifndef Magno_h
#define Magno_h

#include "Arduino.h"

#include "FreeSixIMU.h"
#include "HMC5883L.h"

class Magno
{
	public:
		Magno (void);
                float findAngle(void);
                void getHeading(void);
                void init(void);
                
                float desiredValue;
                float heading;
	private:
                float angles[3];
                FreeSixIMU sixDOF;
                HMC5883L compass;
};

#endif
