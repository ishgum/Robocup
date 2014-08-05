enum PinAssignments 
{
  IntPin = 2
};

unsigned long IntCount=0;


void setup() 
{
  pinMode(IntPin, INPUT); 
  // interrupt pin on interrupt 0 (pin 2)
  attachInterrupt(0, doIntIncrement, CHANGE);
  Serial.begin(9600);
}


void loop() 
{
  Serial.print(IntCount, DEC);
  Serial.println();
}


// Interrupt on A changing state
void doIntIncrement()
{
  IntCount++;  
}
