#include "keypad.hpp"



void keypad::tick(){
  key = -1;
  for(int i = 0; i < 4; i++){
    PCFC::digitalWrite(20+i, LOW);
    delay(10);
    for(int j = 0; j < 4; j++){
      if(PCFC::digitalRead(j) == LOW){
        key = keypad[j][i];
      }
    }
    PCFC::digitalWrite(20+i, HIGH);
  }
  if(lastKey != key){
    lastKey = key;
  }else{
    key = -1;
  }
}
char keypad::getLastKey(){
  return key;
}

