#include "Servo.h"
#include "WaveArm.h"
/* Functions to move the sweeper arms */

#define ARMS_IN 1
#define ARMS_OUT 0

WaveArm::WaveArm(void)
{
  currentAngle = 0;
  currentDirection = ARM_CLOCKWISE;
}

bool WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle<180){
		sweepArmLeft.write(angle);
		sweepArmRight.write(angle);
		angle += 1;
	}else{
		return 1;
	}
}

bool WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle>0){
		sweepArmLeft.write(angle);
		sweepArmRight.write(angle);
		angle -= 1;
	}else{
		return 0;
	}
}

//250kHz clock input is in ms delay between movement 6 optimal, 3 max
void WaveARm::collect(int speed_ms){
	if(time && ARMS_OUT){
		sweepIn(sweepArmLeft, sweepArmRight);
	}
	if(not_collected()){
		wait;
	}
	if(time && ARMS_IN){
		sweepOut(sweepArmLeft, SweepArmRight);
	}
}

void WaveArm::waveArm(bool waving, Servo servo, unsigned long tick){
    if (tick % 10 == 0 && waving) {
      servo.write(currentAngle); 
      armPos();
   }
