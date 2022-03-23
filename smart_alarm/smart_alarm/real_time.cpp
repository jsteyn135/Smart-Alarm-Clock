#include "real_time.h"

void real_time::start(int _year, int _month, int _day, int _hour, int _minute, int _second){
  rtc.begin();
  rtc.adjust(DateTime(_year,_month,_day,_hour,_minute,_second));
  
}//end real_time::start()


void real_time::serial_print(){
  DateTime current = rtc.now();
  Serial.print(current.year());
  Serial.print('/');
  Serial.print(current.month());
  Serial.print('/');
  Serial.print(current.day());
  Serial.print("\n");
  Serial.print(current.hour());
  Serial.print(':');
  Serial.print(current.minute());
  Serial.print(':');
  Serial.print(current.second());
  Serial.println();
  Serial.println();
  delay(5000);
}//end real_time::serial_print();
