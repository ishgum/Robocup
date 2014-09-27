
#ifndef Switch_h
#define Switch_h

#include "Arduino.h"

#define ON_BUFFER 20
#define OFF_BUFFER 10
#define PORT A3

#define SWITCH_OFF 0
#define SWITCH_ON 1

class Switch
{
	public:
		Switch (int inputPort);
		bool updateSwitch(void);
                void Init(void);
	private:
		int port;
		int onCount;
		int offCount;
                int switchState;
};

#endif
