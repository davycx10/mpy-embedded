# Load libraries
from machine import Pin, PWM
from utime import sleep
buzzerPin = Pin(27)
buzzer = PWM(buzzerPin)


for i in range (5):
# Activate buzzer for 1 sec
    buzzer.freq(1000)
    buzzer.duty_u16(1000)
    sleep(1)
    buzzer.duty_u16(0)
    sleep(1)
    print(f"{i+1}")

buzzer.value(0)