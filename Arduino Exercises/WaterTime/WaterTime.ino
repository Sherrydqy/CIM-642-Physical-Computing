
#include "U8glib.h"   // Library for Oled display https://github.com/olikraus/u8glib/
#include "HX711.h"    // Library for Load Cell amplifier board
#include <math.h>


#define CLK 5   // CLK of HX711 connected to pin 5 of Arduino
#define DOUT 6  // DOUT of HX711 connected to pin 6 of Arduino
#define RESETBTN 4
#define standard = 6;
#define drinkStandard = 40;


int reset_screen_counter=0;      // Variable used to decide what to display on Oled
float unit_conversion;           // Used to convert between measuring units
int decimal_place;               // how many decimal number to display
int weight=0;
float curWeight=0;
int prevWeighz;
int flag_clean = 0;
int stable = 0;
int machineOn, flagFinalWeight, flagTimingState,flagCup, flagAlert, flagBlink;
int weightRead,lastWeight,curRead,preRead; 
float startTime, blinkTime, blinkPreTime, blinkInterval, pastInterval;
float drinkInterval = 10000; 
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

/*int stable_measurement(void){
  preWeight = 
  curWeight = scale.get_units(3)unit_conversion;
  prevWeight = curWeight;
 
  curWeight = 
   Serial.print("fsrRead: ");
   Serial.print(fsrADC);
   Serial.println();
   Serial.print("计时: ");
   Serial.println(String(flagTimingState));
   Serial.print("STABLE: ");
      Serial.println(String(stable));
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (weight > 40 && stable != standard) // If the analog reading is non-zero
  {
     //analogWrite(BLUE_PIN, HIGH);
     //analogWrite(RED_PIN, HIGH);
    //blinkTime = 0;
    //flagBlink = 0;
  
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
}*/

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
        Serial.print("重量：");
        Serial.println(scale.get_units(3)*unit_conversion);
        u8g.print(scale.get_units(3)*unit_conversion, decimal_place);  // Display the average of 3 scale value reading
      } while( u8g.nextPage() );
}



void setup(void) {
  
  Serial.begin(9600);
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
    delay(500);  // Delay between dots
  }
}


void loop(void) {
  Serial.print("按钮：");
  Serial.println(digitalRead(RESETBTN));
  
  //Serial.println(scale.get_units(3)*unit_conversion);
// If Switch is pressed on Rotary Encoder
  if (digitalRead(RESETBTN)) {       // Check to see which action to take
    if(reset_screen_counter == 1) {   
      tare_scale();                   // 1 = zero and start scale
      reset_screen_counter=2;
      delay(500);
    } else {
      if(reset_screen_counter == 2) { // 2 = Scale already started so restart from begining
        reset_screen_counter=0;
        delay(500); 
      }
    }
  }

// If system was just started display intro screen  
  if (reset_screen_counter == 0) {    
    startupscreen();
  reset_screen_counter=1;  // set to 1 and wait for Rotary click to zero scale
  }
 
// if zero (tare) of scale as occured start display of weight
  if (reset_screen_counter == 2) {
          start_scale();
  }
}
