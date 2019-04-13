const int sensorGreen = A0;
const int sensorRed = A1;
const int sensorBlue = A2;
const int pinGreen = 9;
const int pinRed = 11;
const int pinBlue = 10;
int inputRed,inputBlue,inputGreen,outputRed,outputBlue,outputGreen;

void setup() {
 // Serial.begin(9600);
 Serial.begin(9600);
 for(int pinNumber = 9; pinNumber<12;pinNumber++){
  pinMode(pinNumber, OUTPUT);
 }

}

void loop() {
  inputRed = analogRead(sensorRed);
  delay(10);
  inputBlue = analogRead(sensorBlue);
  delay(10);
  inputGreen = analogRead(sensorGreen);
  delay(10);
  outputRed = inputRed/4;
  outputBlue = inputBlue/4;
  outputGreen = inputGreen/4;
  analogWrite(pinRed, outputRed);
  analogWrite(pinGreen, outputGreen);
  analogWrite(pinBlue, outputBlue);
  Serial.print("Red input: ");
  Serial.print(inputRed);
  Serial.print("Blue input: ");
  Serial.print(inputBlue);
  Serial.print("Green input: ");
  Serial.println(inputGreen);
  Serial.print("Red output: ");
  Serial.print(outputRed);
  Serial.print("Blue output: ");
  Serial.print(outputBlue);
  Serial.print("Green output: ");
  Serial.println(outputGreen);

}
