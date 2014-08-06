#include "Whisker.h"

Whisker::Whisker(void)
{
	count = 0;
	pulses = 0;
	lastTime = 0;
	time = 0;
	deltaTime = 0;
	freq = 0;
	object = false;
}


bool Whisker::detect (void)
{
  noInterrupts(); //critical section
  time = TCNT1;
  pulses = count; 
  interrupts();
  deltaTime = time - lastTime; //time difference between last poll
  if(deltaTime < MAX_TIME) //-ve if overflow and no NaN
  {
    freq = (pulses*CONV)/deltaTime; 
  }
  count = 0; //reset count
  lastTime = time; //<-- fuck up if dt = 0;
  Serial.print(freq);
  Serial.print("\t");
  Serial.println(object);
  if (freq < DETECT_THRESHOLD) 
  {
    object = true;    
  }
  return object;
{

void Whisker::WISR(void)
{
    count++;
}
