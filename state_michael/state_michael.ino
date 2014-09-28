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
schedule collectorArms(6);
schedule gate(3);
Switch powerSwitch(A3);
Switch collectorSwitch(A4);//????????
Gate frontGate;

bool collect_trigger = false;

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
  
	sweepArmLeft.attach(11); 
	sweepArmRight.attach(10); 
        gateServo.attach(3);//?????????
        powerSwitch.Init();
        collectorSwitch.Init();

} 


void WISR(void)
{
    whisker.count++;
}


void loop() 
{
        if(powerSwitch.on()){
                if(whisker.detect()){
                        collect_trigger = true;
                }
                if(collect_trigger){
                        collect_trigger = sweeperArms.collect(sweepArmLeft, sweepArmRight); 
                }
        }else{
        }
}
//need knockover modules

