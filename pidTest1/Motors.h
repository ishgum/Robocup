
#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include <Servo.h>

#define ZERO_VALUE 90
#define FULL_SPEED 65

#define FORWARDS 1
#define BACKWARDS -1

#define CLOCKWISE 1
#define ANTI_CLOCKWISE -1


class Motors
{
	public:
		Motors (void);
                void fullStop (void);
		void drive (signed int error, signed int speedPercent, signed int dir);
                void turn (unsigned int speedPercent, signed int dir);
                
                int leftValue;
                int rightValue;
	private:
		int _zero;
                int _fullSpeed;
                
                
	
    
};

#endif
