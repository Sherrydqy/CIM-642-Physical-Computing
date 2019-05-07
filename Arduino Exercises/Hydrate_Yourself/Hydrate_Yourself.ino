#include "U8glib.h"   // Library for Oled display https://github.com/olikraus/u8glib/
#include "HX711.h"    // Library for Load Cell amplifier board
#include <math.h>
#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 26 // Number of LEDs in strip
#define DATAPIN    3
#define CLOCKPIN   2
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
#define CLK 5   // CLK of HX711 connected to pin 5 of Arduino
#define DOUT 6  // DOUT of HX711 connected to pin 6 of Arduino
#define RESETBTN 4


const int FRS_PIN = A0;
//const int RED_PIN = 10;
//const int BLUE_PIN = 6;
const int standard = 6;
const int VOL_DIV = 100;
const int drinkStandard = 40;
const float SysV = 5; // Measured voltage of Ardunio 5V line
const float R_DIV= 977; // Measured resistance of 3.3k resistor
float force; // current force applied on the sensor
int weightRead,lastWeight,curRead,preRead; 
float startTime, blinkTime, blinkPreTime, blinkInterval, pastInterval;
float drinkInterval = 10000; 
int machineOn,stable, flagFinalWeight, flagTimingState,flagCup, flagAlert, flagBlink;
int reset_screen_counter=0;      // Variable used to decide what to display on Oled
float unit_conversion;           // Used to convert between measuring units
int decimal_place;               // how many decimal number to display
int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;
int bright = 254;
int dimming = 5;
int flag_clean = 0; 
HX711 scale;  // Init of the HX711
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_FAST);  // Init of the OLED



void startupscreen(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.firstPage(); 
  do {
    u8g.drawStr( 0, 10, "Clear Scale");
    u8g.drawStr( 0, 28, "Click to zero...");
  } while( u8g.nextPage() );
}

// Reset Scale to zero
void tare_scale(void) {
  scale.begin(DOUT, CLK);
  scale.set_scale(-109600);  //Calibration Factor obtained from calibration sketch 
  scale.tare();             //Reset the scale to 0  
 // flag_clean= 1;
}

// Start Displaying information on OLED
void start_scale(void) {
  char temp_current_units[15];  // Needed to store String to Char conversion
  String KG="KG";
  String GRAMS="GRAMS";
  String LBS="POUNDS";
  
                  // 0 = grams
    GRAMS.toCharArray(temp_current_units, 15);  // Convert String to Char for OLED display
    unit_conversion=1000;                        // conversion value for grams
    decimal_place=0;                            // how many decimal place numbers to display
  
    u8g.setFont(u8g_font_unifont);
    u8g.firstPage(); 
      do {
        u8g.drawStr( 0, 10, temp_current_units);  // Display the current measurement unit
        u8g.setPrintPos(38, 28);
       
        u8g.print(888888, decimal_place);  // Display the average of 3 scale value reading
      } while( u8g.nextPage() );
}


void setup() 
{
  
  //Serial.begin(9600);
  //pinMode (RED_PIN, OUTPUT);
  //pinMode (BLUE_PIN, OUTPUT);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
  reset_screen_counter = 1;
  //strip.setPixelColor(0, 0,0,0);
  uint32_t sco= strip.Color(243,218,235);
   strip.fill(sco,0,NUMPIXELS-1);
  strip.begin(); // Initialize pins for output
  //strip.show();
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
 
   // Rotate screen 180 degrees on OLED, if required
  u8g.setRot180();

  // Set color of OLED to Monochrome
  u8g.setColorIndex(1);

  // Select font to use
  u8g.setFont(u8g_font_unifont);

  String start_count_string="Starting up....";  // Message to display at Startup
  char start_count[15];  // Used to String to Char conversion
  
  // Loop to display counting dots
  for (int x=12; x < 16; x++) {  // Select the first 12 to 16 character of String
    start_count_string.toCharArray(start_count, x);
    u8g.firstPage(); 
    do {
      u8g.drawStr( 0, 10, "ARDUINO SCALE");
      u8g.drawStr( 0, 28, start_count);
    } while( u8g.nextPage() );
   // delay(500);  // Delay between dots
  }
  
  
}

