#ifndef TIME_HPP
#define TIME_HPP
#include "time.h"
#include <WiFi.h>
#include "Internet.hpp"
#include "Monitoring.hpp"
#include "Routines.hpp"


namespace Time{
  static char* ntpServer = "pool.ntp.org";
  static long gmtOffset_sec = -3*3600;
  static int daylightOffset_sec = 0;

  void start();
  void update();
  void getTime();
  void getDate();
}


#endif