
#include "Sensors.h"

Sensors::Sensors(int port)
{
  _port = port;
  _currentRead= 0;
  _index = 0;
  filteredRead = 0;
  _found = 0;
  ignore = true;
}


// Updates a single sensor using a MAF

void Sensors::updateSensor () {
    _currentRead = analogRead(_port);
    _filterArray[_index] = _currentRead;
    
    unsigned int temp_sum = 0;
    for (int i = 0; i < SENSOR_FILTER_SIZE; i++)
    {
        temp_sum += _filterArray[i];
    }
    filteredRead = temp_sum / SENSOR_FILTER_SIZE;
    _index++;
    
    
    if (_index == (SENSOR_FILTER_SIZE)) {
        _index = 0;
    }
}


// If the robot drives up to a wall, stop and then determine which direction it should turn

int Sensors::findWall (unsigned int recognitionDistance) {
    if (filteredRead >= recognitionDistance) {
      _found = 1;
    }
    else if (filteredRead < recognitionDistance) {
      _found = 0;
    }
    
    return _found;
}

