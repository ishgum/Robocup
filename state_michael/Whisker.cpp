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


bool Whisker::detect (void){
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
  Serial.print(freq);
  Serial.print("\t");
  Serial.println(object);
  if (freq < DETECT_THRESHOLD){
    object = true;    
  }
  else{
    object = false;
  }
  return object;
}

//void Whisker::WISR(void){
//    count++;
//}
