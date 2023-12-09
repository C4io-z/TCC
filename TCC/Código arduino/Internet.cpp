#include "Internet.hpp"

void Internet::start(){
  xTaskCreate(&loop, "Internet Loop", 10000, NULL, 1, NULL);
  chipId = ESP.getEfuseMac();
  chipIdString = String(chipId, HEX);
  for(int t = 0; t < 5; t++){
    request2[t] = -1;
  }
}
void Internet::restartAP(){
  CONNECTED = -1;
  wifimanager.disconnect();
  wifimanager.resetSettings();
  APshouldRestart = true;
}
void Internet::requestUpdate(int time_space, int address, String values){
  request[time_space] = values;
  request2[time_space] = address;
  _request = true;
}
void Internet::requestSetRoutine(){
  _routine_set = true;
}
void Internet::requestSetRoutine(int i){
  _routine_set = true;
  _routine_index = i;
}
void Internet::requestGetRoutine(){
  _routine_get = true;
}
void Internet::loop(void* aaa){
  while(true){
    delay(100);
    if(APshouldRestart){
      APshouldRestart = false;
      if(!wifimanager.autoConnect("AutoConnectAP")){
        CONNECTED = false;
        digitalWrite(LED_WiFi, LOW);
      }else{
        CONNECTED = true;
        digitalWrite(LED_WiFi, HIGH);
        Time::start();
      }//*/
    }
    if(_request){
      _request = false;
      for(int t = 0; t < 5; t++){
        if(request2[t] != -1){
          updateDB(t, request2[t], request[t]);
          request2[t] = -1;
        }
      }
    }
    if(_routine_set){
      _routine_set = false;
      if(_routine_index == -1)
        for(int s = 0; s < 8; s++)
          updateRoutine(s, Memory::get(s));
      else{
        updateRoutine(_routine_index, Memory::get(_routine_index));
        _routine_index = -1;
      }
         
    }
    if(_routine_get){
      _routine_get = false;
      for(int i = 0; i < 8; i++)
        Memory::set(i, loadRoutine(i));
    }
  }
}
void Internet::updateDB(int time_space, int address, String values){
  const String Modules_S[6] = {"S_U", "S_L", "S_T","A_U", "A_L", "A_T"};
  const String Time_space_S[5] = {"D", "S", "M", "A", "T"};
  if(CONNECTED){
    HTTPClient http;

    String serverPath = serverName + "ID=" + chipIdString + 
                                     "&Values=" + values + 
                                     "&Address=" + String(address) + 
                                     "&Time_space=" + Time_space_S[time_space];                            
    Serial.println(serverPath);
    int retries = 5;
    while(retries > 0){
      retries--;
      http.begin(serverPath.c_str());
        
      int httpResponseCode = http.GET();
        
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        return;
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
      }
  } 
}
void Internet::updateRoutine(int sub_sector, String data){
  //www.digitaq.com.br/Caio_V.php?ID=1&Sub_sector=2&Module=000000000000000000000000000000000000000000000000
  if(CONNECTED){
    HTTPClient http;

    String serverPath = serverName + "ID=" + chipIdString + 
                                     "&Sub_sector=" + (sub_sector+1) + 
                                     "&Module=" + data;     

    Serial.println(serverPath);
    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } 
}
String Internet::loadRoutine(int Sub_sector){
  if(CONNECTED){
    HTTPClient http;
    String serverPath = serverName + "ID=" + chipIdString + 
                                     "&Sub_sector=" + (Sub_sector+1);
    Serial.println(serverPath);
    http.begin(serverPath.c_str());
      
    int httpResponseCode = http.GET();
      
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      return payload;
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } 
}
int Internet::isConnected(){
  return CONNECTED;
}








