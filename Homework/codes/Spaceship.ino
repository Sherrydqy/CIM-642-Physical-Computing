int buttonState = 0;
int prevButtonState = 0;
void setup() {
 // Serial.begin(9600);
 pinMode(2, INPUT);
 pinMode(3, OUTPUT);//green = 3
 pinMode(4, OUTPUT);//red1 = 4
 pinMode(5, OUTPUT);//red2 = 5

}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.print("Button is: ");
    Serial.println(digitalRead(2) );
    buttonState = digitalRead(2);


  if(prevButtonState != buttonState){
    Serial.print("Button is: ");
    Serial.println(buttonState);
    prevButtonState = buttonState;
  }
  if(buttonState == LOW){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(250);
  }
}
