
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (int desired);
                float findError (float currentValue);
                void setDesiredValue(float newValue);
                signed int scaleError(signed int scale);
                
                float error;
	private:
                float desiredValue;
                float scaledError;
};

#endif
