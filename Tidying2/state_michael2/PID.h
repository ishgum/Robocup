
#ifndef PID_h
#define PID_h

#include "Arduino.h"


class PID
{
	public:
		PID (float desired);
                float findError (float currentValue);
                void setDesiredValue(float newValue);
                float scaleError(float scale);
                
                float error;
	private:
                float desiredValue;
                float scaledError;
};

#endif
