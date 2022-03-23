// Ridhisha Dangol and Jacques Steyn
//#include <RTClib.h>
#include "real_time.h"


real_time rt;
void setup() {
  Serial.begin(9600);
  
  rt.start(2022,3,23,12,30,0);
  //rtc.adjust(DateTime(2022,3,23,12,30,0));
  
}

void loop() {
  rt.serial_print();
}
