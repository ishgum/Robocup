
#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include <Servo.h>

#define ZERO_VALUE 90
#define FULL_SPEED 90

#define FORWARDS 1
#define BACKWARDS -1




class Motors
{
	public:
		Motors (void);
                void fullStop (void);
		void driveStraight (signed int error, signed int speedPercent, signed int dir);
	private:
		Servo leftWheel;
                Servo rightWheel;
	
    
};

#endif
