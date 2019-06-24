#include <Wire.h>
#include <RTClib.h>
#include<LiquidCrystal.h>
#include <Servo.h>


int pin_button2 = 2; //주기 스위치
int pin_button3 = 3; //급여량 스위치
int pin_button4 = 4; //모터 제어 스위치
int pin_button5 = 5; //스피커 on/off 스위치
int state_button;
LiquidCrystal lcd(44,45,46,47,48,49); //lcd출력
int period = 0; //주기
int amount = 0; //급여량
int go = 0; //모터제어
int sound = 0; //스피커 소리
bool stateButton2; //주기
bool stateButton3;  //급여량
bool stateButton4;  //모터제어
bool stateButton5;  //스피커 스위치
int state_previous2 = 0;
int state_previous3 = 0;
int state_previous4 = 0;
int state_previous5 = 0;
unsigned long interval; //가변저항
Servo myServo; //모터 제어
int angle=0;  //모터 이동 범위 변수
int servoPin = 11; //모터
int later;  // //delay 변수
int mot;  //사료 양 변수
int k; //고주파 변수
unsigned long time_previous, time_current;
RTC_DS1307 rtc;
unsigned long time1;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
/*
DateTime now = rtc.now();
if(1<=now.month() || now.month()<=9){
     String months = "0"+String(now.month());}
    else
      String months = String(now.month());
*/
void setup() {
  pinMode(A0, INPUT); //가변저항
  Serial.begin(9600); //아두이노 출력
  lcd.begin(16,2);  //lcd 출력
  pinMode(pin_button2, INPUT);  //2번 스위치
  pinMode(pin_button3, INPUT);  //3번 스위치
  pinMode(pin_button4, INPUT);  //4번 스위치
  pinMode(pin_button5, INPUT);
  myServo.attach(servoPin); //모터
  time_previous = millis();
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }}

void Speaker(int sound, unsigned long interval ){
    switch(sound){
    case 0 :{
    }
    case 1 :{
        lcd.setCursor(0,0);
        lcd.print("Speaker on / off");
        if(interval <= 50){
        k = 0;
        lcd.setCursor(0,1);
        lcd.print("Speaker off");
        }
        else{
        k = 1;
        lcd.setCursor(0,1);
        lcd.print("Speaker on ");
    }    }}}

void Time(){
      DateTime now = rtc.now();
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    lcd.setCursor(0,0);
    lcd.print(" "+String(now.year())+"/"+String(now.month())+"/"+String(now.day())+"/"+String(daysOfTheWeek[now.dayOfTheWeek()])+"  ");
    lcd.setCursor(0,1);
    lcd.print(" "+String(now.hour())+"  : "+String(now.minute())+"  : "+String(now.second())+" ");
    delay(1000);
}

void Motor(int go, int mot, int later, unsigned long time_current, int k){ //모터제어(go 스위치,사료양, 대기시간, 스피커 on(1)/off(0))
  Serial.println("go read");
  switch(go){
    case 0:    {
      lcd.setCursor(0,0);
      lcd.print("switch is off");
      break;
    }
    case 1:    {
      if(mot == 100){ //사료양 == 100g
        angle = 60; //각도 60도
       /*
        int i=1;
         if( i != 0){
          Serial.println("ifmoon dongjak");
          for(i = 177; i > 0 ; i--){
          lcd.setCursor(0,0);
          Serial.println("i value : "+String(i));
          lcd.print(" Period: "+String(i)+"   ");}}
         else{
           i = 177;
          } */
        lcd.setCursor(0,1);
         lcd.print("  food : 100 g  ");

        int delayvalue = 3000;  //later * 60 * 1000
        static int seconds= delayvalue/1000;
        lcd.setCursor(0,0);
        lcd.print(" seconds : "+String(seconds)+"   ");
       if(time_current - time_previous >= 1000){

            seconds--; // 초 감소
            //if(k == 1)
            //soundenalbe();
            Serial.println(" seconds : "+String(seconds)+"   ");
            lcd.print(" seconds : "+String(seconds)+"   ");

            time_previous = time_current;
          if(seconds==0){
            lcd.setCursor(0,0);
            lcd.print("    feeding!    ");
            seconds=delayvalue/1000;
        for(int i = 0; i < angle; i++){
          myServo.write(i);
          delay(5);
      }for(int i = angle ; i > 0; i--){
        myServo.write(i);
        delay(5);
      }
      } } }

    else if(mot == 150){ //사료양 == 150g
      angle = 90; //각도 90도
          lcd.setCursor(0,1);
            lcd.print("  food : 150 g  ");

        int delayvalue = 5000;  //later * 60 * 1000
        static int seconds= delayvalue/1000;
        lcd.setCursor(0,0);
        lcd.print(" seconds : "+String(seconds)+"   ");
       if(time_current - time_previous >= 1000){

            seconds--; // 초 감소
            Serial.println(" seconds : "+String(seconds)+"   ");
            lcd.print(" seconds : "+String(seconds)+"   ");

            time_previous = time_current;
          if(seconds==0){
            lcd.setCursor(0,0);
            lcd.print("    feeding!    ");
            seconds=delayvalue/1000;
        for(int i = 0; i < angle; i++){
          myServo.write(i);
          delay(5);
      }for(int i = angle ; i > 0; i--){
        myServo.write(i);
        delay(5);
      }} }}

    else if(mot == 200){ //사료양 == 200g
      angle = 120; //각도 120도
      lcd.setCursor(0,1);
      lcd.print("  food : 200 g  ");

        int delayvalue = 7000;  //later * 60 * 1000
        static int seconds= delayvalue/1000;
        lcd.setCursor(0,0);
        lcd.print(" seconds : "+String(seconds)+"   ");
       if(time_current - time_previous >= 1000){

            seconds--; // 초 감소
            Serial.println(" seconds : "+String(seconds)+"   ");
            lcd.print(" seconds : "+String(seconds)+"   ");

            time_previous = time_current;
          if(seconds==0){
            lcd.setCursor(0,0);
            lcd.print("    feeding!    ");
            seconds=delayvalue/1000;
        for(int i = 0; i < angle; i++){
          myServo.write(i);
          delay(5);
      }for(int i = angle ; i > 0; i--){
        myServo.write(i);
        delay(5);
      }}}}

    else if(mot == 250){ //사료양 == 250g
      angle = 160;  //각도 160도
      lcd.setCursor(0,1);
      lcd.print("  food : 250 g  ");
        int delayvalue = 10000;  //later * 60 * 1000
        static int seconds= delayvalue/1000;
        lcd.setCursor(0,0);
        lcd.print(" seconds : "+String(seconds)+"   ");
       if(time_current - time_previous >= 1000){

            seconds--; // 초 감소
            Serial.println(" seconds : "+String(seconds)+"   ");
            lcd.print(" seconds : "+String(seconds)+"   ");

            time_previous = time_current;
          if(seconds==0){
            lcd.setCursor(0,0);
            lcd.print("    feeding!    ");
            seconds=delayvalue/1000;
        for(int i = 0; i < angle; i++){
          myServo.write(i);
          delay(5);
      }for(int i = angle ; i > 0; i--){
        myServo.write(i);
        delay(5);
      }}}

    else{
      angle = 0;    }break;}
  }
}}

