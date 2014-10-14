
#define DETECT_BUFFER 5







void findWeights (void) {
  
  //Serial.println(whisker.detect(DETECT_THRESHOLD_FRONT));
  foundWeight = whisker.detect(DETECT_THRESHOLD_FRONT);
    
  if (limitRamp.switchState == SWITCH_ON && sweep_dir == WAITING) {
    weightCollect = true;
  }
  
  
  if (foundWeight && limitWeight.switchState == SWITCH_ON && detected == false) {         
     detectCount++;
     Serial.println("here");
  }
  
  if (detectCount == DETECT_BUFFER) {
    sweep_dir = SWEEP1;
    setMotorSpeed(MIN_SPEED);
    detectCount = 0;
    collectAttempt = 0;
    detected = true;
    //Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  }
  
  if (detected == true) {
    collect();
  }
}

void collect(){
  //Serial.println(sweep_dir);
  switch (sweep_dir) {
    
    case SWEEP1:
    
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       gateArm.setDesiredAngle(0);
       sweep_dir = LOWER;
     }
     
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     sweepAll();
     driveState.updateState(STATE_STOPPED);
     
    break;
    
    
    case LOWER:   
      if (leftArm.checkMoving() == false && rightArm.checkMoving() == false) {
        driveState.updateState(STATE_STRAIGHT);
      }
      
      if (gateArm.checkMoving() == false) {
        if (wait(2, 1000)) {
          rightArm.setDesiredAngle(180);
         leftArm.setDesiredAngle(180);
         sweep_dir = SWEEPING_IN;
        }
      }
    break;
    
    
     case SWEEPING_IN:
       if(leftArm.checkMoving() == false && rightArm.checkMoving() == false && gateArm.checkMoving() == false){
         sweep_dir = WAITING;
       }
     break;
    
    
      case WAITING:

        if (wait(3, 2000)) {
          sweep_dir = SWEEP1;
          collectAttempt++;  
        }
        
        if (weightCollect || collectAttempt == 2) {
            rightArm.setDesiredAngle(0);
            weightCollect = false;
            leftArm.setDesiredAngle(0);
            sweep_dir = SWEEPING_OUT;
            resetWait(3);
        } 
        
        if (collectAttempt == 2) {
          navigationState.updateState(STATE_EVACUATE);
        }
        
     break;
     
     
     
     case SWEEPING_OUT:
       if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
         gateArm.setDesiredAngle(110);
         sweep_dir = RAISE;
       }
     break;
     
     
     
     case RAISE:
       if (gateArm.checkMoving() == false) {
         if (wait (6, 500)) {
           sweep_dir = STATIC;
           leftArm.setDesiredAngle(110);
           rightArm.setDesiredAngle(110);
         }

       }
     break;
     
    
    case STATIC:
       if(leftArm.checkMoving() == false && rightArm.checkMoving() == false && gateArm.checkMoving() == false){
         detected = false;
         setMotorSpeed(DEFAULT_SPEED);
         sweep_dir = SWEEP1;
       }
     break;     
     }
}
