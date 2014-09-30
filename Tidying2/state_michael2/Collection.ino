int sweep_dir = SWEEP1;

void findWeights (void) {
  if(whisker.detect() && sweep_dir == SWEEP1){         
     collect_trigger = true;
  }
  if(collect_trigger == true){
     collect();
     
  }
}

void collect(){
  
  if (sweep_dir == SWEEP1) {
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     sweepAll();
     if(leftArm.moving == false && rightArm.moving == false){
       gateArm.setDesiredAngle(50);
       if(millisDelay(1000)){
           sweep_dir = LOWER;
       }
     }
  }
     
  else if (sweep_dir == LOWER) {   
    //gateArm.setDesiredAngle(50);
    if (gateArm.moving == false) {
      leftArm.setDesiredAngle(180);
      rightArm.setDesiredAngle(180);
      sweep_dir = SWEEPING_IN;
    }
  }
  else if (sweep_dir == SWEEPING_IN) {
     if(leftArm.moving == false && rightArm.moving == false){
       sweep_dir = WAITING;
     }
  }
  else if (sweep_dir == WAITING){
      //if (!limitRamp.switchState) {
          leftArm.setDesiredAngle(0);
          rightArm.setDesiredAngle(0);
          sweep_dir = SWEEPING_OUT;
     // } 
  }
  else if (sweep_dir == SWEEPING_OUT) {
     if(leftArm.moving == false && rightArm.moving == false){
       gateArm.setDesiredAngle(110);
       sweep_dir = RAISE;
     }
  }
  else if (sweep_dir == RAISE) {
     if (gateArm.moving == false) {
       sweep_dir = STATIC;
       leftArm.setDesiredAngle(90);
       rightArm.setDesiredAngle(90);
     }
  }
     
  else if (sweep_dir == STATIC) {
     if(leftArm.moving == false && rightArm.moving == false){
       collect_trigger = false;
       sweep_dir = SWEEP1;
     }
  }
}
