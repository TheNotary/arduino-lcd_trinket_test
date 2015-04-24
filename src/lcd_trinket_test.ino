/*********************
Trinket RGB LCD Shield Clock
 
Example code for the Adafruit RGB Character LCD Shield and Library
for Trinket 
 
The DS1307 Real Time Clock must be initialized with a separate sketch.
**********************/
 
// include the library code:
#include <Wire.h>

// If on Arduino Uno, use this...
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// THIS CODE IS FOR A TRINKET OR OTHER TINY 85 BASED SYSTEM TO GET SHIELD AND I2C WORKING!
// #include <TinyWireM.h>                  // Trinket I2C communications
// #include <TinyAdafruit_RGBLCDShield.h>  // RGB LCD Shield communications
 
// These defines make it easy to set the backlight color
#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
 
#define SCREEN_X 0xf
#define SCREEN_Y 0x2

// The shield uses the I2C SCL and SDA pins. 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
 
int8_t offsetX = 0;   // Hour offset set by user with buttons
int8_t offsetY = 0;   // Hour offset set by user with buttons
int8_t frame = 0;   // keeps track of how many frames have gone by
int8_t lastButtonPress = 0;
String displayText = "hello";
boolean doesNeedRedraw;
uint8_t backlight = WHITE;  // Backlight state
 
void setup() {
  lcd.begin(SCREEN_X, SCREEN_Y);         // initialize display colums and rows
  lcd.setBacklight(WHITE);  // Set to OFF if you do not want backlight on boot
  doesNeedRedraw = true;
}
 
void loop() {
  if (doesNeedRedraw)
    draw();

  pollKeys();
  
  frame++;
  if (frame > 63){
    frame = 7;
    lastButtonPress = 0;
  }
  delay(60);  // wait one second
}

void draw() {
  lcd.clear();
  lcd.setCursor(offsetX,offsetY);
  lcd.print(displayText);

  doesNeedRedraw = false;
}

void pollKeys() {
  uint8_t buttons;                       // button read value

  buttons = lcd.readButtons();  // read the buttons on the shield
 
  if(buttons!=0) {                     // if a button was pressed
    boolean wasSelectButtonPressedTooRecently = (frame - lastButtonPress) <= 8;
    doesNeedRedraw = true;
    if (buttons & BUTTON_RIGHT) {       // if up pressed, increment hours
      offsetX +=1;
    }
    if (buttons & BUTTON_LEFT) {     // if down pressed, decrement hours
      offsetX -=1;
    }
    if (buttons & BUTTON_UP) {       // if up pressed, increment hours
      offsetY -=1;
    }
    if (buttons & BUTTON_DOWN) {     // if down pressed, decrement hours
      offsetY +=1;
    }
    if (buttons & BUTTON_SELECT && !wasSelectButtonPressedTooRecently ) { 
      lastButtonPress = frame;
      if(backlight)                 // if the backlight is on
        backlight=OFF;             //   set it to off
      else                          // else turn on the backlight if off 
        backlight=WHITE;           //   (you can select any color)
      
      lcd.setBacklight(backlight);  // set the new backlight state
    }
    if (buttons & BUTTON_SELECT && wasSelectButtonPressedTooRecently ) { 
      doesNeedRedraw = false;
    }

    confineDisplayText();
  }
}

void confineDisplayText() {
  if (offsetX > SCREEN_X) {
    offsetX = SCREEN_X;
    doesNeedRedraw = false;
  }
  if (offsetX < 0) {
    offsetX = 0;
    doesNeedRedraw = false;
  }
  if (offsetY >= SCREEN_Y) {
    offsetY = SCREEN_Y - 1;
    doesNeedRedraw = false;
  }
  if (offsetY < 0) {
    offsetY = 0;
    doesNeedRedraw = false;
  }
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

