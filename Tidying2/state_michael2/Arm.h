
#ifndef ARM_h
#define ARM_h

#include "Arduino.h"
#include "Servo.h"
#include "schedule.h"
#include "Switch.h"

#define LEFT_SIDE 0
#define RIGHT_SIDE 1


        //extern volatile unsigned long tick;

/*Control functions for both sweeper arms together
  Control for knockover arms (?)
  Detection of weights within robot */


class Arm
{  
	public:
		Arm (bool input_loc, int defaultAngle);
                void setDesiredAngle (int newAngle, int speed_ms);
                void sweep(Servo armServo);
                
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
