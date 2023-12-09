#include "Time.hpp"

void Time::start(){
  if(Internet::isConnected()){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  }
}
void Time::update(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))return;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  static int last_min = 0;
  static int last_day = 0;
  int Minutes = timeinfo.tm_hour*60 + timeinfo.tm_min;
  int Days = timeinfo.tm_yday;

  int day_index = Minutes;
  int week_index = timeinfo.tm_wday*205 + Minutes/7;
  int month_index = timeinfo.tm_mday*45 + Minutes/32;
  int year_index = timeinfo.tm_yday*3 + Minutes/480;
  int all_index = timeinfo.tm_yday/3;

  if(last_min != Minutes){
    last_min = Minutes;

      Monitoring::dailyUpdate(day_index);

    if(!(Minutes%7))
      Monitoring::weeklyUpdate(week_index);

    if(!(Minutes%32))
      Monitoring::monthlyUpdate(month_index);

    if(!(Minutes%480))
      Monitoring::yearlyUpdate(year_index);

    if(!(Minutes%10))
      Routines::execute();

    if(!((Minutes)%2))
      Internet::requestGetRoutine();
  }
  if(last_day != Days){
    last_day = Days;
    if(!(Days%3));
      Monitoring::allUpdate(all_index);
  }

}
void Time::getTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
void Time::getDate(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


