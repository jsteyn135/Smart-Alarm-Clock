#include <RTClib.h>
#include "pitches.h"
class real_time{
  public:
    RTC_DS1307 rtc;
    int alarmTime;// holds the time(in seconds) when the alarm will go off in the future
    int alarmSet=0;// 1 if the alarm is set, 0 if not set
    int alarmSound=0;
    void start(int _year, int _month, int _day, int _hour, int _minute, int _second);
    void serial_print();
    void setAlarmTime(int hrs,int mins);
    void soundAlarmOn();
    void soundAlarmOff();
    int checkAlarm();
    
};

//noTone(pin) turns off the buzzer
