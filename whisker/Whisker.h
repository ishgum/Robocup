#ifndef Whisker_h
#define Whisker_h

#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_TIME 60000
#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)
#define DETECT_THRESHOLD 14500

class Whisker
{
	public:
		Whisker(void);
		bool detect(void);
		bool object;
	private:
		void WISR(void);
		volatile unsigned int count;
		unsigned int pulses = 27;
		unsigned int lastTime = 0;
		unsigned int time = 0;
		unsigned int deltaTime = 0;
		unsigned long freq = 0;
}

#endif
