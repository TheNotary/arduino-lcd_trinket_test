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

Ok, this is a little tricky.  Adafruit sells the RPi hat, and also one designed to mount onto the arduino.  I used the RPi hat in this repo, the circuitry is the same, it's just figuring out the pins that's tricky.  

Trinket Diagram:  https://learn.adafruit.com/introducing-trinket/pinouts

LCD Plate Diagram: https://forums.adafruit.com/viewtopic.php?f=8&t=72472 

(LCD Plate -> Trinket)
```
pin 2 -> +USB
pin 3 -> #0
pin 5 -> #2
pin 6 -> Gnd
```

Extra Notes and Code Source:  https://learn.adafruit.com/trinket-rgb-shield-clock/hook-up

## Device Operation

Just start it, and push the buttons to print different stuff to the screen.  

