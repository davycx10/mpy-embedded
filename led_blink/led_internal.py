from time import sleep as time
from  machine import Pin

myLED = Pin('LED',Pin.OUT)
while True:
    myLED.toggle()
    time(0.1)

