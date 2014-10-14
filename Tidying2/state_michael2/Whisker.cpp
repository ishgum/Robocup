#include "Whisker.h"
#include "schedule.h"

Whisker::Whisker(void){
	count = 3000;
	pulses = 0;
	lastTime = 0;
	time = 0;
	deltaTime = 0;
	freq = 0;
	object = false;
}

int t_tick = 0;
bool Whisker::detect (int detect_threshold){
 	cli(); //critical section
	time = TCNT1;
	pulses = count; 
	sei();
	deltaTime = time - lastTime; //time difference between last poll
	if(deltaTime == 0){ //-ve if overflow and no NaN
		Serial.println("Divide by 0 error in whisker");
                return -1;
	}else{
		freqRead = (pulses*CONV)/deltaTime; 
	}
	count = 0; //reset count
	lastTime = time;

	filter_reg = filter_reg - (filter_reg >> FILTER_SHIFT) + freqRead;
	freq = filter_reg >> FILTER_SHIFT;
        //Serial.print(" ");
        //Serial.println(freq);
   t_tick++;
   if (t_tick>1000 && detect_threshold == DETECT_THRESHOLD_SIDE ){
   Serial.println(freq);
   t_tick = 0;
   }
        if (freq <= DETECT_THRESHOLD_ROBOT){
                object = -1;
        }
	else if (freq <= detect_threshold){
		object = true;    
        }else{
		object = false;
	}  
	return object;
}

