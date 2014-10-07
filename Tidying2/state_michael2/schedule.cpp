#include "schedule.h"
#include "Arduino.h"

static bool called[WAIT_ARRAY_SIZE] = {false};
static unsigned long prevTime[WAIT_ARRAY_SIZE];

schedule::schedule(int input_scheduleTime){
	scheduleTime = input_scheduleTime;

	prevCall = millis();
	scheduleReady = false;

}

bool schedule::ready (void) {
    if ((millis() - prevCall) > scheduleTime) {
	scheduleReady = true;              
    }
    
    else
    {
	scheduleReady = false;
    }
    return scheduleReady;
}



bool wait (int instance, unsigned long delayTime) {
  if (called[instance] == false) {
    prevTime[instance] = millis();
    called[instance] = true;
  }
  
  else if ((millis() - prevTime[instance]) > delayTime) {
    called[instance] = false;
    return true;
  }
  
  else {
    return false;
  }
}
  
  
  
