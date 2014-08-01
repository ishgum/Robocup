
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (void);
                float findError (float currentValue);
                float error;
                float desiredValue;
	private:
		
	
    
};

#endif
