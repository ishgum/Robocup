
#ifndef State_h
#define State_h

#include "Arduino.h"



// State defines

#define ON 1
#define OFF 0

#define STOPPED 0
#define STRAIGHT 1
#define TURNING 2

#define WALL_FOLLOW 0
#define SEARCHING 1




class State
{
	public:
		State (void);
                void updatePowerState (int changeState);
                void updateNavigationState (int changeState);
                void updateDriveState (int changeState);
                
                int powerState;
                int navigationState;
                int driveState;
	private:
	
	
    
};

#endif
