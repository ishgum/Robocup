
#ifndef ARM_h
#define ARM_h

#include "Arduino.h"
#include "Servo.h"
#include "schedule.h"
#include "Switch.h"

#define LEFT_SIDE 0
#define RIGHT_SIDE 1

#define SWEEP1 0
#define LOWER 1 
#define SWEEPING_IN 2
#define WAITING 3
#define SWEEPING_OUT 4
#define RAISE 5
#define STATIC 6

        //extern volatile unsigned long tick;

/*Control functions for both sweeper arms together
  Control for knockover arms (?)
  Detection of weights within robot */


class Arm
{  
	public:
		Arm (bool input_loc, int defaultAngle);
                void setDesiredAngle (int newAngle);
                void sweep(Servo armServo);
                
                bool checkMoving(void);
		bool moving;
                int currentAngle;

          private:
		unsigned long curr_time;
		unsigned long prev_time;
		unsigned long delta_ms;

                bool loc;
                int desiredAngle;
                Servo armServo;
	
};

#endif
