// Ridhisha Dangol and Jacques Steyn
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin();

  if(! rtc.isrunning()){
    rtc.adjust(DateTime(2022,3,23,12,30,0));
    
  }
  rtc.adjust(DateTime(2022,3,23,12,30,0));
  
}

void loop() {
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
  delay(10000);
}
