#ifndef PCFC_HPP
#define PCFC_HPP

#include "Arduino.h"
#include "PCF8575.h"
#include "defines.hpp"

namespace PCFC{
  void interrupt_call_back();
  void begin();
  void digitalWrite(int index, bool state);
  bool digitalRead(int index);
  static bool key_change;
  static PCF8575::DigitalInput d2; 
  static PCF8575 e1(0x20);
  static PCF8575 e2(0x21, INTERRUPT_PIN, interrupt_call_back);
  const int temperature[8] = { 0, 1, 2, 3, 4, 5, 6, 7};
  const int luminosity[8]  = {15,14,13, 8, 9,10,11,12};
  const int moisture[8]    = {31,30,29,24,25,26,27,28};
}

#endif