
#include "ColourSense.h"

#include "Adafruit_TCS34725.h"


ColourSense::ColourSense(void)
{
  tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

}


void ColourSense::init() {
    if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}





void ColourSense::findColour(void)
{
  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &colour);

  tcs.setInterrupt(true);  // turn off LED
}
