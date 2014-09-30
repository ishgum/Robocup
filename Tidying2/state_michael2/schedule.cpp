#include "schedule.h"
#include "Arduino.h"



schedule::schedule(int delayTime){
	delay_time = delayTime;
	current_time = 0;
	prev_time = 0;
	progress = false;
	delta_time = 0;
}

bool schedule::ready(void){
	if(millis()%delay_time == 0){
		progress = true;                 
	}else{
		progress = false;
	}
	return progress;
}


