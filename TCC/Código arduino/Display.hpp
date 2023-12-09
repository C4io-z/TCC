#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "Menu.hpp"
#include "LCDIC2.h"
#include "keypad.hpp"
#include "Internet.hpp"
#include "memory.hpp"

namespace display{
  static LCDIC2 lcd(0x27, 16, 2);
  void begin();
  void update();
}

#endif