#include "Display.hpp"

using namespace display;

MENU::MENU principal;
  MENU::MENU visualizar;
    MENU::MENU visualizar_op;
  MENU::MENU configuracao;
    MENU::MENU conectividade;
    MENU::MENU selec_subset;
      MENU::MENU selec_subset_op;
  MENU::MENU utilitarios;

//////////////----------------------//////////////////

// principal/
int configuracoes(){   //configuralçoes
  return configuracao.update();
}int visualizacao(){   //visualizar
  return visualizar.update();
}int util(){           //utilitarios
  return utilitarios.update();
}int ajuda(){          //ajuda
  lcd.clear();
  lcd.print("in progress...");
  if(keypad::getLastKey() == '*')return -1;
  return 1;
}int mostra_ID(){      //mostra ID 
  uint64_t chipId;
  String chipIdString;
  chipId = ESP.getEfuseMac();
  chipIdString = String(chipId, HEX);
  lcd.clear();
  lcd.print(chipIdString);
  delay(10000);
  return -1;
}
// configurações/
int config_subset(){  // subsetores
  return selec_subset.update();
}int config_conect(){ // conectividade
  return conectividade.update();
}
// configurações/subsetores
int config_selection;
int config_subset_x(int subset){  // x
  config_selection = subset;
  return selec_subset_op.update();
}
// configurações/subsetores/x
int config_subset_x_addat(){  // add.at
  static int atuador = -1;
  if(atuador == -1){
    atuador = 0;
    lcd.clear();
    lcd.print("atuador: ");
    lcd.print(atuador);
  }
  char buff = keypad::getLastKey();
  if(buff >= '0' && buff <= '9'){
    atuador*=10;
    atuador+= buff-'0';
    if(atuador > 24)atuador = 0; 
    lcd.clear();
    lcd.print("atuador: ");
    lcd.print(atuador);
  }
  if(buff == '#' && atuador != 0){
    lcd.clear();
    lcd.print("add. atuador ");
    lcd.print(atuador);
    lcd.setCursor(0,1);
    lcd.print("subsetor ");
    lcd.print(config_selection);
    Memory::add(config_selection-1, (atuador-1)/8 + 3, (atuador-1)%8);
    Internet::requestSetRoutine(config_selection-1);
    delay(3000);
    atuador = -1;
    return -1;
  }
  if(buff == '*'){
    return -1;
  }
  return 0;
}int config_subset_x_addse(){ // add.se
  static int sensor = -1;
  if(sensor == -1){
    sensor = 0;
    lcd.clear();
    lcd.print("sensor: ");
    lcd.print(sensor);
  }
  char buff = keypad::getLastKey();
  if(buff >= '0' && buff <= '9'){
    sensor*=10;
    sensor+= buff-'0';
    if(sensor > 24)sensor = 0; 
    lcd.clear();
    lcd.print("sensor: ");
    lcd.print(sensor);
  }
  if(buff == '#' && sensor != 0){
    lcd.clear();
    lcd.print("add. sensor ");
    lcd.print(sensor);
    lcd.setCursor(0,1);
    lcd.print("subsetor ");
    lcd.print(config_selection);
    Memory::add(config_selection-1, (sensor-1)/8 , (sensor-1)%8);
    Internet::requestSetRoutine(config_selection-1);
    delay(3000);
    sensor = -1;
    return -1;
  }
  if(buff == '*'){
    return -1;
  }
  return 0;
}int config_subset_x_delat(){ // del.at
  static int atuador = -1;
  if(atuador == -1){
    atuador = 0;
    lcd.clear();
    lcd.print("atuador: ");
    lcd.print(atuador);
  }
  char buff = keypad::getLastKey();
  if(buff >= '0' && buff <= '9'){
    atuador*=10;
    atuador+= buff-'0';
    if(atuador > 24)atuador = 0; 
    lcd.clear();
    lcd.print("atuador: ");
    lcd.print(atuador);
  }
  if(buff == '#' && atuador != 0){
    lcd.clear();
    lcd.print("remov. atuador ");
    lcd.print(atuador);
    lcd.setCursor(0,1);
    lcd.print("subsetor ");
    lcd.print(config_selection);
    Memory::remove(config_selection-1, (atuador-1)/8 + 3, (atuador-1)%8);
    Internet::requestSetRoutine(config_selection-1);
    delay(3000);
    atuador = -1;
    return -1;
  }
  if(buff == '*'){
    return -1;
  }
  return 0;
}int config_subset_x_delse(){ // del.se
  static int sensor = -1;
  if(sensor == -1){
    sensor = 0;
    lcd.clear();
    lcd.print("sensor: ");
    lcd.print(sensor);
  }
  char buff = keypad::getLastKey();
  if(buff >= '0' && buff <= '9'){
    sensor*=10;
    sensor+= buff-'0';
    if(sensor > 24)sensor = 0; 
    lcd.clear();
    lcd.print("sensor: ");
    lcd.print(sensor);
  }
  if(buff == '#' && sensor != 0){
    lcd.clear();
    lcd.print("remov. sensor ");
    lcd.print(sensor);
    lcd.setCursor(0,1);
    lcd.print("subsetor ");
    lcd.print(config_selection);
    Memory::remove(config_selection-1, (sensor-1)/8, (sensor-1)%8);
    Internet::requestSetRoutine(config_selection-1);
    delay(3000);
    sensor = -1;
    return -1;
  }
  if(buff == '*'){
    return -1;
  }
  return 0;
}
// configurações/conectividade
int config_restart_AP(){  // restart.AP
  lcd.clear();
  lcd.print("reinicinado AP");
  Internet::restartAP();
  while(Internet::isConnected() == -1){
    digitalWrite(LED_WiFi, HIGH);
    delay(500);
    digitalWrite(LED_WiFi, LOW);
    delay(500);
  }
  digitalWrite(LED_WiFi, Internet::isConnected());
  return -1;
}
// visualizar/subsetor
int visu_selection;
int visu_subset_x(int subset){
  visu_selection = subset;
  return visualizar_op.update();
}

