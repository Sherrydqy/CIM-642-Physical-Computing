int switchPin = 2;
int switchRead = 0;
int led1 = 3;
int led2 = 4;
int counter = 0;
boolean wasPressed = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switchRead = digitalRead(switchPin);
  Serial.print("switch: ");
  Serial.println(switchRead);
  
/*  if(switchRead == HIGH){
    if(wasPressed = false){
      wasPressed = true;
      digitalWrite(led1, HIGH);
      digitalWrite(led2,HIGH);
    }
    else{
      wasPressed = false;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
   }*/
   /*if(switchRead == HIGH){
    wasPressed = true;
   }
   if(wasPressed == true && switchRead == LOW){
    counter++;
    Serial.println(counter);
    wasPressed = false;
   }*/

}
