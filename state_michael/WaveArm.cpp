#include "Servo.h"
#include "WaveArm.h"
#include "Gate.h"
/* Functions to move the sweeper arms */


WaveArm::WaveArm(void)
{
  angleRightArm = 0;
  angleLeftArm = 0;
}

bool WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle<ANGLE_MAX){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle += 1;
                temp_dir = ARMS_OUT;
	}else{
		temp_dir = ARMS_IN;
	}
    return temp_dir;
}

bool WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle>ANGLE_MIN){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle -= 1;
                temp_dir = ARMS_IN;
	}else{
		temp_dir = ARMS_OUT;
	}
    return temp_dir;
}

//250kHz clock input is in ms delay between movement 6 optimal, 3 max
bool WaveArm::collect(Servo sweepArmLeft, Servo sweepArmRight){
 	curr_time = millis();
 	delta_ms = (curr_time-prev_time);
        
        if(delta_ms >= SPEED_MS){
                if(collecting){
                        if(gate_down){
                                collecting = sweep(); //when finished, not_collecting
                        }else{
                                gate_down = gate.lowerGate();
                        }
                }else{ //not_collecting
                        gate_down = raiseGate();   //put 'em up
                        if(gate_down == false){                              //gate up
                                collecting = true; //reset for next time
                                return true; 
                        }
                }
        }
//	Serial.print("angle: ");
//	Serial.println(armLocation);
}

bool WaveArm::sweep(void){
        if(armLocation == MOVING_IN){
          //keep doing that
        }
        if(armLocation == WAITING){
         //wait until collected 
        }        
        if(armLocation == MOVING_OUT){
         //keep doing that 
        }
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


