
#ifndef WAVEARM_h
#define WAVEARM_h

#include "Arduino.h"

#define CONV 250000
#define MOV_IN 1
#define MOV_OUT 0
#define WAITING 2
#define ANGLE_MAX 180
#define ANGLE_MIN 0
#define SPEED_MS 10

        //extern volatile unsigned long tick;

/*Control functions for both sweeper arms together
  Control for knockover arms (?)
  Detection of weights within robot */
	

class WaveArm{
  
	public:
		WaveArm (void);
                void collect(Servo sweepArmLeft, Servo sweepArmRight);        
                bool sweep(void);
                
                unsigned int angleRightArm;
                unsigned int angleLeftArm;

	private:
		bool sweepIn(Servo sweepArmLeft, Servo sweepArmRight);
		bool sweepOut(Servo sweepArmLeft, Servo sweepArmRight);
		bool collected(void);

		unsigned long curr_time;
		unsigned long prev_time;
		unsigned long delta_ms;
		int armLocation = 0;
                bool temp_dir;
                int collector;
                bool result = false;
                bool collecting;
                bool gate_down;		
};

#endif
