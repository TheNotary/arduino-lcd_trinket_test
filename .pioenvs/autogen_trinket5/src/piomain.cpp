#include <Arduino.h>










#include <TinyWireM.h>
#include <TinyAdafruit_RGBLCDShield.h>



#define OFF 0x0
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


 
void setup();
 
void loop();
 
void printzero();
#line 26 "lcd_trinket_test.ino"
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

int8_t offset = 0;
uint8_t backlight = BLUE;

void setup() {
lcd.begin(16, 2);
lcd.setBacklight(BLUE);
}

void loop() {
uint8_t buttons;

lcd.setCursor(0,0);
lcd.print("hi");



if(buttons!=0) {
if (buttons & BUTTON_UP) {
offset +=1;
}
if (buttons & BUTTON_DOWN) {
offset -=1;
}
if (buttons & BUTTON_SELECT) {
if(backlight)
backlight=OFF;
else
backlight=BLUE;
lcd.setBacklight(backlight);
}
}

delay(1000);
}

void printzero() {
lcd.print("0");
}