void P_LCD(int period, unsigned long interval){ //주기 설정(주기 스위치 on/off, 가변저항)
    switch(period){
    case 0:{
      lcd.setCursor(0,0);
      lcd.print("switch is off");
      break;
    }
    case 1:{
      lcd.setCursor(0,0);
      lcd.print("   How  often   ");
      if(interval >= 0 and interval < 25) //가변저항
       { lcd.setCursor(0,1);  //lcd출력
        lcd.print("   15  minute   ");
        later = 15;} //delay 변수 설정
      else if(interval >= 25 and interval < 50) //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   25  minute   ");
        later = 25;} //delay 변수 설정
      else if(interval >= 50 and interval < 75) //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   35  minute   ");
        later = 35;} //delay 변수 설정
      else if(interval >= 75 and interval <99)  //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   45  minute   ");
        later = 45;} //delay 변수 설정
      else
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   e r r o r !  ");}
      break;
    }}
}

void A_LCD(int amount, unsigned long interval){ //사료량 설정(스위치 on/off , 가변저항)
    switch(amount){
    case 0:{
      lcd.setCursor(0,0);
      lcd.print("switch is off");
      break;
    }
    case 1:{
      lcd.setCursor(0,0);
      lcd.print(" Amount of food ");
      if(interval >= 0 and interval < 25)  //가변저항
       { lcd.setCursor(0,1);  //lcd출력
        lcd.print("     100  g     ");
        mot = 100;}
      else if(interval >= 25 and interval < 50)  //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     150  g     ");
        mot = 150;}
      else if(interval >= 50 and interval < 75)  //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     200  g     ");
        mot = 200;}
      else if(interval >= 75 and interval <99)  //가변저항
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     250  g     ");
        mot = 250;}
      else
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   e r r o r !  ");}
      break;
    }}
}

void loop() {
  time_current = millis();
  stateButton3 = digitalRead(pin_button3);
  stateButton2 = digitalRead(pin_button2);
  stateButton4 = digitalRead(pin_button4);
  stateButton5 = digitalRead(pin_button5);
if(stateButton2 == 1){ //주기 스위치
  if(state_previous2 == 0){
  period = period + 1;
  state_previous2 = 1;
  }}else{
    state_previous2 = 0;}

if(stateButton3 == 1){  //사료량 스위치
  if(state_previous3 == 0){
  amount = amount + 1;
  state_previous3 = 1;
  }}else{
    state_previous3 = 0;}

if(stateButton4 == 1){ //모터 스위치
  if(state_previous4 == 0){
  go = go + 1;
  state_previous4 = 1;
  }}else{
    state_previous4 = 0;}

if(stateButton5 == 1){ //스피커 스위치
  if(state_previous5 == 0){
  sound = sound + 1;
  state_previous5 = 1;
  }}else{
    state_previous5 = 0;}

   sound = sound%2; //on/off
  go = go%2;  //on/off
  amount = amount%2;  //on/off
  period = period%2;  //on/off
   Serial.print("go = "+String(go));
   Serial.print("amount = "+String(amount));
   Serial.println("period = "+String(period));

   if(period == 1 and amount == 0 and go == 0 and sound == 0){
      P_LCD(period, interval); // later(주기 변수) 값을 들고온다
      }
   else if(amount ==1 and period == 0 and go == 0 and sound == 0){
      A_LCD(amount, interval); // mot(사료량 변수) 값을 들고온다
      }
   else if(period == 0 and amount == 0 and go == 1 and sound == 0){
    Motor(go, mot, later,time_current,k);//모터스위치, 사료량 변수, 주기 변수
   }
   else if(period == 0 and amount == 0 and go == 0 and sound == 0){
    Time();
   }
   else if(period == 0 and amount == 0 and go == 0 and sound == 1){
    Speaker(sound, interval);
   }
   else{lcd.clear();}

   Serial.print("later = "+String(later));
   Serial.println("mot = "+String(mot));
int adc = analogRead(A0); //가변저항 읽기
interval = map(adc,0,1023,0,100); //범위를 0 ~ 100
  }
