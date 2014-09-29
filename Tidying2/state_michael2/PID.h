
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (int desired);
                float findError (float currentValue);
                void setDesiredValue(float newValue);
                void scaleError(signed int scale);
                float currentDesiredValue(void);
                float error;
                float scaledError;
                float desiredValue;
                bool ignore;
                int sweepDirection;
	private:
		
	
    
};

#endif
