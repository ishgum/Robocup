#include "Servo.h"
#include "WaveArm.h"
/* Functions to move the sweeper arms */

#define CONV 250000
#define ARMS_IN 1
#define ARMS_OUT 0
#define ANGLE_MAX 180
#define ANGLE_MIN 0

WaveArm::WaveArm(void)
{
  currentAngle = 0;
  currentDirection = ARM_CLOCKWISE;
}

bool WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle<ANGLE_MAX){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle += 1;
	}else{
		return ARMS_IN;
	}
}

bool WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle>ANGLE_MIN){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle -= 1;
	}else{
		return ARMS_OUT;
	}
}

//250kHz clock input is in ms delay between movement 6 optimal, 3 max
void WaveArm::collect(int speed_ms){
	curr_time = ticks;
	delta_ms = (curr_time-prev_time)/CONV;
	if(delta_ms>speed_ms && armLocation==ARMS_OUT){
		armLocation = sweepIn(sweepArmLeft, sweepArmRight);
		prev_time = curr_time;
	}
	//if(not_collected()){
	//	wait;
	//}
	if(delta_ms>speed_ms && armLocation==ARMS_IN){
		armLocation = sweepOut(sweepArmLeft, SweepArmRight);
		prev_time = curr_time;
	}
}

void WaveArm::knockOver(){
	
}
