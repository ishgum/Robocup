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
WaveArm sweeperArmLeft(LEFT_SIDE, 0, 180); //loc ain aout
WaveArm sweeperArmRight(RIGHT_SIDE, 0, 180);
WaveArm frontGate(RIGHT_SIDE, 90, 120);
Whisker whisker;
schedule collectorArms(6); //ms between each degree of movement
schedule gate(4);
Switch powerSwitch(A3);
Switch collectorSwitch(A4);


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
  tick++;
        if(powerSwitch.on()){
                if(whisker.detect()){         
                        collect_trigger = true;
                }
                if(collect_trigger == true){
                        if (collectorArms.ready()) {
                              //  collect();
                        }
                }
        }else{
                sweepArmLeft.write(180);
                sweepArmRight.write(0);
        }
}
//need knockover modules

