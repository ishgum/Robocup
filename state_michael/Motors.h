
#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include <Servo.h>

#define ZERO_VALUE 90
#define FULL_SPEED 65

#define FORWARDS 1
#define BACKWARDS -1




class Motors
{
	public:
		Motors (void);
                void fullStop (void);
		void drive (signed int error, signed int speedPercent, signed int dir);
                void turn (unsigned int speedPercent, signed int dir);
                void setMotorSpeed(unsigned int newSpeed);
                
                int leftValue;
                int rightValue;
                int motorSpeed;
	private:
                void checkClipping();
                
	
    
};

#endif
