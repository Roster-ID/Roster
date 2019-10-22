#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include <dht.h>
dht DHT;
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(3, 5, 4); // Data=pin5, CLK=pin3, RST=pin4
#define pingTrig 6 
#define pingEcho 7
long duration; 
long cm;
#include <Servo.h>
Servo myservo;
char input;
int lod =10;
int buz =8;
int pakan;

void setup()   {                
  Serial.begin(9600);
  display.begin();display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,1);
  display.println("roster");
  display.setCursor(60,14);
  display.println("app");  
  display.display();
  delay(3000);
  display.invertDisplay(false);
  delay(1000); 
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false); 
  display.clearDisplay();
  pinMode(lod, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(pingTrig, OUTPUT);
  pinMode(pingEcho, INPUT);
  myservo.attach(9);  
  myservo.write(0); 
}

void loop() {
  digitalWrite(pingTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrig, LOW);
  duration = pulseIn(pingEcho, HIGH);
  cm = duration / 58;
  pakan = map(cm,0,20,100,0);
  myRTC.updateTime();DHT.read11(2);
  String data="/"+String(DHT.temperature)+"/"+String(DHT.humidity)+"/"+String(cm)+"/";
  Serial.println(data);delay(1000);
//waktu();suhu();lembab();sonik(); 
  if (Serial.available()) {
    input = Serial.read();//baca input
    if (input == 'a' || input == 'A') {buka();}
    if (input == 's' || input == 'S') {digitalWrite(lod,HIGH);}
    if (input == 'd' || input == 'D') {digitalWrite(lod,LOW);}
  
}}

void suhu() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40,1);
  display.println("Suhu");
  display.setCursor(40,17);
  display.print(DHT.temperature,0);  
  display.print(" c");
  display.display();
  delay(2000);
  display.invertDisplay(false);
  delay(1000); 
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false);
  display.clearDisplay();
  }

void lembab() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,1);
  display.println("Lembab");
  display.setCursor(40,17);
  display.print(DHT.humidity,0);  
  display.print(" %"); 
  display.display();
  delay(2000);
  display.invertDisplay(false);
  delay(1000); 
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false); 
  display.clearDisplay();
  }

void waktu() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5,1);
  display.print(myRTC.dayofmonth);
  display.print("-");
  display.print(myRTC.month);
  display.print("-");
  display.print(myRTC.year);
  display.setCursor(18,17);
  display.print(myRTC.hours);
  display.print(":");
  display.print(myRTC.minutes); 
  display.print(" WIB");
  display.display();
  delay(2000);
  display.invertDisplay(false);
  delay(1000); 
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false); 
  display.clearDisplay();
  }

void sonik() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(35,1);
  display.println("Pakan");
  display.setCursor(40,17);
  display.print(cm);  
  display.print(" %"); 
  display.display();
  delay(2000);
  display.invertDisplay(false);
  delay(1000); 
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false); 
  display.clearDisplay();
  }

void buka(){
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
delay(100);
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
delay(100);
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
myservo.write(90); 
delay(2000);
myservo.write(0); 
delay(500);
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
delay(100);
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
delay(100);
digitalWrite(buz, HIGH); 
delay(100);
digitalWrite(buz, LOW); 
delay(100);
}