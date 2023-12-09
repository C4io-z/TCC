#include "Menu.hpp"

MENU::OBJ::OBJ(int(*_func)(), int _ref, String _text){
  if(_text.length() > 0){
    text = _text;
    has_text = true;
  }else{
    has_text = false;
  }
  func = _func;
  ref = _ref;
}
MENU::OBJ::OBJ(int(*_func)(int), int _argument,int _ref, String _text){
  if(_text.length() > 0){
    text = _text;
    has_text = true;
  }else{
    has_text = false;
  }
  has_argument = true;
  argument = _argument;
  func2 = _func;
  ref = _ref;
}

void MENU::MENU::add(OBJ *_obj, int ref){
  if(ref < 9 && ref > 0){
    obj[ref-1] = _obj;
    obj_exist[ref-1] = true;
  }  
}
int MENU::MENU::update(){
  //if already selected, obj[selected].func(), if it retun -1, selec = false
  if(selec){
    if(obj[selected]->has_argument){
      if(obj[selected]->func2(obj[selected]->argument) == -1){
        selec = false;
        upd = true;
      }
    }else{
      if(obj[selected]->func() == -1){
        selec = false;
        upd = true;
      }
    }
    return 1;
  }
  char buff = keypad::getLastKey();
  //if some number was pressed, selec = true, selected = the number
  if(buff > '0' && buff < '9'){
    if(obj_exist[buff-'1']){
      selec = true;
      selected = buff-'1';
    }
  }
  //if "#" was pressed, stage++, if it is bigeer tan 3, stage = 0
  if(buff == '#'){
    stage++;
    upd = true;
    if(stage > 7) stage = 0;
    while(!obj_exist[stage] || !obj_exist[stage+1] || !obj[stage]->text.length() || !obj[stage+1]->text.length()){
      stage++;
      if(stage > 7){
        stage = 0;
        break;
      }
    }
  }
  //draw the options on the screen
  if(upd){
    upd = false;
    lcd.clear();
    if(obj_exist[stage])
      lcd.print(obj[stage]->text);
    lcd.setCursor(0,1);
    if(obj_exist[stage+1])
      lcd.print(obj[stage+1]->text);
  }
  if(buff == '*'){
    upd = true;
    return -1;
  }
  return 0;
}

