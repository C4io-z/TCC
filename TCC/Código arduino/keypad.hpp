#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "Arduino.h"
#include "defines.hpp"
#include "PCFC.hpp"

namespace keypad{
  void tick();
  char getLastKey();
  static char lastKey;
  static char key;
  const char keypad[4][4] = {{'1','2','3','+'},
                             {'4','5','6','-'},
                             {'7','8','9','X'},
                             {'*','0','#','/'}};
}

#endif