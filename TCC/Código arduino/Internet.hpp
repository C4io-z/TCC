#ifndef INTERNET_HPP
#define INTERNET_HPP
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiManager.h> 
#include "defines.hpp"
#include "esp_system.h"
#include "Arduino.h"
#include "Time.hpp"
#include "Memory.hpp"


namespace Internet{
  //ESP32 ID
  static uint64_t chipId;
  static String chipIdString;
  

  //internet DB request
  static String serverName = "https://www.digitaq.com.br/Caio_V.php?";
  
  //WiFi config
  static char ssid[25];
  static char password[25];
  static WiFiManager wifimanager;
  static int CONNECTED = 0;
  static bool APshouldRestart = true;
  
  //variables
  static String request[5];  
  static int request2[5];
  static bool _request = false;
  static bool _routine_set = false;
  static int _routine_index = -1;
  static bool _routine_get = true;
  

  //functions
  void start();
  void restartAP();
  void requestUpdate(int time_space, int address, String values);
  void requestSetRoutine();
  void requestSetRoutine(int i);
  void requestGetRoutine();
  void loop(void *aaa);
  void updateDB(int time_space, int address, String value);
  void updateRoutine(int sub_sector, String data);
  String loadRoutine(int Sub_sector);
  int isConnected();

}

#endif