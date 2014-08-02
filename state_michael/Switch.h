
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 20
#define OFF_BUFFER 10


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
