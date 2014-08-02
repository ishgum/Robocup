
#include "Magno.h"

#include <Wire.h>
#include <FreeSixIMU.h>
#include <HMC5883L.h>



Magno::Magno(void)
{
  float angles[3];
  FreeSixIMU sixDOF = FreeSixIMU();
  HMC5883L compass;
  
    //Initialising magnet sensor
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  compass = HMC5883L(); // init HMC5883
  compass.SetMeasurementMode(Measurement_Continuous);
  sixDOF.getEuler(angles);

}


float Magno::findAngle(void)
{
  sixDOF.getEuler(angles);
  return angles[0];
}
