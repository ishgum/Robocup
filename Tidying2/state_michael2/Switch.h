
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 1
#define OFF_BUFFER 10

#define SWITCH_OFF 0
#define SWITCH_ON 1
#define SWITCH_WAITING 2

#define PULSE_ON 0
#define PULSE_OFF 1

#define ANALOG 0
#define DIGITAL 1

class Switch
{
	public:
		Switch (int port,  int inputPulse, int inputMode);
		void updateSwitch();
                
                int currentRead;
                int switchState;
	private:
		int _port;
		int _onCount;
		int _offCount;
                int _mode;
                int pulse;
    
};

#endif
