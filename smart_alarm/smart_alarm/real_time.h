#include <RTClib.h>
//#include <Wire.h>
#include "pitches.h"
class real_time{
  public:
    RTC_DS1307 rtc; // TODO maybe change all to uint32_t
    uint32_t alarmTime;// holds the time(in seconds) when the alarm will go off in the future
    int alarmSet=0;// 1 if the alarm is set, 0 if not set
    int alarmSound=0;
    void start(uint16_t _year, uint8_t _month, uint8_t _day,uint8_t _hour, uint8_t _minute, uint8_t _second);
    void serial_print();
    void setAlarmTime(int hrs,int mins);
    void soundAlarmOn();
    void soundAlarmOff();
    int checkAlarm();
    void snoozeButton(int snoozeSeconds,int moreTime);
    
};

//noTone(pin) turns off the buzzer
