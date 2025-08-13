from machine import Pin, PWM
from utime import sleep
from neopixel import NeoPixel
import time


ledPin = 1
ledCount = len(led)

# Initialize GPIOs
led = Pin(ledPin, Pin.OUT)
led = NeoPixel(Pin(ledPin, Pin.OUT), ledCount)



# Define button pins
buttons = [10, 11, 14, 15]

# Initialize buttons
buttonOne = Pin(buttons[0], Pin.IN, Pin.PULL_UP)
buttonTwo = Pin(buttons[1], Pin.IN, Pin.PULL_UP)
buttonThree = Pin(buttons[2], Pin.IN, Pin.PULL_UP)
buttonFour = Pin(buttons[3], Pin.IN, Pin.PULL_UP)


while True:
    if buttonOne.value() == 0:
        for i in range(ledCount):
            led[i] = (255, 0, 255)
        led.write()
        print(f"led blanche allumé")

    if buttonTwo.value() == 0:
        for i in range(ledCount):
            led[i] = (128, 0, 255)
        led.write()
        print(f" led vert allumé")

    if buttonThree.value() == 0:
        for i in range(ledCount):
            led[i] = (0, 255, 0)
        led.write()
        print(f"led rouge allumé")

    if buttonFour.value() == 0:
        for i in range(ledCount):
            led[i] = (0, 0, 255)
        led.write()
        print(f" led blue allumé")
