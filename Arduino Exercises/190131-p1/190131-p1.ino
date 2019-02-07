int button1 = 2;
int led1 = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600); // 9600 is the speed limit for the conversation between
                      // Arduino and your computer
}

void loop() {
  // put your main code here, to run repeatedly:
  int button = digitalRead(2); // read from pin2
  //Serial.println(button);
  //Serial.print("button1:" + button); 不行
  Serial.print("button1:");
  Serial.println(button);
  digitalWrite(13,button);
}
