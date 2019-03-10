#include <TimeLib.h>
#include <TimeAlarms.h>

const int buttonMode = 7;   //button for time set mode and alarm set mode
const int buttonSet = 6;    //button to count, increment for alarm
const int alarmSet = 11;    //LED to light up when you are setting the alarm times, off when setting normal time
const int hr_LED = 10;      //LED lit when the hour is being set
const int mn_LED = 9;       //LED lit when the minute is being set
const int alarm = 5;        //Pin number for the piezzo speaker

int modeState = 0;          //state of the mode button
int setState = 0;           //state of the set button

//ints for time sets and 
  int newHr = 0;
  int newMin = 0;
  int newAlarmHr = 100;
  int newAlarmMin = 100;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  setTime(newHr,newMin,0,1,1,19);
  
  //set LED pins 
  pinMode(alarmSet, OUTPUT);
  pinMode(hr_LED, OUTPUT);
  pinMode(mn_LED, OUTPUT);
  
  //set the alarm pin
  pinMode(alarm, OUTPUT);

  //set buttons
  pinMode(buttonMode, INPUT);
  pinMode(buttonSet, INPUT);
  
}

void loop() {
  //check if the time set button was pressed
  modeState = digitalRead(buttonMode);
  if(modeState == HIGH) {
    //if button was pressed, a new time and alarm will be set
    createNewTimes();
    setTime(newHr,newMin,0,1,1,19);
  } 

  //displays the time to the serial
  clockDisplay();

  //check the alarm
  checkAlarm();

}

//method to set the new time
void createNewTimes(){
    delay(200);
    timeHour();
    Serial.print("new time hour = ");
    Serial.println(newHr);

    delay(200);
    timeMinute();
    Serial.print("new time minute = ");
    Serial.println(newMin);

    delay(200);
    alarmHour();
    Serial.print("new alarm hour = ");
    Serial.println(newAlarmHr);

    delay(200);
    alarmMinute();
    Serial.print("new alarm minute = ");
    Serial.println(newMin);

    delay(200);
}

//method for setting the time hour based on the button input
void timeHour(){
  digitalWrite(hr_LED,HIGH);
  int count = 0;
  modeState = digitalRead(buttonMode);
  while(modeState == LOW){
    setState = digitalRead(buttonSet);
    if(setState == HIGH){
      if(count == 23){
        count = 0;
      } else {
        count++;
      }
      Serial.print("set time hour to: ");
      Serial.println(count);
    }
    delay(200);
    modeState = digitalRead(buttonMode);
  }
  digitalWrite(hr_LED,LOW);
  newHr = count;  
}

//method for setting the time minute based on the button input
void timeMinute(){
  digitalWrite(mn_LED,HIGH);
  int count = 0;
  modeState = digitalRead(buttonMode);
  while(modeState == LOW){
    setState = digitalRead(buttonSet);
    if(setState == HIGH){
      if(count == 59){
        count = 0;
      } else {
        count++;
      }
      Serial.print("set time minute to: ");
      Serial.println(count);
    }
    delay(200);
    modeState = digitalRead(buttonMode);
  }
  digitalWrite(mn_LED,LOW);
  newMin = count;  
}

//method for setting the alarm hour based on the button input
void alarmHour(){
  digitalWrite(alarmSet,HIGH);
  digitalWrite(hr_LED,HIGH);
  int count = 0;
  modeState = digitalRead(buttonMode);
  while(modeState == LOW){
    setState = digitalRead(buttonSet);
    if(setState == HIGH){
      if(count == 23){
        count = 0;
      } else {
        count++;
      }
      Serial.print("set alarm hour to: ");
      Serial.println(count);
    }
    delay(200);
    modeState = digitalRead(buttonMode);
  }
  digitalWrite(hr_LED,LOW);
  digitalWrite(alarmSet,LOW);
  newAlarmHr = count;  
}

//method for setting the alarm minute based on the button input
void alarmMinute(){
  digitalWrite(alarmSet,HIGH);
  digitalWrite(mn_LED,HIGH);
  int count = 0;
  modeState = digitalRead(buttonMode);
  while(modeState == LOW){
    setState = digitalRead(buttonSet);
    if(setState == HIGH){
      if(count == 59){
        count = 0;
      } else {
        count++;
      }
      Serial.print("set alarm minute to: ");
      Serial.println(count);
    }
    delay(200);
    modeState = digitalRead(buttonMode);
  }
  digitalWrite(alarmSet,LOW);
  digitalWrite(mn_LED,LOW);
  newAlarmMin = count;  
}

void clockDisplay(){
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
}

//method to check if the alarm should go off, snd for when
//it gets turned off. output to piezzo speaker
void checkAlarm(){
  if(hour() == newAlarmHr){
    if(minute()== newAlarmMin){
      tone(alarm,1000);
      modeState = digitalRead(buttonMode);
      while(modeState == LOW){
        modeState = digitalRead(buttonMode);
      }
      noTone(alarm);
      newAlarmMin = 100;
      newAlarmHr = 100;
    }
  }
  delay(200);
}


