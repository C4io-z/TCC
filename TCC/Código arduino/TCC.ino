#include "Arduino.h"
#include "PCFC.hpp"
#include "sensors.hpp"
#include "keypad.hpp"
#include "actuators.hpp"
#include "LCDIC2.h"
#include "Display.hpp"
#include "Internet.hpp"
#include "Time.hpp"
#include "memory.hpp"
#include "Routines.hpp"

LCDIC2 lcd(0x27, 16, 2);

void setup(){

  Serial.begin(115200);

  pinMode(INTERRUPT_PIN, INPUT);
  pinMode(MOISTURE,     INPUT);
  pinMode(TEMPERATURE,  INPUT);
  pinMode(LUMINOSITY,   INPUT);

  pinMode(_A, OUTPUT);
  pinMode(_B, OUTPUT);
  pinMode(_C, OUTPUT);
  digitalWrite(_A, LOW);
  digitalWrite(_B, LOW);
  digitalWrite(_C, LOW);

  pinMode(LED_ON, OUTPUT);
  pinMode(LED_WiFi, OUTPUT);

  digitalWrite(LED_ON, HIGH);

  PCFC::begin();
  actuators::start();
  display::begin();
  Internet::start();
  Memory::start();

}    

void loop(){
  Time::update();
  keypad::tick();
  actuators::update();
  display::update();

  if(keypad::getLastKey() == '+'){
    sensors::read();
    for(int i = 0; i < 8; i++){
      Serial.print("sensores ");Serial.println(i);
      Serial.print("Umidade: ");Serial.println(sensors::get(Module_type::Moisture, i));
      Serial.print("Luminosidade: ");Serial.println(sensors::get(Module_type::Luminosity, i));
      Serial.print("Temperatura: ");Serial.println(sensors::get(Module_type::Temperature, i));
    }
  }
  if(keypad::getLastKey() == '-'){
    Routines::execute();
  }
   

}




