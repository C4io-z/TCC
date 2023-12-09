#include "memory.hpp"


void Memory::start(){
  if(!EEPROM.begin(sizeof(Routine))){
    Serial.println("erro ao iniciar EEPROM!");
  }
  pointer = (char*)EEPROM.getDataPtr();
}
void Memory::submit(){
  EEPROM.commit();
}
Routine *Memory::getPointer(){
  return (Routine*)EEPROM.getDataPtr();
}
void Memory::add(int sub_sector, int module, int index){
  int final_address = (sizeof(Routine::Routine[0])*sub_sector) + 
                      (sizeof(Routine::Routine[0].Module[0])*module) +
                      (sizeof(Routine::Routine[0].Module[0].index[0])*index);
                      
  EEPROM.writeChar(final_address, '1');
}
void Memory::remove(int sub_sector, int module, int index){
  int final_address = (sizeof(Routine::Routine[0])*sub_sector) + 
                      (sizeof(Routine::Routine[0].Module[0])*module) +
                      (sizeof(Routine::Routine[0].Module[0].index[0])*index);

  EEPROM.writeChar(final_address, '0');
}
void Memory::setRoutine(int sub_sector, int module, char value, char config, char time){
  int value_address = (sizeof(Routine::Routine[0])*sub_sector) + 
                      (sizeof(Routine::Routine[0].Module[0])*6) +
                      (sizeof(Routine::Routine[0].Config[0])*module);
  int config_address = value_address+1;
  EEPROM.writeChar(value_address, value);
  EEPROM.writeChar(config_address, config);
  EEPROM.writeChar(config_address+1, time);
}
void Memory::set(int sub_sector, String data){
  for(int i = 0; i < 48; i++){
    (data[i] != '0')? add(sub_sector, (Modules)(i/8), i%8) : remove(sub_sector, (Modules)(i/8), i%8);
  }
  setRoutine(sub_sector, Module_type::Moisture, data[48], data[49], data[50]);
  setRoutine(sub_sector, Module_type::Luminosity, data[51], data[52], data[53]);
  setRoutine(sub_sector, Module_type::Temperature, data[54], data[55], data[56]);
}

String Memory::get(int sub_sector){
  String out = "";
    for(int i = 0; i < 56; i++){
      out += pointer[(sub_sector*57 + i)]; 
    }
  return out;
}



