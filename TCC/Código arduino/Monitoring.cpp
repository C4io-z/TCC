#include "Monitoring.hpp"

void Monitoring::dailyUpdate(int address){
  sensors::read();
  String out;
  for(int i = 0; i < 8; i++){
    for(int m = 0; m < 3; m++){
      out += String(sensors::get(m, i)) + ",";
      week[m][i]    =   (sensors::get(m, i) +  week[m  ][i]) * 0.5;
      week[m+3][i]  = (actuators::get(m, i) +  week[m+3][i]) * 0.5;
      month[m][i]   =   (sensors::get(m, i) + month[m  ][i]) * 0.5;
      month[m+3][i] = (actuators::get(m, i) + month[m+3][i]) * 0.5;
      year[m][i]    =   (sensors::get(m, i) +  year[m  ][i]) * 0.5;
      year[m+3][i]  = (actuators::get(m, i) +  year[m+3][i]) * 0.5;
      all[m][i]     =   (sensors::get(m, i) +   all[m  ][i]) * 0.5;
      all[m+3][i]   = (actuators::get(m, i) +   all[m+3][i]) * 0.5;
    }
    for(int m = 0; m < 3; m++){
      out += String(actuators::get(m, i)) + ",";
    }
    
  }
  Internet::requestUpdate(Time_space::day, address, out);
}
void Monitoring::weeklyUpdate(int address){
  String out;
  for(int i = 0; i < 8; i++){
    for(int m = 0; m < 3; m++){
      out += String(week[m][i]) + ",";
      week[m  ][i] = 0;
    }
    for(int m = 3; m < 6; m++){
      out += String(week[m][i]) + ",";
      week[m][i] = 0;
    }
  }
  Internet::requestUpdate(Time_space::week, address, out);
}
void Monitoring::monthlyUpdate(int address){
  String out;
  for(int i = 0; i < 8; i++){
    for(int m = 0; m < 3; m++){
      out += String(month[m][i]) + ",";
      month[m  ][i] = 0;
    }
    for(int m = 3; m < 6; m++){
      out += String(month[m][i]) + ",";
      month[m][i] = 0;
    }
  }
  Internet::requestUpdate(Time_space::month, address, out);
}
void Monitoring::yearlyUpdate(int address){
  String out;
  for(int i = 0; i < 8; i++){
    for(int m = 0; m < 3; m++){
      out += String(year[m][i]) + ",";
      year[m][i] = 0;
    }
    for(int m = 3; m < 6; m++){
      out += String(year[m][i]) + ",";
      year[m][i] = 0;
    }
  }
  Internet::requestUpdate(Time_space::year, address, out);
}
void Monitoring::allUpdate(int address){
  String out;
  for(int i = 0; i < 8; i++){
    for(int m = 0; m < 3; m++){
      out += String(all[m][i]) + ",";
      all[m  ][i] = 0;
    }
    for(int m = 3; m < 6; m++){
      out += String(all[m][i]) + ",";
      all[m][i] = 0;
    }
  }
  Internet::requestUpdate(Time_space::all, address, out);
}

