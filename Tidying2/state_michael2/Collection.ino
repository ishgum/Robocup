
int sweep_dir = SWEEP1;


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
     sweepAll();
     if(leftArm.moving == false && rightArm.moving == false){
       gateArm.setDesiredAngle(50);
       if(millisDelay(1000)){
           sweep_dir = LOWER;
       }           
     }
     
  case LOWER:   
    //gateArm.setDesiredAngle(50);
    if (gateArm.moving == false) {
      leftArm.setDesiredAngle(180);
      rightArm.setDesiredAngle(180);
      sweep_dir = SWEEPING_IN;
  break;

  case SWEEPING_IN:
     if(leftArm.moving == false && rightArm.moving == false){
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
}
