
int sweep_dir = STATIC;
//int originalTick = 0;

void findWeights (void) {
  if (whisker.detect() && sweep_dir == STATIC) {         
     collect_trigger = true;
     //sweep_dir = SWEEP1;
  }
  if (collect_trigger == true) {
  collect();
  }
}

void collect(){
  //Serial.println(sweep_dir);
  switch (sweep_dir) {
    
    case SWEEP1:
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       sweep_dir = LOWER;
     }
    break;
  
  
    case LOWER:   
      gateArm.setDesiredAngle(50);
      
      if (gateArm.checkMoving() == false) {
        sweep_dir = SWEEPING_IN;
        delay(1000);
      }
    break;
 
 
    case SWEEPING_IN:
     leftArm.setDesiredAngle(180);
     rightArm.setDesiredAngle(180);
        
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       sweep_dir = WAITING;
     }
     break;
    
    
     case WAITING:
     
        if (weightCollect) {
            sweep_dir = SWEEPING_OUT;
            weightCollect = false;
        } 
     break;
     
    case SWEEPING_OUT:
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       sweep_dir = RAISE;
     }
     break;
     
     
     case RAISE:
     gateArm.setDesiredAngle(110);
     
     if (gateArm.checkMoving() == false) {
       sweep_dir = STATIC;
     }
     break;
     
     
     case STATIC:
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle( 0);
     gateArm.setDesiredAngle(120);
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false && gateArm.checkMoving() == false){
       collect_trigger = false;
     }
     break;
     
     }
}
