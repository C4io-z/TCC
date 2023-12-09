#include "Routines.hpp"
/*
struct Routines{
  struct{
    struct{
      char index[8];
    }Module[6];
    struct{
      char Value, OP, Time;
    }Config[3];
  }Routine[8];
};
//*/
void Routines::execute(){
  //Internet::requestGetRoutine();
  Routine *rt = Memory::getPointer();
  for(int r = 0; r < 8; r++){
    Serial.print("Rotina: ");Serial.println(r);
    float moisture = 0;
    float luminosity = 0;
    float temperature = 0;
    for(int i = 0; i < 8; i++){
      /*Serial.print("index: ");Serial.println(i);
      Serial.print("umidade: ");Serial.println((int)rt->Routine[r].Module[Modules::Moisture_sensor].index[i]);
      Serial.print("luminosidade: ");Serial.println((int)rt->Routine[r].Module[Modules::Luminosity_sensor].index[i]);
      Serial.print("temperatura: ");Serial.println((int)rt->Routine[r].Module[Modules::Temperature_sensor].index[i]);
      //*/
      if(rt->Routine[r].Module[Modules::Moisture_sensor].index[i] == '1'){
        if(!moisture)moisture=sensors::get(Module_type::Moisture, i);
        moisture = (moisture + sensors::get(Module_type::Moisture, i)) * 0.5;
        //Serial.println(i);
      }
      if(rt->Routine[r].Module[Modules::Luminosity_sensor].index[i] == '1'){
        if(!luminosity)luminosity=sensors::get(Module_type::Luminosity, i);
        luminosity = (Luminosity + sensors::get(Module_type::Luminosity, i)) * 0.5;
        //Serial.println(i + 8);
      }
      if(rt->Routine[r].Module[Modules::Temperature_sensor].index[i] == '1'){
        if(!temperature)temperature=sensors::get(Module_type::Temperature, i);
        temperature = (Temperature + sensors::get(Module_type::Temperature, i)) * 0.5;
        //Serial.println(i + 16);
      }
    }
    Serial.print("umidade: "); Serial.println(moisture);
    Serial.print("luminosidade: "); Serial.println(luminosity);
    Serial.print("temperatura: "); Serial.println(temperature);

    Serial.print("OP: "); Serial.println((char)rt->Routine[r].Config[Module_type::Moisture].OP);
    Serial.print("VALUE: "); Serial.println((int)rt->Routine[r].Config[Module_type::Moisture].Value);
    if(moisture < rt->Routine[r].Config[Module_type::Moisture].Value){
      for(int i = 0; i < 8; i++)
        if(rt->Routine[r].Module[Modules::Moisture_actuator].index[i] == '1')
          actuators::set(Module_type::Moisture, i, rt->Routine[r].Config[Module_type::Moisture].Time*10000);
    }

    Serial.print("OP: "); Serial.println((char)rt->Routine[r].Config[Module_type::Temperature].OP);
    Serial.print("VALUE: "); Serial.println((int)rt->Routine[r].Config[Module_type::Temperature].Value);
    if(rt->Routine[r].Config[Module_type::Temperature].OP == '<'){
      if(temperature < rt->Routine[r].Config[Module_type::Temperature].Value){
        for(int i = 0; i < 8; i++)
          if(rt->Routine[r].Module[Modules::Temperature_actuator].index[i] == '1')
            actuators::set(Module_type::Temperature, i, rt->Routine[r].Config[Module_type::Temperature].Time*10000);
      }
    }else{
      if(temperature > rt->Routine[r].Config[Module_type::Temperature].Value){
        for(int i = 0; i < 8; i++){
          if(rt->Routine[r].Module[Modules::Temperature_actuator].index[i] == '1')
            actuators::set(Module_type::Temperature, i, rt->Routine[r].Config[Module_type::Temperature].Time*10000);
        }
      }
    }

    Serial.print("OP: "); Serial.println((char)rt->Routine[r].Config[Module_type::Luminosity].OP);
    Serial.print("VALUE: "); Serial.println((int)rt->Routine[r].Config[Module_type::Luminosity].Value);
    if(rt->Routine[r].Config[Module_type::Luminosity].OP == '<'){
      if(luminosity < rt->Routine[r].Config[Module_type::Luminosity].Value){
        for(int i = 0; i < 8; i++)
          if(rt->Routine[r].Module[Modules::Luminosity_actuator].index[i] == '1')
            actuators::set(Module_type::Luminosity, i, rt->Routine[r].Config[Module_type::Luminosity].Time*10000);
      }
    }else{
      if(luminosity > rt->Routine[r].Config[Module_type::Luminosity].Value){
        for(int i = 0; i < 8; i++)
          if(rt->Routine[r].Module[Modules::Luminosity_actuator].index[i] == '1')
            actuators::set(Module_type::Luminosity, i, rt->Routine[r].Config[Module_type::Luminosity].Time*10000);
      }
    }
  }
}


