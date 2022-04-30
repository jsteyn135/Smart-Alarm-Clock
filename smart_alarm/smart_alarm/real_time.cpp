#include "real_time.h"

void real_time::start(uint16_t _year, uint8_t _month, uint8_t _day,uint8_t _hour, uint8_t _minute, uint8_t _second){
  //if(!rtc.begin()){
  //  exit(0);
  //}
  //rtc.begin();
  while(!rtc.begin());
  //rtc.adjust();
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
  //DateTime x= rtc.now();
  alarmTime = rtc.now().secondstime();// get the time in terms of seconds
  hrs = hrs*3600;//convert hours to seconds
  mins = mins*60;//convert mins to seconds
  //alarm time is the time(in seconds) in the future when the alarm will go off
  alarmTime = alarmTime + hrs + mins;
  alarmSet = 1;
  
  
}//end set alarm time


void real_time::soundAlarmOn(){// turn on the buzzer alarm
  tone(10,NOTE_E3,147);//pin 10, note_e3, 147 miliseconds
  alarmSet = 0;
}//end sound alarm on

void real_time::soundAlarmOff(){// probably dont need this one, but jsut keeping it incase
  noTone(10);// turn off the buzzer alarm
}//end sound alarm on

int real_time::checkAlarm(){
  //DateTime x= rtc.now();
  uint32_t current_time = rtc.now().secondstime();// get the current time in seconds 
  if(current_time >= alarmTime){
    alarmSet = 0;// the alarm is not set anymore
    alarmSound = 1;
    return 1;
  }
  return 0;
  
}//end check alarm



void real_time::snoozeButton(int snoozeSeconds,int moreTime){
    if(alarmSet == 0){
      ;//do nothing if the alarm is not set
    }
    else{
      if(moreTime ==1){// the alarm hasnt gone off yet but you want to add more time
        //DateTime x= rtc.now();
        uint32_t current_time = rtc.now().secondstime();// get the current time in seconds
        alarmTime = alarmTime + snoozeSeconds; //add snoozeseconds seconds to the alarm time  
      }
      else{
        if(moreTime == 0){// the alarm is going off, but you want more time
          //DateTime x= rtc.now();
          uint32_t current_time = rtc.now().secondstime();// get the current time in seconds
          alarmTime = current_time + snoozeSeconds; //add snoozeseconds seconds to the CURRENT time  
        }// end if
      }//end else
      
    }// end else
}// end snooze
