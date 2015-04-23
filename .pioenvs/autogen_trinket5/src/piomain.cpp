#include <Arduino.h>










#include <TinyWireM.h>
#include <TinyAdafruit_RGBLCDShield.h>
#include <TinyRTClib.h>


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

RTC_DS1307 RTC;
DateTime Clock;
int8_t offset = 0;
uint8_t backlight = WHITE;

void setup() {
lcd.begin(16, 2);
RTC.begin();
lcd.setBacklight(WHITE);
}

void loop() {
uint8_t buttons;
uint8_t hourval, minuteval, secondval;

DateTime Clock;
char* colon = ":";
char* slash = "/";

Clock = RTC.now();

hourval = Clock.hour()+offset;
if(hourval > 23) hourval-=24;
else if(hourval < 0) hourval+=24;

minuteval = Clock.minute();
secondval = Clock.second();
lcd.setCursor(0,0);
if(hourval < 10) printzero();
lcd.print(hourval);
lcd.print(colon);
if(minuteval < 10) printzero();
lcd.print(minuteval);
lcd.print(colon);
if(secondval < 10) printzero();
lcd.print(secondval);

buttons = lcd.readButtons();

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
backlight=WHITE;
lcd.setBacklight(backlight);
}
}
lcd.setCursor(0,1);
if(Clock.month()<10) printzero();
lcd.print(Clock.month());
lcd.print(slash);
if(Clock.day()<10) printzero();
lcd.print(Clock.day());
lcd.print(slash);
lcd.print(Clock.year());

delay(1000);
}

void printzero() {
lcd.print("0");
}