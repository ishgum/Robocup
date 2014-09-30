
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 20
#define OFF_BUFFER 10

#define SWITCH_OFF 0
#define SWITCH_ON 1
#define SWITCH_WAITING 2

#define PULSE_ON 0
#define PULSE_OFF 1

class Switch
{
	public:
		Switch (int port,  int defaultOff, int inputPulse);
		void updateSwitch();
                
                int switchState;
	private:
		int _port;
		int _onCount;
		int _offCount;
	        int defaultOff;
                int pulse;
    
};

#endif