// visualizar/subsetor/x - not ready
int visu_subset_x_sensores(){  // sensores
  lcd.clear();
  Routine *rt = Memory::getPointer();
  static int i = 0;
  static int m = 0;
  if(rt->Routine[visu_selection-1].Module[m].index[i] == '1'){
    if(m == 0){
      lcd.print("Umidade ");
      lcd.print(i+1);
    }if(m == 1){
      lcd.print("Luminosidade ");
      lcd.print(i+1);
    }if(m == 2){
      lcd.print("Temperatura ");
      lcd.print(i+1);
    }
    delay(1000);
  }
  if( i == 7 && m == 2){
    i = 0;
    m = 0;
    return -1;
  }
  i++;
  if(i > 7){
    i = 0;
    m++;
  }
  return 1;
}int visu_subset_x_atuadores(){ //atuadores
  lcd.clear();
  Routine *rt = Memory::getPointer();
  static int i = 0;
  static int m = 0;
  if(rt->Routine[visu_selection-1].Module[m+3].index[i] == '1'){
    if(m == 0){
      lcd.print("Umidade ");
      lcd.print(i+1);
    }if(m == 1){
      lcd.print("Luminosidade ");
      lcd.print(i+1);
    }if(m == 2){
      lcd.print("Temperatura ");
      lcd.print(i+1);
    }
    delay(1000);
  }
  if( i == 7 && m == 5){
    i = 0;
    m = 0;
    return -1;
  }
  i++;
  if(i > 7){
    i = 0;
    m++;
  }
  return 1;
}int visu_subset_x_rotinas(){   // ratinas
  lcd.clear();
  Routine *rt = Memory::getPointer();
  static int m = 0;
  if(m == 0){
    lcd.print("Umidade ");
  }if(m == 1){
    lcd.print("Luminosidade ");
  }if(m == 2){
    lcd.print("Temperatura ");
  }
  delay(1000);
  lcd.clear();
  lcd.print("Valor, OP, Tempo");
  lcd.setCursor(0,1);
  lcd.print((byte)rt->Routine[visu_selection-1].Config[m].Value);
  lcd.print("      ");
  lcd.print((char)rt->Routine[visu_selection-1].Config[m].OP);
  lcd.print("   ");
  lcd.print((byte)rt->Routine[visu_selection-1].Config[m].Time);
  delay(1000);
  if(m == 2){
    m = 0;
    return -1;
  }
  m++;
  return 1;
}

