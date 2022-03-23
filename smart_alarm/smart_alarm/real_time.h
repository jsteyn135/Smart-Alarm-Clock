#include <RTClib.h>

class real_time{
  public:
    RTC_DS1307 rtc;
    void start(int _year, int _month, int _day, int _hour, int _minute, int _second);
    void serial_print();
};
