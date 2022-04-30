
// Ridhisha Dangol and Jacques Steyn
//#include <RTClib.h>

#include <LiquidCrystal.h>
#include "real_time.h"
#include <DHT.h>// look for the one in the library mananger by adafruit
#include <avr/interrupt.h>


#define input_Length 5
#define DHTPIN 8
#define DHTTYPE DHT11

char Data[input_Length]; 
byte data_count = 0, master_count = 0;
DHT dht(DHTPIN, DHTTYPE);
real_time rt;//real time clock

// each number here refers to the pins
LiquidCrystal lcd(12,11,5,4,3,2);// lcd

const int analogPin = A0; 
//int analogValues[] = {59,108,162,183,587,597,609,614,631,640,649,653,668,674,682,686};// Ridhisha analog values,
int analogValues[] = {8,74,132,184,222,263,301,335,361,389,416,440,458,478,498,516}; // Jacques analog values, pls dont delete just comment out
char keypadButton[] = "123A456B789C*0#D";           
int analogValuesSize;
int alarmButton = 1;

//lets use the bell icon to indicate the alarm has been set
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

int hourKey1, hourKey2, minKey1, minKey2;

void setup() {
  pinMode(7,INPUT_PULLUP);// for button to turn off alarm
  pinMode(9,INPUT_PULLUP);// for button to snooze
  pinMode(A1,OUTPUT);// for led light that turns on when alarm is set
  Serial.begin(9600);
  analogValuesSize = sizeof(analogValues)/sizeof(int); 
  
  lcd.begin(16,2);//width and height of the lcd
  //rt.start(2022,5,2,5,30,0);// this sets the rtc time to 2022/11/23 12:30:09 -> year/month/day hours/minutes/seconds
  rt.start(2022,5,2,5,45,1);
  pinMode(10,OUTPUT);// for the buzzer
  
  dht.begin(); //for the temperature and humidity sensor
  delay(100);
  digitalWrite(A1,LOW);

  
}


int test = 1;
//Data should hold the value of the user input alarm
void loop() {
  
  float humidity = dht.readHumidity();// use this to get the humidity and temp, they may sometimes be nan
  delay(300);
  float temperature = dht.readTemperature();
  
  //pin 7 is the button used to turn off the alarm sound and LED


  if(digitalRead(9)== LOW){// if the snooze button is pressed
    if(rt.alarmSet == 0 && rt.alarmSound == 1){
      rt.alarmSet = 1;
      rt.alarmSound = 0;
      rt.snoozeButton(15,0);// snooze for 15 second
      digitalWrite(A1,HIGH);
    }
    else{
      if(rt.alarmSet == 1 && rt.alarmSound == 0){
        rt.snoozeButton(15,1);// snooze for 15 second
        digitalWrite(A1,HIGH);
      }
    }
    
  }// end if snooze
  if(digitalRead(7) == LOW){// if it is LOW its being pushed
    rt.alarmSound = 0;// this will turn off the buzzer and the light
    if(rt.alarmSet == 1){
      
    }
    else{
      digitalWrite(A1,LOW);  
    }
    
  }


  if(rt.alarmSet ==1){// if the alarm is set, then check if its time to make the alarm go off
    rt.checkAlarm();  
  }

  if(rt.alarmSound == 1){//if it is alarm time, then make sound
    rt.soundAlarmOn();// this will also turn on the LED light because of the way it is wired
    
  }
  
  int value = analogRead(analogPin);
  char currentKeyHit = analogKeyPress(value);

  // first greeting page
  if(test==1){
    lcd.setCursor(0,0);
    lcd.print("ALARM:");
    lcd.setCursor(0, 1);
  }
  //screen after the alarm has been set
  if(test==0){
   delay(100);
   lcd.clear();
   defaultScreen();
  }
  
  delay(200);
     
  
  if (value<1000 && currentKeyHit ){
    // when the we reach third array elemnt skip the :
    if(data_count == 2){
        lcd.setCursor(data_count+7,0);
        Data[data_count] = ':';
        data_count ++;
    }
    //else prints the array on lcd and convets the key hit to integer
    if(data_count > 2 || data_count < 2 || data_count < input_Length){
      
      Data[data_count] = currentKeyHit;
      lcd.setCursor(8,0);
      lcd.print(":");
      lcd.setCursor(data_count+6,0); 
      lcd.print(Data[data_count]);
      
      switch (data_count) {
        case 0:
          hourKey1 =  currentKeyHit - '0';
          
        case 1:
          hourKey2 = currentKeyHit - '0';

        case 3:
          minKey1 = currentKeyHit - '0';

        case 4:
          minKey2 = currentKeyHit - '0';
      }
      data_count+=1;
     }
     
     if (data_count == 5){
       lcd.setCursor(0,1); 
       lcd.print("*.Ok");
     }

   }
    if(currentKeyHit == '*'){
        setAlarm();
        
    }
   
}// end of loop
//set the actual alarm
void setAlarm(){
 int hrs = (hourKey1*10)+ hourKey2;// you cannot set the time above 9hrs 99 mins or else the alarm goes off instantly(bug)
 int mins = ( minKey1*10)+ minKey2;// dont waste time trying to figure out why, I already spent hours looking
 if(test==1){
    test=0;
    rt.setAlarmTime(hrs,mins);
    digitalWrite(A1,HIGH);// turns on the led indicating the alarm is set
 }
 
 
}// end set alarm
//show the default screen with date once alam is set with bell to indicate that the alarm has been set
void defaultScreen(){
  lcd.clear();
  lcd.createChar(0, Bell);
  lcd.setCursor(0,0);
  lcd.print(rt.rtc.now().year());
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(rt.rtc.now().month());
  lcd.setCursor(8,0);
  lcd.print(":");
  lcd.setCursor(9,0);
  lcd.print(rt.rtc.now().day());
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
  
}

void clearRow(int row){
  
  lcd.setCursor(0,row);
  lcd.print("                   ");
  
}

//analog pin valaue read to get current 
int debounce(int last){
  
  delay(10);                                             
  int current = analogRead(analogPin);                   
  
  if(abs(current - last) > 5){                           
    delay(5);                       
    current = analogRead(analogPin);
     
  }
  
  return current;                                       
}

//converting to char to conver the current value to the equivalent key
char analogKeyPress(int value){
  
  value = debounce(value);  
                              
  for (int i = 0; i < analogValuesSize; i++){           
    if (abs(value - analogValues[i]) < 5){
     
      return keypadButton[i];

      while(analogRead(analogPin) < 1000){delay(100);}  
    }
  }
}
