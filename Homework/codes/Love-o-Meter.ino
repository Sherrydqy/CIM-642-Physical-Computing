const int sensorPin = A0;
const float baselineTemp = 25.0;
void setup() {
 // Serial.begin(9600);
 Serial.begin(9600);
 for(int pinNumber = 5; pinNumber<8;pinNumber++){
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber,LOW);
 }

}

void loop() {
  // put your main code here, to run repeatedly:
   int sensorVal = analogRead(sensorPin);
   Serial.print("Sensor Value: ");
   Serial.print(sensorVal);
   float voltage = (sensorVal/1024.0) *5.0;
   float temperature = (voltage - 0.5) * 100;
   if(temperature < baselineTemp){
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
   }
   else if(temperature >= baselineTemp +2 && temperature < baselineTemp +4){
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
   }
   else if(temperature >= baselineTemp +4 && temperature < baselineTemp +6){
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
   }
   else if(temperature >= baselineTemp +6 && temperature < baselineTemp +8){
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
   }
   delay(1);
}
