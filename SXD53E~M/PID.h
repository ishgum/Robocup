
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (void);
                float findError (float currentValue);
                void setDesiredValue(float newValue);
                float currentDesiredValue(void);
                float error;
                float desiredValue;
                float desiredSweep;
                int sweepDirection;
	private:
		
	
    
};

#endif
