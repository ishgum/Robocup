
#ifndef State_h
#define State_h

#include "Arduino.h"



// State defines

#define STATE_ON 1
#define STATE_OFF 0

#define STATE_STOPPED 0
#define STATE_STRAIGHT 1
#define STATE_TURNING 2

#define STATE_WALL_FOLLOW 0
#define STATE_SEARCHING 1
#define STATE_EVACUATE 2
#define STATE_ALIGNING 3
#define STATE_COLLECTING 4

#define STATE_RIGHT_WALL -1
#define STATE_LEFT_WALL 1



class State
{
	public:
		State (void);
                void updatePowerState (int changeState);
                void updateNavigationState (int changeState);
                void updateDriveState (int changeState);
                void updateFollowState (int changeState);
                
                int powerState;
                int navigationState;
                int driveState;
                int followState;
                
                bool init;
	private:
	
	
    
};

#endif
