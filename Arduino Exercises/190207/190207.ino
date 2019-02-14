int pot1 = A0;
int ledPin1 = 10;
int ledPin2 = 11;
int potRead = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // we are telling arduino to send back infomation, like read a sensor, read a switch and send
  // back to your pc. 9600 is the speed limit of the communication between cmoputer and arduino
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(ledPin1,HIGH);
  //digitalWrite(ledPin2,HIGH);
  //analogWrite(ledPin1, 127);
  //analogWrite(ledPin2, 255);
  //potRead = analogRead(pot1)/4; //This will constantly read my potentiometer .  1023/4 约等于255 
  potRead = analogRead(pot1);
  int mapped = map(potRead, 0,200,0,255);
  Serial.println(mapped);
  analogWrite(ledPin1, mapped);
  
//  if (potRead < 512) {
//    analogWrite(ledPin1, 64);
//    analogWrite(ledPin2, 0);
//  }
//  else {
//    analogWrite(ledPin2, 255);
//    analogWrite(ledPin1, 0);
//  }

}
