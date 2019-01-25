void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); // Parameter1: a pin Parameter2: how do you want to set this pin, input or output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH); // Parameter1: a pin; Parameter2: how do you want to with this pin?
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
}
