
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 20
#define OFF_BUFFER 10

#define SWITCH_OFF 0
#define SWITCH_ON 1
#define WAITING 2

class Switch
{
	public:
		Switch (int port);
		void updateSwitch();
                
                int switchState;
	private:
		int _port;
		int _onCount;
		int _offCount;
	
    
};

#endif
