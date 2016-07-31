import RPi.GPIO as GPIO
import time

#######
# This code detects whenever something comes in proximity of PIR 
# sensor. 
#######

GPIO.setmode(GPIO.BCM)
PIR_PIN = 18
GPIO.setup(PIR_PIN, GPIO.IN)

def MOTION(PIR_PIN):
	print "Person Detected!"

print "PIR Module Test (CTRL+C to exit)"
time.sleep(2)
print "Ready"

try:
	GPIO.add_event_detect(PIR_PIN, GPIO.FALLING, callback=MOTION, bouncetime=500)
	while True:
		a=2
except KeyboardInterrupt:
	print " Quit"
	GPIO.cleanup()
