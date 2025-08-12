from machine import Pin, PWM
from utime import sleep

# Servo pin numbers
servoOnePin = 7
servoTwoPin = 8
servoThreePin = 9
servoFourPin = 20

# Initialize servos
servoOne = PWM(Pin(servoOnePin))
servoTwo = PWM(Pin(servoTwoPin))
servoThree = PWM(Pin(servoThreePin))
servoFour = PWM(Pin(servoFourPin))

# Set PWM frequency to 50 Hz for all servos
servoOne.freq(50)
servoTwo.freq(50)
servoThree.freq(50)
servoFour.freq(50)

# Servo degree positions in nanoseconds
deg0 = 500000    # 0.5 ms
deg45 = 1000000  # 1.0 ms
deg90 = 1500000  # 1.5 ms
deg135 = 2000000 # 2.0 ms
deg180 = 2500000 # 2.5 ms

while True:
    # Move each servo through a range of angles
    for servo in [servoOne, servoTwo, servoThree, servoFour]:
        print("Moving to 0 degrees")
        servo.duty_ns(deg0)
        sleep(1)
        print("Moving to 45 degrees")
        servo.duty_ns(deg45)
        sleep(1)
        print("Moving to 90 degrees")
        servo.duty_ns(deg90)
        sleep(1)
        print("Moving to 135 degrees")
        servo.duty_ns(deg135)
        sleep(1)
        print("Moving to 180 degrees")
        servo.duty_ns(deg180)
        sleep(1)
