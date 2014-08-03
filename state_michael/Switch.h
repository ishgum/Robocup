
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 30
#define OFF_BUFFER 10

#define SWITCH_ON 1
#define SWITCH_OFF 0


class Switch
{
	public:
		Switch (int port);
		void updateSwitch();
                int returnPort();
                
                int switchState;
	private:
                int _port;
		int _onCount;
		int _offCount;
	
    
};

#endif
