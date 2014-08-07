#include "Retrieve.h"

//Aligns the robot to a detected weight

bool align(void){
	//since arm on the right, assume target always clockwise of current location
	//input detector arm triggered if 2 are used to determine dir to turn
	aligned = false;
	//check arm pos, note mag pos
	//change pos, check mag, change by D_armpos

	change_rotation = current - Magno.currentAngle;
	//want absolute change
	if(change_rotation < 0){
		change_rotation *= (-1);
	}
	
	rotation += change_rotation;

	//drive robo proportional to angle/target  etc.
	//PD control
	P = target - rotation; //-->0
	D = (rotation - p_rotation); //-->0
	
	//as a percentage
	motor_speed = (KP*P + KD*D)*100/FULLSPEED;
	Motors.turn(motor_speed, CW)	
			
	if(rotation == target){
		aligned = true;
	}

	p_rotation = rotation;
	return aligned;
}
