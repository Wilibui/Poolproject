#include "Wire.h"
#include "RTClib.h"
#include "LiquidCrystal_I2C.h"
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,20,4);
DateTime now;

//pins conected to 5V 4 Channel Relay Module for Arduino 
int Lamp_1 = 4;
int Lamp_2 = 3;
int Lamp_3 = 2;

//Set power value for on and off
int on = LOW;
int off = HIGH;
int daySinceStart = 0;

void setup() {
  setupRTC();

  lcd.init();
  lcd.init();

  pinMode(Lamp_1, OUTPUT);
  pinMode(Lamp_2, OUTPUT);
  pinMode(Lamp_3, OUTPUT);

  digitalWrite(Lamp_1, off);
  digitalWrite(Lamp_2, off);
  digitalWrite(Lamp_3, off);
}

void loop() {
  //Set time var to real time using RTC
  DateTime now = rtc.now();
  
  Check_Lamp_1();
  Check_Lamp_2();
  Check_Lamp_3();
  ShowLCD();

  //delay with 1 sec so that Arduino would not fail
  delay(1000);  
}

//Setup Real Time Clock (RTC)
void setupRTC() {
  if (! rtc.begin()) {
    while (1);
  }

  //If connected to pc
  if (Serial) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

//Check if lamp should be on or off
void Check_Lamp_1() {
  if (now.hour() % 2 == 0) {
    digitalWrite(Lamp_1, on);
  } else {
    digitalWrite(Lamp_1, off);
  }
}
void Check_Lamp_2() {
  if (now.hour()  >= 6 && now.hour() <= 18) {
    digitalWrite(Lamp_2, on);
  } else {
    digitalWrite(Lamp_2, off);
  }
}
void Check_Lamp_3() {
  digitalWrite(Lamp_3, on);
}

//Show information on LCD (Display) for Arduino
//This is not crusial, it's just very usefull 
void ShowLCD(){
  lcd.backlight();
  
  lcd.setCursor(1,0);
  lcd.print(now.day());
  lcd.setCursor(3,0);
  lcd.print("/");
  lcd.setCursor(4,0);
  lcd.print(now.month());
  lcd.setCursor(6,0);
  lcd.print("/");
  lcd.setCursor(7,0);
  lcd.print(now.year());
 
  lcd.setCursor(1,1);
  lcd.print(now.hour());
  lcd.setCursor(3,1);
  lcd.print(":");
  lcd.setCursor(4,1);
  lcd.print(now.minute());
  lcd.setCursor(6,1);
  lcd.print(":");
  lcd.setCursor(7,1);
  lcd.println(now.second());
  lcd.setCursor(9,1);
  lcd.println("         ");

  lcd.setCursor(0,3);
  lcd.println("day :");
  lcd.setCursor(5,3);
  lcd.println(daySinceStart);

  if(now.hour() == 0 && now.minute() == 0 && now.second() == 0){
    daySinceStart++;
  }
}
