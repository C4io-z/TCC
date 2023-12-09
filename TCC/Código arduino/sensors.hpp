#ifndef SENSORS_HPP
#define SENSORS_HPP
#include "defines.hpp"
#include "Arduino.h"
#include <DHT22.h>

// SAF R  O I O H

namespace sensors{
  void read();
  void setAddress(int i);
  float moistureLinearity(int m);
  const int multiplex[8] = {3,0,1,2,4,6,7,5};
  float get(int type, int address);

  namespace moisture{
    static float sensors[8];
  }
  namespace luminosity{
    static float sensors[8];
  }
  namespace temperature{
    static float sensors[8];
    static DHT22 dht22[8] = {DHT22(TEMPERATURE),DHT22(TEMPERATURE),
                             DHT22(TEMPERATURE),DHT22(TEMPERATURE),
                             DHT22(TEMPERATURE),DHT22(TEMPERATURE),
                             DHT22(TEMPERATURE),DHT22(TEMPERATURE)}; 
  }
}

#endif