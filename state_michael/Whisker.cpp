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


bool Whisker::detect (){;
 	cli(); //critical section
	time = TCNT1;
	pulses = count; 
	sei();
	deltaTime = time - lastTime; //time difference between last poll
	if(deltaTime == 0){ //-ve if overflow and no NaN
		return -1;
	}else{
		freqRead = (pulses*CONV)/deltaTime; 
	}
	count = 0; //reset count
	lastTime = time;

	filter_reg = filter_reg - (filter_reg >> FILTER_SHIFT) + freqRead;
	freq = filter_reg >> FILTER_SHIFT;

	if (freq < DETECT_THRESHOLD){
		object = true;    
	}
	else{
		object = false;
	}  
	return object;
}

