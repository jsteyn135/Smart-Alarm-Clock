
// Ridhisha Dangol and Jacques Steyn
//#include <RTClib.h>

#include <LiquidCrystal.h>
#include "real_time.h"
#include <DHT.h>// look for the one in the library mananger by adafruit
#include <avr/interrupt.h>

#define Password_Length 5
#define DHTPIN 8
#define DHTTYPE DHT11

char Data[Password_Length]; 
byte data_count = 0, master_count = 0;
DHT dht(DHTPIN, DHTTYPE);
real_time rt;//real time clock

// each number here refers to the pins
LiquidCrystal lcd(12,11,5,4,3,2);// lcd

const int analogPin = A0; 
int analogValues[] = {59,108,162,183,587,597,609,614,631,640,649,653,668,674,682,686};

char keypadButton[] = "123A456B789C*0#D";           
int analogValuesSize;

byte Bell[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

void setup() {
  pinMode(7,INPUT_PULLUP);// for button to turn off alarm
  Serial.begin(9600);
  analogValuesSize = sizeof(analogValues)/sizeof(int); 
  
  lcd.begin(16,2);//width and height of the lcd
  rt.start(2022,4,16,1,45,1);// this sets the rtc time to 2022/11/23 12:30:09 -> year/month/day hours/minutes/seconds
  pinMode(10,OUTPUT);// for the buzzer
  
  dht.begin(); //for the temperature and humidity sensor
  delay(100);

  
}


void rotateRow(int row){

  lcd.createChar(0, Bell);
  delay(1000);
  lcd.setCursor(0,row); 
  lcd.print("                ");
  lcd.setCursor(0,row);
  lcd.print("HOLD # TO SET");
  lcd.setCursor(14,0);
  lcd.write(byte(0));
  delay(1000);
  lcd.setCursor(0,row); 
  lcd.print("                ");
  
} 
int test = 1;
//Data should hold the value of the user input alarm
void loop() {
  
  float humidity = dht.readHumidity();// use this to get the humidity and temp, they may sometimes be nan
  delay(300);
  float temperature = dht.readTemperature();
  
  //pin 7 is the button used to turn off the alarm sound and LED
  if(digitalRead(7) == LOW){// if it is LOW its being pushed
    rt.alarmSound = 0;// this will turn off the buzzer and the light
  }
  
   
  if(test==1){// just some testing code
    test=0;
    rt.setAlarmTime(0,1);// alarm and led will go off in 1 mins and 0 hours
  }
  
  if(rt.alarmSet ==1){// if the alarm is set, then check if its time to make the alarm go off
    rt.checkAlarm();  
  }

  if(rt.alarmSound == 1){//if it is alarm time, then make sound
    rt.soundAlarmOn();// this will also turn on the LED light because of the way it is wired
    
  }

  
  
  int value = analogRead(analogPin);
  char currentKeyHit = analogKeyPress(value);

  
  lcd.setCursor(0,0);
  lcd.print("ALARM:");
  delay(200);
     
  
  if (value<1000 && currentKeyHit ){
      Data[data_count] = currentKeyHit;
      lcd.setCursor(data_count+6,0); 
      lcd.print(Data[data_count]); 
      data_count++; 
    
   }
   
   
   /*
    if(hit some button or input to set the alarm){
      //determine hours/mins
      int hrs;
      int mins;
      rt.setAlarmTime(hrs,mins);
    }
    */
   

}
void defaultScreen(){
  lcd.setCursor(0,0);
  lcd.print(rt.rtc.now().year());
  lcd.setCursor(5,0);
  lcd.print(rt.rtc.now().month());
  lcd.setCursor(8,0);
  lcd.print(rt.rtc.now().day());
  lcd.setCursor(0,0);
  lcd.print("HOLD # TO SET");
  lcd.setCursor(14,0);
  lcd.write(byte(0));
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
  rotateRow(0);
}

void clearRow(int row){
  
  lcd.setCursor(0,0);
  lcd.print("               ");
  
}

int debounce(int last){
  
  delay(10);                                             
  int current = analogRead(analogPin);                   
  
  if(abs(current - last) > 5){                           
    delay(5);                       
    current = analogRead(analogPin);
     
  }
  
  return current;                                       
}

char analogKeyPress(int value){
  
  value = debounce(value);  
                              
  for (int i = 0; i < analogValuesSize; i++){           
    if (abs(value - analogValues[i]) < 5){
      //Serial.println(keypadButton[i]);
      return keypadButton[i];

      while(analogRead(analogPin) < 1000){delay(100);}  
    }
  }
}
