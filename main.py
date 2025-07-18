from machine import Pin
import time

led = Pin("LED", Pin.OUT)

print("Démarrage du clignotement de la LED...")

while True:
    led.toggle()
    print("LED est allumée" if led.value() else "LED est éteinte")
    time.sleep(1)
