#ifndef DEFINES_HPP
#define DEFINES_HPP

#define INTERRUPT_PIN 34

#define NUM_OF_MEASUREMENTS 10

#define LUMINOSITY  35
#define MOISTURE    32
#define TEMPERATURE 33

#define _A 27
#define _B 26
#define _C 25

#define LED_ON   16
#define LED_WiFi 17

enum Module_type{
  Moisture,
  Luminosity,
  Temperature
};

enum Modules{
  Moisture_sensor,
  Luminosity_sensor,
  Temperature_sensor,
  Moisture_actuator,
  Luminosity_actuator,
  Temperature_actuator
};
enum Time_space{
  day,
  week,
  month,
  year,
  all
};

#endif