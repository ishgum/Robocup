
#ifndef State_h
#define State_h

#include "Arduino.h"



// State defines

#define STATE_ON 1
#define STATE_OFF 0

#define STATE_STOPPED 10
#define STATE_STRAIGHT 11
#define STATE_TURNING 12

#define STATE_WALL_FOLLOW 20
#define STATE_SEARCHING 21
#define STATE_EVACUATE 22
#define STATE_ALIGNING 23
#define STATE_COLLECTING 24
#define STATE_HONING 25

#define STATE_RIGHT_WALL -1
#define STATE_LEFT_WALL 1



class State
{
	public:
		State (int defaultState);
                void setToDefault(void);
                void updateState (int changeState);
                int returnState (void);
                
                bool init;
	private:
	        int _currentState;
                int _default;
	
    
};

int previousState;
int sensorTurnAngle;


#endif
