int switchPin = 2;
int switchRead = 0;
int led1 = 3;
int led2 = 4;
int counter = 0;
int interval = 2000;
int trigger = -1;
boolean wasPressed = false;
long prevMillis = 0;
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
  if (counter == 1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  } else if (counter == 2) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else if (counter == 3) {
    if (millis() - prebMillise > interval) {
      prevMillis = millis();
      trigger = trigger * (-1);
    }
  }
