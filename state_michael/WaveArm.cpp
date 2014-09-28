#include "WaveArm.h"

/* Functions to move the sweeper arms */


WaveArm::WaveArm(void)
{
        angleRightArm = 0;
        angleLeftArm = 0;
}

bool WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angleLeftArm < ANGLE_MAX && angleRightArm < ANGLE_MAX){
		sweepArmLeft.write(angleLeftArm);
                sweepArmRight.write(180 - angleRightArm);
		angleLeftArm += 1;
		angleRightArm += 1;
                temp_dir = MOVING_IN;
	}else{
		temp_dir = WAITING;
	}
    return temp_dir;
}

bool WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angleLeftArm > ANGLE_MIN && angleRightArm > ANGLE_MIN){
		sweepArmLeft.write(angleLeftArm);
                sweepArmRight.write(angleRightArm);
                if(angleLeftArm > ANGLE_MIN){
		        angleLeftArm-= 1;
                }
                if(angleLeftArm<=170){
                        angleRightArm = angleLeftArm + SWEEP_OUT_DELAY;
                }
                temp_dir = MOVING_OUT;
	}else{
		temp_dir = MOVING_IN;
	}
    return temp_dir;
}

//250kHz clock input is in ms delay between movement 6 optimal, 3 max
bool WaveArm::collect(Servo sweepArmLeft, Servo sweepArmRight){
       if(collectorArms.ready()){
                if(collecting){
                        if(gate_down){
                                collecting = sweep(sweepArmLeft, sweepArmRight); //when finished, not_collecting
                        }else{
                                gate_down = frontGate.lowerGate();
                        }
                 }else{ //not_collecting
                        gate_down = frontGate.raiseGate();   //put 'em up
                        if(gate_down == false){                              //gate up
                                collecting = true; //reset for next time
                                return true; 
                        }
                }
        }
//	Serial.print("angle: ");
//	Serial.println(armLocation);
}

bool WaveArm::sweep(Servo sweepArmLeft, Servo sweepArmRight){
        bool collecting = false;
        if(armLocation == MOVING_IN){
                armLocation = sweepIn(sweepArmLeft, sweepArmRight);
        }
        if(armLocation == WAITING){
          //wait until collected 
                delay(1000);
                armLocation = MOVING_OUT;
        }        
        if(armLocation == MOVING_OUT){
                armLocation = sweepOut(sweepArmLeft, sweepArmRight);
                if(armLocation == MOVING_IN){
                      collecting = true;
                }
        }
        return collecting;
}

bool WaveArm::collected(void){
        collector = analogRead(A2);
        if(collector == 0){
                result = false;
        }else{
                result = true;
        }
        
        Serial.print("     col?: ");
	Serial.println(result);
        
        return result;
}