// utilitarios/
int util_calc(){      // calculadora
  static int etapa = 0, n1 = 0, n2 = 0, op = 0;
  char buff = keypad::getLastKey();
  switch(etapa){
    case 0:{
      lcd.clear();
      lcd.print("n1: ");
      etapa++;
    }break;
    case 1:{
      if(buff >= '0' && buff <= '9'){
        n1*=10;
        n1+= buff-'0';
        lcd.clear();
        lcd.print("n1: ");
        lcd.print(n1);
      }
      if(buff == '*'){
        n1/=10;
        lcd.clear();
        lcd.print("n1: ");
        lcd.print(n1);
      }
      if(buff == '#')etapa++;
    }break;
    case 2:{
      lcd.clear();
      lcd.print("+ - / *");
      lcd.setCursor(0,1);
      lcd.print("?");
      etapa++;
    }break;
    case 3:{
      if(buff == '+'){
        op = '+';
        etapa++;
        lcd.clear();
        lcd.print("n2:");
      }if(buff == '-'){
        op = '-';
        etapa++;
        lcd.clear();
        lcd.print("n2:");
      }if(buff == 'X'){
        op = '*';
        etapa++;
        lcd.clear();
        lcd.print("n2:");
      }if(buff == '/'){
        op = '/';
        etapa++;
        lcd.clear();
        lcd.print("n2:");
      }
    }break;
    case 4:{
      if(buff >= '0' && buff <= '9'){
        n2*=10;
        n2+= buff-'0';
        lcd.clear();
        lcd.print("n2: ");
        lcd.print(n2);
      }
      if(buff == '*'){
        n2/=10;
        lcd.clear();
        lcd.print("n2: ");
        lcd.print(n2);
      }
      if(buff == '#')etapa++;
    }break;
    case 5:{
      lcd.clear();
      lcd.print("n1 ");
      lcd.print(op);
      lcd.print(" n2 = ");
      lcd.setCursor(0, 1);
      lcd.print((op == '+')? n1+n2 :(op == '-')? n1-n2 :(op == '*')? n1*n2 : n1/n2);
      etapa++;
    }break;
    case 6:{
      if(buff == '*')etapa = 0;
      n1 = 0;
      n2 = 0;
      op = 0;
    }
  }
  if(buff == '*' && etapa == 0)return -1;
  return 0;
}int util_entret(){   // joguinho - not ready
  return -1;
}

//////////------------------------////////////
MENU::OBJ obj_config(configuracoes, 1, "1-Configuracao");
MENU::OBJ obj_visu  (visualizacao,  2, "2-visualizar");
MENU::OBJ obj_util  (util,          3, "");
MENU::OBJ obj_ajuda (ajuda,         4, "");
MENU::OBJ obj_mostraID(mostra_ID,         9, "");

