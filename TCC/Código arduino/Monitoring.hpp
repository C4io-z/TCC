#ifndef MONITORING_HPP
#define MONITORING_HPP

#include "Arduino.h"
#include "sensors.hpp"
#include "Internet.hpp"
#include "actuators.hpp"

namespace Monitoring{
  static float week[6][8];
  static float month[6][8];
  static float year[6][8];
  static float all[6][8];

  void dailyUpdate(int address);
  void weeklyUpdate(int address);
  void monthlyUpdate(int address);
  void yearlyUpdate(int address);
  void allUpdate(int address);
  
}

#endif