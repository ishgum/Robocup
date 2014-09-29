#include "WaveArm.h"

/* Functions to move the sweeper arms */


WaveArm::WaveArm(void)
{
        angle = 0;
}


int WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle < ANGLE_OUT){
		sweepArmLeft.write(angle);
		angle += 1;
                if(angle>=(SWEEP_OUT_DELAY)){
                        sweepArmRight.write(angle - SWEEP_OUT_DELAY);
                }
                temp_dir = MOVING_OUT;
	}else{
		temp_dir = MOVING_IN;
	}
    return temp_dir;
}


int WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle > ANGLE_IN){
		sweepArmLeft.write(angle);
                sweepArmRight.write(180-angle);
		angle-= 1;
                temp_dir = MOVING_IN;
	}else{
		temp_dir = WAITING;
	}
    return temp_dir;
}


//250kHz clock input is in ms delay between movement 6 optimal, 3 max
bool WaveArm::collect(Servo sweepArmLeft, Servo sweepArmRight){
  sweepIn(sweepArmLeft, sweepArmRight);
  return 1;
//       bool collect_trigger = true; 
//       Serial.print("\tCol? ");
//       Serial.println(collecting);
//                if(collecting){
//                        if(gate_down && collectorArms.ready()){
//                                collecting = sweep(sweepArmLeft, sweepArmRight); //when finished, not_collecting
//                        }else{
//                                if(gate.ready()){
//                                      gate_down = frontGate.lowerGate();
//                                }
//                        }
//                 }else{ //not_collecting
//                        if(gate.ready()){
//                               gate_down = frontGate.raiseGate();   //put 'em up
//                        }
//                        if(gate_down == false){                              //gate up
//                                collecting = true; //reset for next time
//                                collect_trigger = false; 
//                        }
//                }
        
}

bool WaveArm::sweep(Servo sweepArmLeft, Servo sweepArmRight){
        bool collecting = true;
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
                      collecting = false;
                }
        }
        return collecting;
}

bool WaveArm::collected(void){
        bool collected = false;
        if(collectorSwitch.on()){
                collected = true;
        }
        
        return collected;
}


