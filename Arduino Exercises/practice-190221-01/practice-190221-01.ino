#include <Servo.h>

int ledpin1 = 3;
int counter = 0;
long prevMillis = 0;
int interval = 10;
int direct = 1;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  pinMode (ledpin1, OUTPUT);
  myservo.attach (3);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite (ledpin1, counter);
  if(millis() - prevMillis > interval){
    prevMillis = millis();
    counter = counter + direct;
  }  
  if (counter >= 180){
    direct = -1;
  }
  else if (counter <= 0){
    direct = 1;
  }
  Serial.println(counter);
  
}
