#ifndef Whisker_h
#define Whisker_h

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_TIME 60000
#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)
#define DETECT_THRESHOLD 6100

#define TOLERANCE 5

class Whisker
{
	public:
		Whisker(void);
		//void WISR(void);		
                bool updateDetector(void);
		bool object;
                bool findWeight(void);
		volatile unsigned int count;
                
	private:
		unsigned int pulses;
		unsigned int lastTime;
		unsigned int time;
		unsigned int deltaTime;
		unsigned long freq;
                unsigned long _foundCount;
                bool _weightFound;
                
};

#endif
