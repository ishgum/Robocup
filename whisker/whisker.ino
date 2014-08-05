/* 
** Frequency calculator for whisker board
** written by Sarah Howe
*/ 
#include <avr/io.h>
#include <avr/interrupt.h>

#define CONV 250000 //for 1 clock tick every 4us (250kHz clock)

volatile unsigned int count = 27;
unsigned int pulses = 27;
unsigned int lastTime = 0;
unsigned int time = 0;
unsigned int deltaTime = 0;
unsigned long freq = 0;

void setup()
{
  Serial.begin(9600);
  //attachInterrupt(0, WISR, FALLING); //enable interrupt0 (pin2)
  //pinMode(0, INPUT);
  cli(); //disable glob interrupts
  TCCR1A = 0x00; //normal operation mode
  TCCR1B = 0x03; //64x prescale for 250kHz clock
  TCNT1=0x0000; //16bit counter register initialised to 0
  EIMSK |=(1<<INT0); //interrupt 0 (pin 2)
  EICRA |=(1<<ISC01); //falling edge
  sei(); //enable glob interrupts
}

ISR(EXT_INT0_vect)
{
    count = 0;
}

void loop()
{
  noInterrupts(); //critical section
  time = TCNT1;
  pulses = count; //???
  interrupts();
  deltaTime = time - lastTime; //time difference between last poll
  if(deltaTime < 60000) //-ve if overflow and no NaN
  {
    freq = (pulses*CONV)/deltaTime; //calc frequency
  }
  //count = 0; //reset count
  lastTime = time; //<-- fuck up if dt = 0;
  //Serial.print(count-lastCount);
  Serial.println(count);
  //Serial.println("hello");
  //lastCount = count;
}
