
#ifndef WaveArm_h
#define WaveArm_h

#include "Arduino.h"
#include "Servo.h"
#include "Whisker.h"

#define ARM_CLOCKWISE 1
#define ARM_ANTI -1

#define MAX_ANGLE 130
#define MIN_ANGLE 30
#define CENTRE_ANGLE 0


class WaveArm
{
	public:
		WaveArm (void);
                void armPos(void);
                void waveArm(bool waving, Servo servo, unsigned long tick);
                void moveToCentre();
                bool align(Servo servo);
                bool weightCheck(Whisker whisker);
                
                unsigned int currentAngle;
                unsigned int currentDirection;
	private:
               bool centred;
};

#endif
