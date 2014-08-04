
#include "Magno.h"

#include <Wire.h>
#include "FreeSixIMU.h"
#include "HMC5883L.h"



Magno::Magno(void)
{
  Wire.begin();
  sixDOF = FreeSixIMU();
  currentAngle = 0;

}


void Magno::init() {
      //Initialising magnet sensor
  delay(5);
  sixDOF.init(); //init the Acc and Gyro
  delay(5);
  compass = HMC5883L(); // init HMC5883
  compass.SetMeasurementMode(Measurement_Continuous);
  sixDOF.getEuler(angles);
  
  getHeading();
}


void Magno::getHeading(){
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();
   
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)
 
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  heading = atan2(scaled.YAxis, scaled.XAxis); 
   
  float declinationAngle = 0.0457;
  heading += declinationAngle;
   
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
     
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
    
  // Convert radians to degrees for readability.
  heading = heading * 180/M_PI;
}


float Magno::findAngle(void)
{
  sixDOF.getEuler(angles);
  delay(5);
  getHeading();
  currentAngle = angles[0];
}
