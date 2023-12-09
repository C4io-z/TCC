#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <EEPROM.h>
#include <Arduino.h>
#include "defines.hpp"


struct Routine{
  struct{
    struct{
      char index[8];
    }Module[6];
    struct{
      char Value, OP, Time;
    }Config[3];
  }Routine[8];
};

/*
r[8]--|--[[6][8]]
      |
      |--[[3][2]]
//*/

namespace Memory{
  static char *pointer;
  void start();
  void submit();
  Routine* getPointer();
  void set(int sub_sector, String data);
  String get(int sub_sector);
  void add(int sub_sector, int module, int index);
  void remove(int sub_sector, int module, int index);
  void setRoutine(int sub_sector, int module, char value, char config, char time);
}



#endif 