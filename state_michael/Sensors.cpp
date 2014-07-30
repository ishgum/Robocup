
#include "Arduino.h"
#include "Sensors.h"

Sensors::Sensors(int port)
{
  int _port = port;
  int _currentRead= 0;
  int _index = 0;
  int _filterArray[FILTER_SIZE] = {0};
  int _filteredRead = 0;
  int _found = false;
}


