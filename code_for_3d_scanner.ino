#include <Servo.h>
#include <math.h>

Servo m;

int t = 7;
int e=  6;
int n;

void setup() {
  pinMode(t, OUTPUT);  //trigger pin
  pinMode(e, INPUT);  //echo pin
  pinMode(8,OUTPUT); //pin to control DC motor, goes to mosfet
  m.attach(10);     //servo motor pin
  
  Serial.begin(9600);

}

int distance(){
  
  long duration, cm;
  
  digitalWrite(t, LOW);
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(5);
  digitalWrite(t, LOW);
  
  duration = pulseIn(e, HIGH);

  cm = duration/ 29 / 2;
  
  return cm; //returns distance in centimeters
}

void revolve(){ // rotates motor 18 degree
 digitalWrite(8,HIGH);
 delay(120);
 digitalWrite(8,LOW);

}

void scan(){
  int i;
  for(i=70;i<=120;i+=1){
    m.write(i);
    
    delay(25);      
    
    float d= distance();

    if (d<30){
      
      Serial.print(n);
      Serial.print(",");
   
      Serial.print(d*cos((i-90)*3.14/180));
      Serial.print(",");
   
      Serial.print(d*sin((i-90)*3.14/180));
      Serial.println();  
      
      }
    
  

  }
  
  for(i=120;i>=70;i-=1){
    m.write(i);
    delay(20);
    }

}

void loop() {

  int i;

  Serial.println("Start");
  
  for(i=0;i<20;i+=1){ // scan 20 times, every revolution is 18° i.e. 20x18° = 360°
    n=i;
    
    scan();       //scan top to bottom
    revolve();   // revolve the object
    delay(50);  //repeat    
    
  }
 
 Serial.println("End");
 delay(50);
 
}