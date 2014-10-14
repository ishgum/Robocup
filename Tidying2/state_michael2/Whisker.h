#ifndef WHISKER_h
#define WHISKER_h

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)
#define DETECT_THRESHOLD_FRONT 5510 //~2740 wo serial
#define DETECT_THRESHOLD_SIDE 3345
#define DETECT_THRESHOLD_ROBOT 100 //GUESSING HERE
#define FILTER_SHIFT 6
class Whisker
{
	public:
		Whisker(void);		
                bool detect(int detect_threshold);
		bool object;
		volatile unsigned int count;
	private:
        bool doubleCheck(bool object);
		unsigned int pulses;
		unsigned int lastTime;
		unsigned int time;
		unsigned int deltaTime;
		unsigned long freq;
                unsigned long freqRead;
                unsigned long filter_reg;
};

#endif
