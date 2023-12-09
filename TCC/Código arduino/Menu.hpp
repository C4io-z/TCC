#ifndef MENU_HPP
#define MENU_HPP

#include "Arduino.h"
#include "keypad.hpp"
#include "LCDIC2.h"

namespace MENU{
  static LCDIC2 lcd(0x27, 16, 2);
  class OBJ{
    public:
    int(*func)();
    int(*func2)(int);
    int ref;
    int argument = 0;
    String text;
    bool has_text, has_argument = false;

    OBJ(int(*_func)(), int _ref, String _text = "");
    OBJ(int(*_func)(int), int _argument,int _ref, String _text = "");
  };
  class MENU{
    public:
      OBJ *obj[8];
      bool obj_exist[8] = {0,0,0,0,0,0,0,0};
      bool upd = true; 
      bool selec = false;
      int selected = 0;
      int stage = 0;

      void add(OBJ *_obj, int ref);
      int update();
  };
}  

#endif