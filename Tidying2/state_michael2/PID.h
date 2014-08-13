
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (void);
                float findError (float currentValue);
                void setDesiredValue(float newValue);
                void scaleError(signed int scale);
                float currentDesiredValue(void);
                float error;
                float scaledError;
                float desiredValue;
                float desiredSweep;
                bool ignore;
                int sweepDirection;
	private:
		
	
    
};

#endif
