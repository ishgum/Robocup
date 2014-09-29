#include "WaveArm.h"

/* Functions to move the sweeper arms */


WaveArm::WaveArm(bool input_loc, int input_angle_in, int input_angle_out)
{
        loc = input_loc;
        angle_in = input_angle_in;
        angle_out = input_angle_out;
        angle = 0;
        angle_right = 0;
        dir = MOVING_IN;
}

bool WaveArm::sweepOut(Servo sweeper){
       bool full_out = false;
       if(angle < angle_out){
              angle += 1;
       }
       if(angle = angle_out){
              full_out = true; 
       }
       Serial.println(angle);
 
       if(loc == LEFT_SIDE){      
               sweeper.write(angle);
       }else{
               sweeper.write(180-angle);
       }
       return full_out;
}

bool WaveArm::sweepIn(Servo sweeper){
       bool full_in = false;
       if(angle > angle_in){
       angle -= 1;
       }
 if(angle == angle_in){
   full_in = true;
 }
 Serial.print("sweepOut ");
 Serial.println(angle);
 
 if(loc == LEFT_SIDE){
   sweeper.write(angle);
 }else{
   sweeper.write(180-angle);
 }
 return full_in;
}


                //lower gate
                //sweepin
                //wait
                //sweepout
                //raisegate
bool WaveArm::collect(){
         bool collected = false;
         if(dir = MOVING_IN){
           
                 if(gate_down == false && gate.ready()){
                         gate_down = sweepIn(gateServo);
                 }
                 if(gate_down == true && collectorArms.ready()){
                        sweepIn(sweepArmLeft);
                        arms_in = sweepIn(sweepArmRight);
                        if(arms_in == true){
                                dir = WAITING;
                        }
                 } 
         }
         if(dir == WAITING){
                 //wait for collected trigger
                 dir = MOVING_OUT;
         }
         if(dir = MOVING_OUT){
                 if(arms_in == true && collectorArms.ready()){
                         sweepOut(sweepArmLeft);
                         arms_in != sweepOut(sweepArmRight);
                 }
                 if(arms_in == false && gate.ready()){
                         gate_down != sweepOut(gateServo);
                         if(gate_down == false){
                                 dir == MOVING_IN;
                                 collected = true;
                         }  
                 }
         }
         return collected;
}
//int WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
//	if(angle < ANGLE_OUT || angle_right < ANGLE_OUT){
//                if(angle < ANGLE_OUT){
//		        angle += 1;
//                }
//                if(angle>=(SWEEP_OUT_DELAY) && angle_right < ANGLE_OUT){
//                        angle_right += 1;
//                }
//		sweepArmLeft.write(angle);
//                sweepArmRight.write(180-(angle_right));
//                temp_dir = MOVING_OUT;
//	}else{
//		temp_dir = MOVING_IN;
//	}
//    return temp_dir;
//}
//
//
//int WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
//	if(angle > ANGLE_IN){
//		sweepArmLeft.write(angle);
//                sweepArmRight.write(180-angle);
//		angle-= 1;
//                temp_dir = MOVING_IN;
//	}else{
//                angle_right = 0;
//		temp_dir = WAITING;
//	}
//    return temp_dir;
//}


//250kHz clock input is in ms delay between movement 6 optimal, 3 max
//bool WaveArm::collect(Servo sweepArmLeft, Servo sweepArmRight){
  //sweepIn(sweepArmLeft, sweepArmRight);
  //return 1;
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
        
//}

//bool WaveArm::sweep(Servo sweepArmLeft, Servo sweepArmRight){
//        bool collecting = true;
//        if(armLocation == MOVING_IN){
//                armLocation = sweepIn(sweepArmLeft, sweepArmRight);
//        }
//        if(armLocation == WAITING){
//          //wait until collected 
//                delay(1000);
//                armLocation = MOVING_OUT;
//        }        
//        if(armLocation == MOVING_OUT){
//                armLocation = sweepOut(sweepArmLeft, sweepArmRight);
//                if(armLocation == MOVING_IN){
//                      collecting = false;
//                }
//        }
//        return collecting;
//}

//bool WaveArm::collected(void){
//        bool collected = false;
//        if(collectorSwitch.on()){
//                collected = true;
//        }
//        
//        return collected;
//}
//
//
//
//bool WaveArm::sweep(Servo sweepArmLeft, Servo sweepArmRight){
//        sweepArmLeft.write(angle);
//        return collecting;
//}

