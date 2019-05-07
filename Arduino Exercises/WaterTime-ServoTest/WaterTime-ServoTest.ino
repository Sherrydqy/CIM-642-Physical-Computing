#include <Servo.h>
int servoPin = 9;
float prevTime = 0;
float pastTime = 0;
int interval = 5000;
int count = 0;
Servo servoManRising;

void setup() {
  // put your setup code here, to run once:
  servoManRising.attach(servoPin);
  //servoManRising.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  pastTime = millis()-prevTime;
  if(pastTime>interval){
    count++;
    prevTime = interval*count;
    servoManRising.write(0);
   // delay(15);
  }
  //prevTime = millis();
  else{
  servoManRising.write(pastTime/interval*90);
  }
  //delay(15);
  
 
}
