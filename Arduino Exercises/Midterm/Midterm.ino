#include <math.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

const int FRS_PIN = A0;
const int RED_PIN = 10;
const int BLUE_PIN = 6;
const int standard = 6;
const int VOL_DIV = 100;
const int drinkStandard = 40;
const float SysV = 5; // Measured voltage of Ardunio 5V line
const float R_DIV= 977; // Measured resistance of 3.3k resistor
float force; // current force applied on the sensor
int weightRead,lastWeight,curRead,preRead; 
float startTime, blinkTime, blinkPreTime, blinkInterval, pastInterval;
float drinkInterval = 10000; 
int machineOn,stable,  flagFinalWeight, flagTimingState,flagCup, flagAlert, flagBlink;
void setup() 
{
  
  Serial.begin(9600);
  pinMode (RED_PIN, OUTPUT);
  pinMode (BLUE_PIN, OUTPUT);
  /*lcd.begin(16,2);
  lcd.print("Ask the");
  lcd.setCursor(0,1);
  lcd.print("Crystal Ball!");*/
  flagFinalWeight = 0;
  flagTimingState = 0;
  stable = 0;
  weightRead = 0;
  lastWeight = 0;
  curRead = 0;
  preRead = 0;
  flagCup = 0;
  flagAlert = 0;
  blinkInterval = 1000;
  blinkTime = 0;
  blinkPreTime = 0;
  flagBlink = 0;
 // delay(5000);
  
}

void loop() 
{
  force=0;
  
  preRead = curRead;
  int  fsrADC= analogRead(FRS_PIN);
  curRead = fsrADC;
   Serial.print("fsrRead: ");
   Serial.print(fsrADC);
   Serial.println();
   Serial.print("计时: ");
   Serial.println(String(flagTimingState));
   Serial.print("STABLE: ");
      Serial.println(String(stable));
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC > VOL_DIV && stable != standard) // If the analog reading is non-zero
  {
    analogWrite(BLUE_PIN, HIGH);
     analogWrite(RED_PIN, HIGH);
    blinkTime = 0;
    flagBlink = 0;
  
   if(flagCup == 0 || flagCup == 3){
    flagCup = 1;
   }
    // Use ADC reading to calculate voltage:
    /*float fsrV = fsrADC * SysV/ 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (SysV /fsrV - 1.0);
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    /*if (fsrR <= 600) 
      force = (fsrG -0.00075) / 0.00000102639;
    else
     force =  fsrG / 0.000000700857;*/
  
    
    if (fabs(curRead - preRead) < 4 ){
      stable++; 
    }
    else{
      stable = 0;
    }
  }

    if (stable >= standard  && flagCup != 0 && flagTimingState != 1 && flagTimingState != 3){
      weightRead = curRead;
      //Serial.print("Current Weight: ");
      Serial.println("混蛋");
       Serial.print("Current Weight: ");
      Serial.println(String(weightRead));
     // flagFinalRead = 1;
     if(flagTimingState == 0){
      startTime = millis();
      flagTimingState = 1;
      analogWrite(BLUE_PIN, HIGH);
      analogWrite(RED_PIN, LOW);
     }
     if(flagTimingState == 2){
      flagTimingState = 3;
     }
     
    }

    if(fsrADC > VOL_DIV && flagCup != 0){
     
     Serial.print("Current Weight: ");
      Serial.println(String(weightRead));
      if(flagCup == 1 && flagTimingState == 1){
      pastInterval = millis() - startTime;
       Serial.print("Time has past: ");
      Serial.println(String(pastInterval / 1000));
      if(pastInterval > drinkInterval && flagCup == 1 ){
        flagAlert = 1;
        Serial.println("喝水啦！！！！");
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
        myBlink(RED_PIN, blinkInterval);
        
      }
      }

      else if(fsrADC > VOL_DIV && pastInterval > drinkInterval && flagCup == 2 && stable == standard && flagTimingState == 3 ){

        preRead = curRead;

        
        if(fabs(weightRead - lastWeight) <= drinkStandard){
        Serial.println("--- 多喝点-----！");
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
        
      }
      else {
        Serial.println("这儿了？？");
        flagAlert = 0;
        stable = 0;
        flagCup = 0;
        lastWeight = weightRead;
        weightRead = 0;
        lastWeight = 0;
        curRead = 0;
        preRead = 0;
        flagTimingState = 0;
       // flagFinalRead = 0;
        startTime = 0; 
      }
    }
      
    }
    
  
  if (fsrADC < VOL_DIV && flagCup != 0){
    //Serial.println("水杯起来了");
   
       
       if(flagAlert == 1){
        flagCup = 2;
       lastWeight = weightRead;
       stable = 0;
        flagTimingState = 2;
       }
    
       else{
         flagCup = 3;
         stable = 0;
         lastWeight = weightRead;
        weightRead = 0;
        lastWeight = 0;
        curRead = 0;
        preRead = 0;
        flagTimingState = 0;
       // flagFinalRead = 0;
        startTime = 0; 
       }
       
       Serial.println("--- 正在喝喝喝喝水-----！");
       analogWrite(BLUE_PIN, HIGH);
      analogWrite(RED_PIN, LOW);
      myBlink(BLUE_PIN, blinkInterval*2);
     }
   /*else{
    flagCup = 0;
    stable = 0;
     lastWeight = weightRead;
    weightRead = 0;
    curRead = 0;
    preRead = 0;
    flagTimingState = 0;
   // flagFinalRead = 0;
    startTime = 0; 
   }*/


/*  Serial.println("Force: " + force + " g");
    Serial.println();
    Serial.println("Weight: " + weight + " g");
    Serial.println();*/

    delay(500);
}

void myBlink(int pin, float interval){
  if(flagBlink == 0){
    blinkTime = millis();
   // blinkPreTime = blinkTime;
    flagBlink = 1;
  }
  if(millis()- blinkTime < interval ){
    digitalWrite(pin, LOW);
   
  }
  else{
    blinkTime = millis();
  }
  return;
}
