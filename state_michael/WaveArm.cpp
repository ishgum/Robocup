#include "Servo.h"
#include "WaveArm.h"
/* Functions to move the sweeper arms */

#define CONV 250000
#define ARMS_IN 1
#define ARMS_OUT 0
#define ANGLE_MAX 180
#define ANGLE_MIN 0
#define SPEED_MS 6

WaveArm::WaveArm(void)
{
  angle = 0;
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
void WaveArm::collect(void){
	curr_time = TCNT1;
	delta_ms = (curr_time-prev_time)/CONV;
	if(delta_ms>SPEED_MS && armLocation==ARMS_OUT){
		armLocation = sweepIn(sweepArmLeft, sweepArmRight);
		prev_time = curr_time;
	}
	//if(not_collected()){
	//	wait;
	//}
	if(delta_ms>SPEED_MS && armLocation==ARMS_IN){
		armLocation = sweepOut(sweepArmLeft, SweepArmRight);
		prev_time = curr_time;
	}
}

void WaveArm::knockOver(){
	
}

bool WaveArm::collected(void){

}
