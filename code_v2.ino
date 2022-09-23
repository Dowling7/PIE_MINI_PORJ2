#include <Servo.h>
#include <math.h>


Servo myservo1;  // create servo object to control a servo
Servo myservo2;
int buttonPin = A2;
int pos1=0 ;    // variable to store the servo position
int pos2=0 ;
int buttonState = 0;
int sensor =A0;
int state =1;

int measure(){
  int sum=0;
  int drop=0;
  int value;
 for(int i=0; i<3; i++){
  value=analogRead(sensor); 
  if(value>drop){
    drop=value;
  }
  sum+=value;
  
  delay(52.9);//5ms inverval in between 5+38.3+9.6
 }
 delay(15);
 int volt=(sum-drop)/7;
  return volt; //returns distance in voltage, need to do mapping on laptop
}

void scan(){
  //pos1 horizontal
  //pos2 verticle
  //half angle max is 70
  int ps1max=90;
  int ps2max=180;
  int initpos=45;
  int vt=0;
  String result;
  myservo1.write(initpos);
  myservo2.write(initpos);
  for (pos1 = initpos; pos1 <=ps1max; pos1 += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 5 degree
    for (pos2 = initpos; pos2 <= ps2max; pos2 += 10){
      myservo2.write(pos2);
      vt=measure();
     result="( "+String(pos1)+", "+String(pos2)+", "+String(vt)+" )";
      Serial.println(result); 
    }
    myservo1.write(pos1);// tell servo to go to position in variable 'pos1'
   }
  }
  



void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(sensor, INPUT);  //trigger pin
  myservo1.attach(3);  // attaches the servo on pin 0 to the servo object
  myservo2.attach(5);
  Serial.begin(9600);
}


void loop() {
  while(state==1){
     buttonState = digitalRead(buttonPin);
     buttonState = HIGH;//for testing
       if (buttonState == HIGH) {
          Serial.write("begin\n");
          scan();
          Serial.write("end\n");
          state=0;
       }
   }
}
