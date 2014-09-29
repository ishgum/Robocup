
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
#define ANGLE_OUT 180
#define ANGLE_IN 0
#define SWEEP_OUT_DELAY 30 //degrees

        //extern volatile unsigned long tick;

/*Control functions for both sweeper arms together
  Control for knockover arms (?)
  Detection of weights within robot */

extern Gate frontGate;
extern schedule collectorArms;
extern schedule gate;
extern Switch collectorSwitch;

class WaveArm{
  
	public:
		WaveArm (void);
                bool collect(Servo sweepArmLeft, Servo sweepArmRight);        
                bool sweep(Servo sweepArmLeft, Servo sweepArmRight);
                
                unsigned int angle;

	//private:
		int sweepIn(Servo sweepArmLeft, Servo sweepArmRight);
		int sweepOut(Servo sweepArmLeft, Servo sweepArmRight);
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
};

#endif
