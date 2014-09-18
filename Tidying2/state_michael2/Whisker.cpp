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

	filter_reg = filter_reg - (filter_reg >> FILTER_SHIFT) + freqRead;
	freq = filter_reg >> FILTER_SHIFT;
        //Serial.println(freq);
	if (freq < DETECT_THRESHOLD){
		object = true;    
	}
	else{
		object = false;
	}  
	return object;
}

