#include "Whisker.h"

Whisker::Whisker(void){
	count = 0;
	pulses = 0;
	lastTime = 0;
	time = 0;
	deltaTime = 0;
	freq = 0;
	object = false;
}


bool Whisker::detect (bool quick){
  _prevObject = object;
  cli(); //critical section
  time = TCNT1;
  pulses = count; 
  sei();
  deltaTime = time - lastTime; //time difference between last poll
  if(deltaTime < MAX_TIME){ //-ve if overflow and no NaN
    freq = (pulses*CONV)/deltaTime; 
  }
  count = 0; //reset count
  lastTime = time;
//  Serial.print("freq: ");
  Serial.println(freq);
  if (freq < DETECT_THRESHOLD){
    object = true;    
  }
  else{
    object = false;
  }  
  if(quick){
   return object; 
  }
  if(doubleCheck(object)){
    _noChange = object;
    return object; 
  }
  else{
    return _noChange;
  }
}

bool Whisker::doubleCheck(bool object) {
  //Serial.print("sc: ");
  //Serial.println(_sureCount);
  if(_sureCount >= TOLERANCE){
     _sureCount = 0;
    return true; 
  }
  else if(object == _prevObject){
     _sureCount++; 
     return false;
  }
  else{
    _sureCount = 0;
    return false;
  }
}

  
