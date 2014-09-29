

bool collect(){
    if (gateArm.moving == false) {
       leftArm.setDesiredAngle(180);
       rightArm.setDesiredAngle(180);
   } 
}




void findWeights (void) {
  if(whisker.detect()){         
     collect_trigger = true;
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     gateArm.setDesiredAngle(80); 
  }
  if(collect_trigger == true){
     collect();
     
  }
}
