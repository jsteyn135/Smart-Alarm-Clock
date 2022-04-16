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



void real_time::setAlarmTime(int hrs,int mins){
  DateTime x= rtc.now();
  alarmTime = x.secondstime();// get the time in terms of seconds
  hrs = hrs*3600;//convert hours to seconds
  mins = mins*60;//convert mins to seconds
  //alarm time is the time(in seconds) in the future when the alarm will go off
  alarmTime = alarmTime + hrs + mins;
  alarmSet = 1;
  
  
}//end set alarm time


void real_time::soundAlarmOn(){// turn on the buzzer alarm
  tone(10,NOTE_E3,147);//pin 10, note_e3, 147 miliseconds
}//end sound alarm on

void real_time::soundAlarmOff(){// probably dont need this one, but jsut keeping it incase
  noTone(10);// turn off the buzzer alarm
}//end sound alarm on

int real_time::checkAlarm(){
  DateTime x= rtc.now();
  int current_time = x.secondstime();// get the current time in seconds 
  if(current_time >= alarmTime){
    alarmSet = 0;// the alarm is not set anymore
    alarmSound = 1;
    return 1;
  }
  return 0;
  
}//end check alarm
