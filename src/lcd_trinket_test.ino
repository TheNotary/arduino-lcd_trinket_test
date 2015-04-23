/*********************
Trinket RGB LCD Shield Clock
 
Example code for the Adafruit RGB Character LCD Shield and Library
for Trinket 
 
The DS1307 Real Time Clock must be initialized with a separate sketch.
**********************/
 
// include the library code:
#include <Wire.h>
// #include <TinyWireM.h>                  // Trinket I2C communications
#include <TinyAdafruit_RGBLCDShield.h>  // RGB LCD Shield communications
 
// These defines make it easy to set the backlight color
#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
 
// The shield uses the I2C SCL and SDA pins. 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
 
int8_t offset = 0;   // Hour offset set by user with buttons
uint8_t backlight = BLUE;  // Backlight state
 
void setup() {
  lcd.begin(16, 2);         // initialize display colums and rows
  lcd.setBacklight(BLUE);  // Set to OFF if you do not want backlight on boot
  setupBlinking();
}
 
void loop() {
  uint8_t buttons;                       // button read value
 
  lcd.setCursor(0,0);
  lcd.print("h");

  blinkOnFor(1000);

  buttons = lcd.readButtons();  // read the buttons on the shield
 
  if(buttons!=0) {                     // if a button was pressed
      if (buttons & BUTTON_UP) {       // if up pressed, increment hours
         offset +=1;
       }
      if (buttons & BUTTON_DOWN) {     // if down pressed, decrement hours
         offset -=1;
       }
      if (buttons & BUTTON_SELECT) {   // if select button pressed
         if(backlight)                 // if the backlight is on
            backlight=OFF;             //   set it to off
         else                          // else turn on the backlight if off 
            backlight=BLUE;           //   (you can select any color)
         lcd.setBacklight(backlight);  // set the new backlight state
      }
   }
  
  delay(1000);  // wait one second
}
 
void printzero() {  // prints a zero to the LCD for leading zeros
  lcd.print("0");   // a function saves multiple calls to the print function
}

void setupBlinking() {
  pinMode(13, OUTPUT);
}

// Turns the light on for onDuration,
// does not control off duration
void blinkOnFor(int onDuration) {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(onDuration);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
}

