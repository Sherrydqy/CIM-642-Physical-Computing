#include <Servo.h>
 
Servo ServoMotor;
 
// Required hardware I/O connections
const byte PIEZO_PIN      = A0; 
const byte SWITCH_PIN     = 2;  
const byte YELLOW_LED_PIN = 3;  
const byte GREEN_LED_PIN  = 4;  
const byte RED_LED_PIN    = 5; 
const byte SERVO_PIN      = 9;  
 
// Global constants
const unsigned short BAUD_RATE = 9600;
const byte QUIET_KNOCK_VAL     = 30;
const byte LOUD_KNOCK_VAL      = 50;
const byte MAX_NUM_KNOCK       = 3;
 
// Global variables
byte switch_val;
byte knock_val;
boolean is_locked  = false;
byte    num_knocks = 0;
 
void setup() {
    ServoMotor.attach(SERVO_PIN);
    pinMode(SWITCH_PIN,     INPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN,  OUTPUT);
    pinMode(RED_LED_PIN,    OUTPUT);
    Serial.begin(BAUD_RATE);
    // unlock the box first
    digitalWrite(GREEN_LED_PIN, HIGH);
    ServoMotor.write(0);
    Serial.println("ACCESS GRANTED");
}
 
void loop() {
    if (is_locked == false) {
        switch_val = digitalRead(SWITCH_PIN);
 
        if (switch_val == HIGH) {
            LockTheBox();
            delay(1000);
        }
    } else {
        knock_val = analogRead(PIEZO_PIN);
 
        // require MAX_NUM_KNOCK valid knocks
        if ((num_knocks < MAX_NUM_KNOCK) && (knock_val > 0)) {
            if (CheckForKnock(knock_val) == true) {
                num_knocks++;
                delay(1000);
            }
            Serial.print("Need ");
            Serial.print(MAX_NUM_KNOCK - num_knocks);
            Serial.println(" more knock(s)");
        }
 
        if (num_knocks >= MAX_NUM_KNOCK) {
            UnLockTheBox();
            // reset num_knocks
            num_knocks = 0;
        }
    }
}

void UnLockTheBox(void) {
    // change the is_locked value
    is_locked = false;
    // indicate on LEDs
    digitalWrite(RED_LED_PIN,   LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    // rotate the servo to 0 degree
    ServoMotor.write(0);
    // print a message on the Serial Monitor
    Serial.println("ACCESS GRANTED");
    // allow time for the servo to completely move
    delay(20);
}
 

void LockTheBox(void) {
    // change is_locked value
    is_locked = true;
    // indicate on LEDs
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN,   HIGH);
    // rotate the servo to 90 degrees
    ServoMotor.write(90); // rotate the servo 90 degrees to lock
    // print a message on the Serial Monitor
    Serial.println("ACCESS DENIED");
    // allow time for the servo to completely move
    delay(20);
}

boolean CheckForKnock(byte a_knock_val) {
    if ((a_knock_val > QUIET_KNOCK_VAL) && (a_knock_val < LOUD_KNOCK_VAL)) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(50);
        digitalWrite(YELLOW_LED_PIN, LOW);
        Serial.print("Valid knock value: ");
        Serial.println(a_knock_val);
        return true;
    } else {
        Serial.print("Invalid knock value: ");
        Serial.println(a_knock_val);
        return false;
    }
}
