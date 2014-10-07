
#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

#define SENSOR_FILTER_SIZE 8

class Sensors
{
	public:
		Sensors (int port);
		void updateSensor();
                int findWall (unsigned int recognitionDistance);
		int filteredRead;
		int _found;
                bool ignore;
	private:
		int _port;
		int _currentRead;
		int _index;
		int _filterArray[SENSOR_FILTER_SIZE];
	
    
};

#endif
