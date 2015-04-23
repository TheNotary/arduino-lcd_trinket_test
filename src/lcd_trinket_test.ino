/*********************
Trinket RGB LCD Shield Clock
 
Example code for the Adafruit RGB Character LCD Shield and Library
for Trinket 
 
The DS1307 Real Time Clock must be initialized with a separate sketch.
**********************/
 
// include the library code:
#include <TinyWireM.h>                  // Trinket I2C communications
#include <TinyAdafruit_RGBLCDShield.h>  // RGB LCD Shield communications
#include <TinyRTClib.h>                 // DS1307 clock communications
 
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
 
RTC_DS1307 RTC;      // Establish clock object
DateTime Clock;      // Holds current clock time
int8_t offset = 0;   // Hour offset set by user with buttons
uint8_t backlight = WHITE;  // Backlight state
 
void setup() {
  lcd.begin(16, 2);         // initialize display colums and rows
  RTC.begin();              // Initialize clock
  lcd.setBacklight(WHITE);  // Set to OFF if you do not want backlight on boot
}
 
void loop() {
  uint8_t buttons;                       // button read value
  uint8_t hourval, minuteval, secondval; // holds the time
 
  DateTime Clock;                    // variable to hold our time
  char* colon = ":";                 // static characters save a bit 
  char* slash = "/";                 //   of memory
  
  Clock = RTC.now();                 // get the RTC time
  
  hourval = Clock.hour()+offset;     // calculate hour to display
  if(hourval > 23) hourval-=24;      // adjust for over 23 hour
  else if(hourval < 0) hourval+=24;  //   or under 0 hours
  
  minuteval = Clock.minute();        // This block prints the time
  secondval = Clock.second();        //  to the LCD Shield
  lcd.setCursor(0,0);
  if(hourval < 10) printzero();      // print function does not print
  lcd.print(hourval);                //   leading zeros so this will
  lcd.print(colon);
  if(minuteval < 10) printzero();
  lcd.print(minuteval);
  lcd.print(colon);
  if(secondval < 10) printzero();
  lcd.print(secondval);
 
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
            backlight=WHITE;           //   (you can select any color)
         lcd.setBacklight(backlight);  // set the new backlight state
      }
   }
  lcd.setCursor(0,1);                  // This block prints the date
  if(Clock.month()<10) printzero();    //   to the LCD Shield
  lcd.print(Clock.month());
  lcd.print(slash);
  if(Clock.day()<10) printzero();
  lcd.print(Clock.day());
  lcd.print(slash);
  lcd.print(Clock.year());
  
  delay(1000);  // wait one second
}
 
void printzero() {  // prints a zero to the LCD for leading zeros
  lcd.print("0");   // a function saves multiple calls to the print function
}
