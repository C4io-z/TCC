#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP

#include "defines.hpp"
#include "PCFC.hpp"

namespace actuators{

  void update();
  void start();
  void set(int type, char index, unsigned int onTime);
  bool get(int type,char index);

  namespace moisture{
    static bool state[8];
    static unsigned long ontime[8];
  }
  namespace temperature{
    static bool state[8];
    static unsigned long ontime[8];
  }
  namespace luminosity{
    static bool state[8];
    static unsigned long ontime[8];
  }
}

#endif