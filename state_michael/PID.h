
#ifndef PID_h
#define PID_h

#include "Arduino.h"
#include <Servo.h>

#define ZERO_VALUE 90
#define FULL_SPEED 90

#define FORWARDS 1
#define BACKWARDS -1

#define CLOCKWISE 1
#define ANTI_CLOCKWISE -1


class PID
{
	public:
		PID (void);
                void fullStop (void);
		void drive (signed int error, signed int speedPercent, signed int dir);
                void turn (unsigned int speedPercent, signed int dir);
	private:
		Servo leftWheel;
                Servo rightWheel;
	
    
};

#endif
