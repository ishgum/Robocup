
int sweep_dir = STATIC;
bool detected = false;
//int originalTick = 0;
#define DETECT_BUFFER 6

void findWeights (void) {
  //Serial.println(whisker.detect());
  if (whisker.detect() && detected == false) {         
     weightDetect++;
     Serial.println("here");
  }
  
  if (weightDetect >= DETECT_BUFFER) {
    sweep_dir = SWEEP1;
    detected = true;
    weightDetect = 0;
  }
  
  if (detected == true) {
    collect();
  }
  if (!whisker.detect()) {
    weightDetect = 0;
  }
}

void collect(){
  //Serial.println(sweep_dir);
  switch (sweep_dir) {
    
    case STATIC:
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false && gateArm.checkMoving() == false){
       detected = false;
       setMotorSpeed(80);
     }
     break;
     
     
    case RAISE:
     if (gateArm.checkMoving() == false) {
       sweep_dir = STATIC;
       leftArm.setDesiredAngle(110);
       rightArm.setDesiredAngle(110);
     }
     break;
     
     
    case SWEEPING_OUT:
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       gateArm.setDesiredAngle(110);
       sweep_dir = RAISE;
     }
     break;
     
     
      case WAITING:
      //collect_trigger = true;
        if (weightCollect) {
            weightCollect = false;
            motorsGoing = true;
            //changeToTurnState();
            collect_trigger = false;
            
            leftArm.setDesiredAngle(0);
            rightArm.setDesiredAngle(0);
            sweep_dir = SWEEPING_OUT;
        } 
        if (tick % 2000 == 0) {
          sweep_dir = SWEEP1;
           
        }
     break;
     
     
    case SWEEPING_IN:
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false && gateArm.checkMoving() == false){
       sweep_dir = WAITING;
     }
     break;
     
     
     
     case LOWER:   
      if (gateArm.checkMoving() == false) {
        if(tick % 500 == 0){
          startTime = 0;
          leftArm.setDesiredAngle(180);
          rightArm.setDesiredAngle(180);
          sweep_dir = SWEEPING_IN;
       }
      }
    break;
     
    
    case SWEEP1:
     setMotorSpeed(60);
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     sweepAll();
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       gateArm.setDesiredAngle(50);
       sweep_dir = LOWER;
     }
    break;
     
     }
}
