/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
#include "WaveArm.h"
#include "Servo.h"

volatile unsigned long tick = 0;
Servo sweepArmLeft;   
Servo sweepArmRight;    
WaveArm sweeperArms; 


void setup() 
{ 
  Serial.begin(9600);
  cli();
	TCCR1A = 0x00; //normal operation mode
	TCCR1B = 0x03; //64x prescale for 250kHz clock
	TCNT1=0x0000; //16bit counter register initialised to 0

        TCCR2A = 0x00; //normal mode
        TCCR2B = 0x04; //64 prescale for 1ms overflow rate
        TCNT2 = 0x0000; //Zero it
        TIMSK2 = (1<<TOIE2); //interrupt on TCNT2 overflow
  sei(); 
  
	sweepArmLeft.attach(11); 
	sweepArmRight.attach(10); 

} 

ISR(TIMER2_OVF_VECT){
   tick++; 
}

void loop() 
{

sweeperArms.collect(sweepArmLeft, sweepArmRight);
Serial.println(tick);

} 

