/* 
** Frequency calculator for whisker board
** written by Sarah Howe
*/ 

#define CONV 250000 // for 1 clock tick every 4us (250kHz clock)

volatile int count = 0;
int lastTime = 0;
int time = 0;
int deltaTime = 0;
long freq = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, WISR, FALLING); //enable interrupt0 (pin2)
  TCCR1A = 0x06; // 64x prescale for 250kHz clock
  TCNT1=0x0000; // 16bit counter register initialised to 0
}

void WISR() //WhiskerInterruptServiceRoutine
{
  count++; 
}

void loop()
{
  noInterrupts(); //critical section
  time = TCNT1;
  interrupts();
  deltaTime = time - lastTime; //time difference between last poll
  if(deltaTime > 0) //-ve if overflow and no NaN
  {
    freq = (count*CONV)/deltaTime; //calc frequency
  }
  lastTime = time; //<-- fuck up if dt = 0;
  //Serial.print(count-lastCount);
  Serial.println(freq);
  //lastCount = count;
}
