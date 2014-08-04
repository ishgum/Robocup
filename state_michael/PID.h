
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (void);
                float findError (float currentValue);
                void changeDesired();
                float error;
                float desiredValue;
                float desiredSweep;
                int sweepDirection;
	private:
		
	
    
};

#endif
