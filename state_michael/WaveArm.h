
#ifndef WaveArm_h
#define WaveArm_h

#include "Arduino.h"

#define ARM_CLOCKWISE 1
#define ARM_ANTI -1

#define MAX_ANGLE 130
#define MIN_ANGLE 50


class WaveArm
{
	public:
		WaveArm (void);
                void armPos(void);
                
                
                unsigned int currentAngle;
                unsigned int currentDirection;
	private:
               
};

#endif
