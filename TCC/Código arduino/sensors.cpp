#include "sensors.hpp"

float sensors::moistureLinearity(int m){
  if(m < 50)return 0;
  float x = (float)m/10.0;
  float y = x-180.0;
  float t = ((x*x) + (y*y*y))/9000000 + 0.45;
  return t*100;
}
float sensors::get(int type, int address){
  switch(type){
    case Moisture:
      if(address >= 0 && address < 8)
        return moisture::sensors[address];
      else return -1;
    break;
    case Luminosity:
      if(address >= 0 && address < 8)
        return luminosity::sensors[address];
      else return -1;
    break;
    case Temperature:
      if(address >= 0 && address < 8)
        return temperature::sensors[address];
      else return -1;
    break;
  }
}


#define _A 27
#define _B 26
#define _C 25

void sensors::setAddress(int i){
  digitalWrite(_A, !(i & 1));
  digitalWrite(_B, !(i & 2));
  digitalWrite(_C, !(i & 4));
}

void sensors::read(){
  for(int i = 0; i < 8; i++){
    setAddress(multiplex[i]);
    moisture::sensors[i] = 0;
    for(int j = 0; j < NUM_OF_MEASUREMENTS; j++){
      moisture::sensors[i] += analogRead(MOISTURE);
    }
    moisture::sensors[i] = moistureLinearity(moisture::sensors[i] / NUM_OF_MEASUREMENTS);
    float x = (float)analogRead(LUMINOSITY)/409.5;
    if(x < 4){
       luminosity::sensors[i] = 0;
    }else if(x < 7){
       luminosity::sensors[i] = 1;
    }else if(x < 9){
       luminosity::sensors[i] = 2;
    }else{
       luminosity::sensors[i] = 3;
    }
    float temp = temperature::dht22[i].getTemperature();
    temperature::sensors[i] = (temp > 0)? temp : 0;
  }
}


