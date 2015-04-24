This repo is not functional yet.  

# LcdTrinketTest

This repo is just a basic way of getting a trinket to work with Adafruit's LCD module with keypad

## Installation

Download this repo with git.  

```
$ git clone this_repo
```

Connect your trinket and flash it using platformio:

    $ platformio run

## Parts

- Trinket 5v
- Adafruit i2c 16x2 RGB LCD Pi Plate

## Wiring

### Trinket 5v and Pi LCD
Ok, this is a little tricky.  Adafruit sells the RPi hat, and also one designed to mount onto the arduino.  I used the RPi hat in this repo, the circuitry is the same, it's just figuring out the pins that's tricky.  

Trinket Diagram:  https://learn.adafruit.com/introducing-trinket/pinouts

LCD Plate Diagram: https://learn.adafruit.com/system/assets/assets/000/003/861/original/raspberry_pi_pilcdplate.png?1396802991
LCD Plate Pins: https://forums.adafruit.com/viewtopic.php?f=8&t=72472 

(LCD Plate -> Trinket 5v)
```
pin 2 -> +USB
pin 3 -> #0
pin 5 -> #2
pin 6 -> Gnd
```

### Arduino Uno and Pi LCD
The repo is setup to work with this combo out of the box, btw...


(LCD Plate -> Arduino Uno)
```
pin 2 -> 5v
pin 3 -> SDA
pin 5 -> SCL
pin 6 -> Gnd
```


Extra Notes and Code Source:  https://learn.adafruit.com/trinket-rgb-shield-clock/hook-up

## Device Operation

Just start it, and push the buttons to print different stuff to the screen.  

## Trouble Shooting

### LCD Screen not lighting up
If your screen doesn't light up on boot, it may be due to you messing around with the backlight color in the code.  I think "WHITE" will light all LCD displays.  Some cheapskates try to get away with a single color LCD plate and so turning it to RED will be the same as turning it off if the LCD plate only has a blue color.  


### LCD Screen not displaying text
The LCD screen's contrast needs to be set just right.  If you see a bunch of boxes, that means contrast is too low.  If you see nothing that may mean contrast is too high

### Thing doesn't compile or run
This repo is setup to work fine on the Arduino Uno just fine, but if you use a trinket 5v, you'll need to make some tweaks (maybe I can code that in...).  On the trinket, use those TINY libraries.  Otherwise use the ones that are already setup.  
