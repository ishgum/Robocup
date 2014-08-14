#ifndef Whisker_h
#define Whisker_h

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_TIME 60000
#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)
#define DETECT_THRESHOLD 61600
#define QUICK true
#define SLOW false
#define FILTER_SHIFT 3
#define TOLERANCE 8

class Whisker
{
	public:
		Whisker(void);
		//void WISR(void);		
		bool detect(void);
		bool object;
		volatile unsigned int count;
	private:
		//bool doubleCheck(bool object);
		unsigned int pulses;
		unsigned int lastTime;
		unsigned int time;
		unsigned int deltaTime;
		unsigned long freq;
		//unsigned long _sureCount;
		//bool _prevObject;
		//bool _noChange;i
		long long filter_reg;
		unsigned long freqRead;
};

#endif
