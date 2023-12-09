#include "actuators.hpp"

void actuators::start(){
  // desliga todos os atuaodres
  for(int i = 0;i < 8; i++){
    PCFC::digitalWrite(PCFC::moisture[i],    LOW);
    PCFC::digitalWrite(PCFC::luminosity[i],  LOW);
    PCFC::digitalWrite(PCFC::temperature[i], LOW);
  }
}

void actuators::update(){
  for(int i = 0; i < 8; i++){     //para cada um ds 8 atuadores
    if(moisture::state[i]){       //se o sensor de umidade [i] estiver ativado
      if(millis() > moisture::ontime[i]){           //verifica se já se passou o tempo estipulado
        moisture::state[i] = false;                 
        PCFC::digitalWrite(PCFC::moisture[i], LOW);  //desliga o atuado
        Serial.print("desativando atuador de umidade: ");Serial.println(i);
      }
    }
    if(luminosity::state[i]){     //se o sensor de luminosidade [i] estiver ativado
      if(millis() > luminosity::ontime[i]){        //verifica se já se passou o tempo estipulado
        luminosity::state[i] = false;             
        PCFC::digitalWrite(PCFC::luminosity[i], LOW); //desliga o atuado
        Serial.print("desativando atuador de luminosidade: ");Serial.println(i);
      }
    }
    if(temperature::state[i]){    //se o sensor de temperatura [i] estiver ativado
      if(millis() > temperature::ontime[i]){       //verifica se já se passou o tempo estipulado
        temperature::state[i] = false;             
        PCFC::digitalWrite(PCFC::temperature[i], LOW);  //desliga o atuado
        Serial.print("desativando atuador de temperatura: ");Serial.println(i);
      }
    }
  }
}
void actuators::set(int type, char index, unsigned int onTime){
  switch(type){
    case Moisture:
      if(index >= 0 && index < 8){
        moisture::state[index] = true;
        moisture::ontime[index] = millis()+onTime;
        PCFC::digitalWrite(PCFC::moisture[index], HIGH);
        Serial.print("ativando atuador de umidade: ");Serial.print((int)index);Serial.print(" por tempo:");Serial.println(onTime);
      }
    break;
    case Luminosity:
      if(index >= 0 && index < 8){
        luminosity::state[index] = true;
        luminosity::ontime[index] = millis()+onTime;
        PCFC::digitalWrite(PCFC::luminosity[index], HIGH);
        Serial.print("ativando atuador de luminosidade: ");Serial.print((int)index);Serial.print(" por tempo:");Serial.println(onTime);
      }
    break;
    case Temperature:
      if(index >= 0 && index < 8){
        temperature::state[index] = true;
        temperature::ontime[index] = millis()+onTime;
        PCFC::digitalWrite(PCFC::temperature[index], HIGH);
        Serial.print("ativando atuador de temperatura: ");Serial.print((int)index);Serial.print(" por tempo:");Serial.println(onTime);
      }
    break;
  }
}
bool actuators::get(int type, char index){
  switch(type){           //se o tipo do atuador for:
    case Moisture:        //umidade
      return moisture::state[index]; //retorna o estado atual do atuador
    break;
    case Luminosity:      //luminosidade
      return luminosity::state[index]; //retorna o estado atual do atuador
    break;
    case Temperature:     //temperatura
      return temperature::state[index]; //retorna o estado atual do atuador
    break;
  }
}


