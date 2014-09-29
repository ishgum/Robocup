
#ifndef WAVEARM_h
#define WAVEARM_h

#include "Arduino.h"
#include "Gate.h"
#include "Servo.h"
#include "schedule.h"
#include "Switch.h"

#define CONV 250000
#define MOVING_IN 1
#define MOVING_OUT 0
#define WAITING 2
#define SWEEP_OUT_DELAY 170 //degrees
#define LEFT_SIDE 0
#define RIGHT_SIDE 1

#define SWEEP_IN 0
#define SWEEP_OUT 1

        //extern volatile unsigned long tick;

/*Control functions for both sweeper arms together
  Control for knockover arms (?)
  Detection of weights within robot */

extern Servo gateServo;
extern Servo sweepArmLeft;
extern Servo sweepArmRight;
extern schedule collectorArms;
extern schedule gate;
extern Switch collectorSwitch;

class WaveArm{
  
	public:
		WaveArm (bool input_loc, int input_angle_in, int input_angle_out);
                bool collect(void);        
                bool sweep(Servo sweepArmLeft, Servo sweepArmRight);
                
                unsigned int angle;
                unsigned int angle_right;

	//private:
		bool sweepIn(Servo sweeper);
		bool sweepOut(Servo sweeper);
		bool collected();
private:
		unsigned long curr_time;
		unsigned long prev_time;
		unsigned long delta_ms;
		int armLocation = 0;
                bool temp_dir;
                int collector;
                bool result = false;
                bool collecting = true;
                bool gate_down;	
                int angle_out;
                int angle_in;
                bool loc;
                Servo sweeper;
                int dir;
                bool arms_in;	
};

#endif
