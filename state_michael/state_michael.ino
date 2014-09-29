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
#include "Gate.h"


volatile unsigned long tick = 0;
Servo sweepArmLeft;   
Servo sweepArmRight;
Servo gateServo;
WaveArm sweeperArms; 
Whisker whisker;
schedule collectorArms(6); //ms between each degree of movement
schedule gate(4);
Switch powerSwitch(A3);
Switch collectorSwitch(A4);
Gate frontGate;

bool collect_trigger = false;
int ct;

/*
**gate 13
**right knocker 11
**right sweeper 10
**frontIR servo 12
**left knocker 8 //broken cable?
**left sweeper 9
*/

void setup() 
{ 
  Serial.begin(9600);
  cli();
        attachInterrupt(5, WISR, FALLING);
        pinMode(18, INPUT); //green 19 is yellow
	TCCR1A = 0x00; //normal operation mode
	TCCR1B = 0x03; //64x prescale for 250kHz clock
	TCNT1=0x0000; //16bit counter register initialised to 0
  sei(); 
  
	sweepArmLeft.attach(9); 
	sweepArmRight.attach(10); 
        //gateServo.attach(13);
        powerSwitch.Init();
        collectorSwitch.Init();
        
        //get them in a nice position
        sweepArmLeft.write(180);
        sweepArmRight.write(0);
        //gateServo.write(90);

} 


void WISR(void)
{
    whisker.count++;
}


void loop() 
{
        if(powerSwitch.on()){
                if(whisker.detect()){
                        //collect_trigger = true;
                        ct = sweeperArms.sweepIn(sweepArmLeft, sweepArmRight);
                }else{
                        //if(collect_trigger){
                          //      Serial.print(collect_trigger);
                                ct= sweeperArms.sweepOut(sweepArmLeft, sweepArmRight); 
                        //}
                }
        }else{
        }
}
//need knockover modules