void loop() 
{
    if(reset_screen_counter == 1) {   
      tare_scale();     
      reset_screen_counter=2;
    }  
    start_scale();

  if(reset_screen_counter==2){
   // Serial.print("上一次: ");
    //   Serial.print(curRead);
       preRead = curRead;
       int  fsrADC= scale.get_units(3)*unit_conversion;
       curRead = fsrADC;
     //  Serial.print("这一次: ");
      // Serial.print(curRead);
      // Serial.print("fsrRead: ");
      // Serial.print(fsrADC);
      // Serial.println();
      // Serial.print("计时: ");
      // Serial.println(String(flagTimingState));
      // Serial.print("STABLE: ");
      // Serial.println(String(stable));
          
      if (fsrADC > 40 && stable != standard) // If the analog reading is non-zero
      {
        
       if(flagCup == 0 || flagCup == 3){
        flagCup = 1;
       }

        if (fabs(curRead - preRead) < 4 ){
           
          stable++; 
        }
        else{
          stable = 0;
        }
      }
     if(flagCup==1 && stable<standard){
      uint32_t c1 = strip.Color(255, 27, 155);
        uint32_t c2 = strip.Color(123, 65, 255);
        lightBlinking (c1,c2,500);
     }
        else if (stable >= standard  && flagCup != 0 && flagTimingState != 1 && flagTimingState != 3){
           
          weightRead = curRead;
          u8g.print(weightRead, decimal_place);
         // Serial.println("混蛋");
         //  Serial.print("Current Weight: ");
         // Serial.println(String(weightRead));
         if(flagTimingState == 0){
          startTime = millis();
          flagTimingState = 1;
         }
         if(flagTimingState == 2){
          flagTimingState = 3;
         }
         
         
        }
    
        if(fsrADC > 40 && flagCup != 0 && stable >= standard){
          uint32_t waitingColor = strip.Color(255, 0, 255);
         // Serial.print("亮度：");
        // Serial.println(bright);
          lightBreathing(waitingColor);          
        // Serial.print("Current Weight: ");
        //  Serial.println(String(weightRead));
          if(flagCup == 1 && flagTimingState == 1){
          pastInterval = millis() - startTime;
         //  Serial.print("Time has past: ");
         // Serial.println(String(pastInterval / 1000));
          if(pastInterval > drinkInterval && flagCup == 1 ){
            flagAlert = 1;
            uint32_t c1 = strip.Color(12, 217, 45);
          uint32_t c2 = strip.Color(43, 183, 60);
        lightBlinking (c1,c2,300);
           // Serial.println("喝水啦！！！！");
          }
          }
    
          else if(fsrADC > 40 && pastInterval > drinkInterval && flagCup == 2 && stable == standard && flagTimingState == 3 ){
    
            preRead = curRead;
            flagTimingState = 0;
            
          }
        }
 
      if (fsrADC < 40 && flagCup != 0){
           flagCup = 3;
            stable = 0;
            lastWeight = weightRead;
            weightRead = 0;
            lastWeight = 0;
            curRead = 0;
            preRead = 0;
            flagTimingState = 0;
            startTime = 0; 
           
          // Serial.println("--- 正在喝喝喝喝水-----！");
           uint32_t c1 = strip.Color(255, 27, 23);
          uint32_t c2 = strip.Color(123, 35, 10);
        lightBreathing (c2);

         }
  }
}
/*void lightMeasuring(){
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  //delay(5);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0;
}*/

void lightBlinking(uint32_t color1, uint32_t color2, int interval){
  
  strip.fill(color1,0,NUMPIXELS-1);     // 'Off' pixel at tail
  strip.show();   
  delay(interval);
  
  strip.fill(color2,0,NUMPIXELS-1);    // 'Off' pixel at tail
  strip.show();  
  delay(interval);                 
}

void lightBreathing(uint32_t color){
  
  strip.setBrightness(bright);
  strip.fill(color,0,NUMPIXELS-1); 
  strip.show(); 
  bright+=dimming;
  if(bright>254){
      bright = 255;
      dimming = -5;
   }else if(bright<1){
       bright = 0;
       dimming = 5;
   }                  
}
