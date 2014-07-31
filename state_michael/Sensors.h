
#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

#define FILTER_SIZE 8

class Sensors
{
	public:
		Sensors (int port);
		void updateSensor();
		int filteredRead;
		int found;
	private:
		int _port;
		int _currentRead;
		int _index;
		int _filterArray[FILTER_SIZE];
	
    
};

#endif
