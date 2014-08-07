
#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include "State.h"
#include <Servo.h>

#define ZERO_VALUE 90
#define FULL_SPEED 65

#define FORWARDS 1
#define BACKWARDS -1

#define MOTOR_CW 1
#define MOTOR_CCW -1



class Motors
{
	public:
		Motors (void);
                void fullStop (void);
                void setMotorSpeed(int newSpeed);
                void setTurnSpeed(int newSpeed);
                void setMotorDir(int newDir);
                void setTurnDir(int newDir);
                void driveRobot (State state, signed int error);
                
                int leftValue;
                int rightValue;
	private:
                void checkClipping();
                void straight (signed int error);
                void turn (void);
                
                int _motorSpeed;
                int _motorDir;
                int _turnSpeed;
                int _turnDir;

                
                
	
    
};

#endif
