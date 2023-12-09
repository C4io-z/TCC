#include "PCFC.hpp"

void PCFC::interrupt_call_back(){
  key_change = true;
}
void PCFC::begin(){
  for(int i = 0; i < 16; i++){
    e1.pinMode(i, OUTPUT);
    if(i < 4){
      e2.pinMode(i, INPUT);
    }else{
      e2.pinMode(i, OUTPUT);
    }
  }
  e2.digitalWrite(P4, LOW);
  e2.digitalWrite(P5, LOW);
  e2.digitalWrite(P6, LOW);
  e2.digitalWrite(P7, LOW);

  e1.begin();
  e2.begin();
}
void PCFC::digitalWrite(int index, bool state){
  if(index < 16)
    e1.digitalWrite(index, state);
  else
    e2.digitalWrite(index-16, state);
}
bool PCFC::digitalRead(int index){
  //d2 = e2.digitalReadAll();
  if(key_change){
    d2 = e2.digitalReadAll();
    key_change = false;
  }
    
  if(index < 4){
    switch(index){
      case 0: return d2.p0;
      case 1: return d2.p1;
      case 2: return d2.p2;
      case 3: return d2.p3;
    }
  }
  return false;
}