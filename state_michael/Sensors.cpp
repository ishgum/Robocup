
#include "Sensors.h"

Sensors::Sensors(int port)
{
  _port = port;
  _currentRead= 0;
  _index = 0;
  setOff = false;
  filteredRead = 0;
  found = 0;
}


// Updates a single sensor using a MAF

void Sensors::updateSensor () {
	_currentRead = analogRead(_port);
	_filterArray[_index] = _currentRead;
	
	unsigned int temp_sum = 0;
	for (int i = 0; i < FILTER_SIZE; i++)
	{
		temp_sum += _filterArray[i];
	}
	
	filteredRead = temp_sum / FILTER_SIZE;
	
	_index++;
	if (_index == (FILTER_SIZE)) {
		_index = 0;
	}
}


// If the robot drives up to a wall, stop and then determine which direction it should turn

int Sensors::findWall (unsigned int recognitionDistance) {
    if (filteredRead >= recognitionDistance) {
      found = 1;
    }
    else if (filteredRead < recognitionDistance) {
      found = 0;
    }
    
    return found;
}

