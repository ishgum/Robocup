#ifndef Whisker_h
#define Whisker_h

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_TIME 60000
#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)
#define DETECT_THRESHOLD 6500

class Whisker
{
	public:
		Whisker(void);
		//void WISR(void);		
                bool detect(void);
		bool object;
		volatile unsigned int count;
	private:
		unsigned int pulses;
		unsigned int lastTime = 0;
		unsigned int time = 0;
		unsigned int deltaTime = 0;
		unsigned long freq = 0;
};

#endif
