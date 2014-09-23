
#ifndef WaveArm_h
#define WaveArm_h

#include "Arduino.h"

#define CONV 250000
#define ARMS_IN 1
#define ARMS_OUT 0
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
	        void knockOver(void);
                unsigned int angle;

	private:
		bool sweepIn(Servo sweepArmLeft, Servo sweepArmRight);
		bool sweepOut(Servo sweepArmLeft, Servo sweepArmRight);
		bool collected(void);
		unsigned long curr_time;
		unsigned long prev_time;
		unsigned long delta_ms;
		int armLocation = 0;
                bool temp_dir;		
};

#endif
