from machine import Pin
import time

btn = Pin(15, Pin.IN, Pin.PULL_UP)  # remplace 15 par le GPIO bouton

while True:
    if btn.value() == 0:
        print("Bouton pressé !")
    time.sleep(0.1)