//////////------------------------////////////
MENU::OBJ obj_config_subset(config_subset, 1, "1-sub-setores");
MENU::OBJ obj_config_conect(config_conect, 2, "2-conectividade");
//////////------------------------////////////
MENU::OBJ obj_config_subset_1(config_subset_x,1, 1, "selecione um sub");
MENU::OBJ obj_config_subset_2(config_subset_x,2, 2, "setor [1 a 8]");
MENU::OBJ obj_config_subset_3(config_subset_x,3, 3, "");
MENU::OBJ obj_config_subset_4(config_subset_x,4, 4, "");
MENU::OBJ obj_config_subset_5(config_subset_x,5, 5, "");
MENU::OBJ obj_config_subset_6(config_subset_x,6, 6, "");
MENU::OBJ obj_config_subset_7(config_subset_x,7, 7, "");
MENU::OBJ obj_config_subset_8(config_subset_x,8, 8, "");
//////////------------------------////////////
MENU::OBJ obj_config_subset_x_1(config_subset_x_addat, 1, "1-add. atuador");
MENU::OBJ obj_config_subset_x_2(config_subset_x_addse, 2, "2-add. sensor");
MENU::OBJ obj_config_subset_x_3(config_subset_x_delat, 3, "");
MENU::OBJ obj_config_subset_x_4(config_subset_x_delse, 4, "");
//////////------------------------////////////
MENU::OBJ obj_config_restartAP(config_restart_AP, 1, "1-reiniciar AP");
//////////------------------------////////////
MENU::OBJ obj_visu_subset_1(visu_subset_x,1, 1, "Selecione um sub");
MENU::OBJ obj_visu_subset_2(visu_subset_x,2, 2, "setor [1 a 8]");
MENU::OBJ obj_visu_subset_3(visu_subset_x,3, 3, "");
MENU::OBJ obj_visu_subset_4(visu_subset_x,4, 4, "");
MENU::OBJ obj_visu_subset_5(visu_subset_x,5, 5, "");
MENU::OBJ obj_visu_subset_6(visu_subset_x,6, 6, "");
MENU::OBJ obj_visu_subset_7(visu_subset_x,7, 7, "");
MENU::OBJ obj_visu_subset_8(visu_subset_x,8, 8, "");
//////////------------------------////////////
MENU::OBJ obj_visu_subset_x_1(visu_subset_x_sensores,  1, "1-sensores");
MENU::OBJ obj_visu_subset_x_2(visu_subset_x_atuadores, 2, "2-atuadores");
MENU::OBJ obj_visu_subset_x_3(visu_subset_x_rotinas,   3, "3-rotinas");
//////////------------------------////////////
MENU::OBJ obj_util_1(util_calc,   1, "1-calculadora kkkk");
MENU::OBJ obj_util_2(util_entret, 1, "2-joguinho kkkk");
//////////------------------------////////////

void display::begin(){
  lcd.begin();
  utilitarios.add(&obj_util_1, 1);
  utilitarios.add(&obj_util_2, 2);

  principal.add(&obj_config, 1);
  principal.add(&obj_visu, 2);
  principal.add(&obj_util, 3);
  principal.add(&obj_ajuda, 4);
  principal.add(&obj_mostraID, 8);
  

  configuracao.add(&obj_config_subset, 1);
  configuracao.add(&obj_config_conect, 2);

  selec_subset.add(&obj_config_subset_1, 1);
  selec_subset.add(&obj_config_subset_2, 2);
  selec_subset.add(&obj_config_subset_3, 3);
  selec_subset.add(&obj_config_subset_4, 4);
  selec_subset.add(&obj_config_subset_5, 5);
  selec_subset.add(&obj_config_subset_6, 6);
  selec_subset.add(&obj_config_subset_7, 7);
  selec_subset.add(&obj_config_subset_8, 8);

  selec_subset_op.add(&obj_config_subset_x_1, 1);
  selec_subset_op.add(&obj_config_subset_x_2, 2);
  selec_subset_op.add(&obj_config_subset_x_3, 3);
  selec_subset_op.add(&obj_config_subset_x_4, 4);

  conectividade.add(&obj_config_restartAP, 1);

  visualizar.add(&obj_visu_subset_1, 1);
  visualizar.add(&obj_visu_subset_2, 2);
  visualizar.add(&obj_visu_subset_3, 3);
  visualizar.add(&obj_visu_subset_4, 4);
  visualizar.add(&obj_visu_subset_5, 5);
  visualizar.add(&obj_visu_subset_6, 6);
  visualizar.add(&obj_visu_subset_7, 7);
  visualizar.add(&obj_visu_subset_8, 8);

  visualizar_op.add(&obj_visu_subset_x_1, 1);
  visualizar_op.add(&obj_visu_subset_x_2, 2);
  visualizar_op.add(&obj_visu_subset_x_3, 3);
}

void display::update(){
  principal.update();
}
