// Ridhisha Dangol and Jacques Steyn
//#include <RTClib.h>
#include <LiquidCrystal.h>
#include "real_time.h"


real_time rt;//real time clock

// each number here refers to the pins

LiquidCrystal lcd(12,11,5,4,3,2);// lcd

void setup() {
  
  
  lcd.begin(16,2);//width and height of the lcd
  rt.start(2022,11,23,12,30,9);// this sets the rtc time to 2022/11/23 12:30:09 -> year/month/day hours/minutes/seconds
  
}

void loop() {
  lcd.setCursor(0,0);// col,row
  lcd.print(rt.rtc.now().year());
  lcd.setCursor(5,0);
  lcd.print(rt.rtc.now().month());
  lcd.setCursor(8,0);
  lcd.print(rt.rtc.now().day());

  lcd.setCursor(0,1);
  lcd.print(rt.rtc.now().hour());
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(rt.rtc.now().minute());
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(rt.rtc.now().second());

  delay(2000);
}
