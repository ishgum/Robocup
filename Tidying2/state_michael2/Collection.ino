
#define DETECT_BUFFER 5

static int sweep_dir = STATIC;


static bool weightCollect = false;
static bool detected = false;

static int detectCount = 0;
static int collectAttempt = 0;



void findWeights (void) {
  
  //Serial.println(whisker.detect());
  
  
  if (limitWeight.switchState == SWITCH_ON && weightCollect == false) {
    weightCollect = true;
  }
  
  
  if (whisker.detect() && detected == false ) {         
     detectCount++;
     Serial.println("here");
  }
  
  if (detectCount >= DETECT_BUFFER) {
    sweep_dir = SWEEP1;
    setMotorSpeed(MIN_SPEED);
    detectCount = 0;
    collectAttempt = 0;
    detected = true;
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  }
  
  if (detected == true) {
    collect();
  }
  if (!whisker.detect()) {
    //detectCount = 0;
  }

  
}

void collect(){
  //Serial.println(sweep_dir);
  switch (sweep_dir) {
    
    case SWEEP1:
    
     if(leftArm.checkMoving() == false && rightArm.checkMoving() == false){
       gateArm.setDesiredAngle(50);
       sweep_dir = LOWER;
     }
     
     leftArm.setDesiredAngle(0);
     rightArm.setDesiredAngle(0);
     sweepAll();
     
    break;
    
    
    case LOWER:   
      if (gateArm.checkMoving() == false) {
        if (wait(2, 500)) {
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
        
        if (weightCollect || collectAttempt == 3) {
            rightArm.setDesiredAngle(0);
            weightCollect = false;
            leftArm.setDesiredAngle(0);
            sweep_dir = SWEEPING_OUT;
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
       }
     break;     
     }
}
