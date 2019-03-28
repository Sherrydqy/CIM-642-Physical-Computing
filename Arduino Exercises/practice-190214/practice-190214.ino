int tonePin = 8;
int photoPin = A0;
int photoRead = 0;

int lowLimit = 0;
int highLimit = 600;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  photoRead = analogRead(photoPin);
  
  if(photoRead < lowLimit){
    photoRead = lowLimit;
  }
  else if(photoRead > highLimit){
    photoRead = highLimit;
  }
  int mapped = map(photoRead, 0, 350,31,4970);
  Serial.println(photoRead);
  //tone(tonePin,mapped,100);
}
