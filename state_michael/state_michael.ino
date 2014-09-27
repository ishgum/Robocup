/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <Servo.h> 
#include "WaveArm.h"
#include "Servo.h"
#include "Whisker.h"
#include "schedule.h"
#include "Switch.h"


volatile unsigned long tick = 0;
Servo sweepArmLeft;   
Servo sweepArmRight;    
WaveArm sweeperArms; 

Whisker whisker;
schedule collectorArms;

void setup() 
{ 
  Serial.begin(9600);
  cli();
        attachInterrupt(5, WISR, FALLING);
        pinMode(18, INPUT); //green 19 is yellow
	TCCR1A = 0x00; //normal operation mode
	TCCR1B = 0x03; //64x prescale for 250kHz clock
	TCNT1=0x0000; //16bit counter register initialised to 0

//        TCCR2A = 0x00; //normal mode
//        TCCR2B = 0x04; //64 prescale for 1ms overflow rate
//        TCNT2 = 0x0000; //Zero it
//        TIMSK2 = (1<<TOIE2); //interrupt on TCNT2 overflow
  sei(); 
  
	sweepArmLeft.attach(11); 
	sweepArmRight.attach(10); 
     
        Switch powerSwitch(A3);
        powerSwitch.Init();

} 

void WISR(void)
{
    whisker.count++;
}

//ISR(TIMER2_OVF_VECT){
//   tick++; 
//}

void loop() 
{
        if(whisker.detect()){
                sweeperArms.collect(sweepArmLeft, sweepArmRight);
        }

} 

