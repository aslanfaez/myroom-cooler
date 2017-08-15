#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

byte btnOn = 3;
byte btnOff = 4;

byte pump = 13;
byte fast = 11;
byte med = 10;
byte slow = 12;

float hum = 40;
float temp = 28;

int state = 0;
int motor = 0;

void setup() {
  // put your setup code here, to run once:
    dht.begin();
    pinMode(pump,OUTPUT);
    pinMode(slow,OUTPUT);
    pinMode(fast,OUTPUT);
    pinMode(med,OUTPUT);
    
    pinMode(btnOn,INPUT);
    pinMode(btnOff,INPUT);
    
    state = 1;
    digitalWrite(pump,0);
    digitalWrite(slow,1);
    digitalWrite(med,1);
    digitalWrite(fast,0);
    motor = 1;
    delay(10000);
//  hum = 45;
    temp = 28;
}

void loop() {
//  hum = dht.readHumidity();
    temp = dht.readTemperature();
    if(digitalRead(btnOn) == 1)
    {
      state = 1;
      digitalWrite(pump,0);
      digitalWrite(slow,1);
      digitalWrite(med,1);
      digitalWrite(fast,0);
      motor = 1;
      delay(10000);
    }
    if(digitalRead(btnOff) == 1)
    {
      state = 0;
    }
    if(state == 1)
    {    
      if(motor==0){
        digitalWrite(pump,1);
      }
      else{
        digitalWrite(pump,0);
      }
      if(temp>26.5){
          digitalWrite(slow,1);
          digitalWrite(med,1);
          digitalWrite(fast,0);
          motor = 1;}
      
      if(temp>25.8&&temp<26.2){
          digitalWrite(slow,1);
          digitalWrite(med,0);
          digitalWrite(fast,1);
          motor = 1;}
      
      if(temp<25.5&&temp>25){
          digitalWrite(slow,0);
          digitalWrite(med,1);
          digitalWrite(fast,1);
          motor = 1;}
          
       if(temp<24.3&&temp>24){
          digitalWrite(slow,1);
          digitalWrite(med,1);
          digitalWrite(fast,1);
          motor = 0;}   
    }
    else{
      digitalWrite(pump,1);
      digitalWrite(slow,1);
      digitalWrite(med,1);
      digitalWrite(fast,1);
      motor = 0;}
}
