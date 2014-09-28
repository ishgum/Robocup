#include "schedule.h"
#include "Arduino.h"

schedule::schedule(void){
	delay_time;
	current_time = 0;
	prev_time = 0;
	progress = false;
	delta_time = 0;
}

bool schedule::ready(void){
	current_time = millis();
	delta_time = current_time - prev_time;
	if(delta_time > delay_time){
		progress = true;
	}else{
		progress = false;
	}
	return progress;
}
