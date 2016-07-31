import RPi.GPIO as GPIO
import time
import thread
import socket
import sys
import signal

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

led2=2			# for led
led3=3			# for PIR

GPIO.setup(led3, GPIO.OUT)
GPIO.setup(led2, GPIO.OUT)
PIR_PIN = 18		# for receiving input from PIR
motor_pin = 17
GPIO.setup(motor_pin, GPIO.OUT)
GPIO.setup(PIR_PIN, GPIO.IN)
count = 0;
timestamp=time.time()
pir_off = 1

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)	# creating a socket
except socket.error:
	print("Failed to create socket")
	GPIO.cleanup()
	sys.exit()

# signal handler (to handle CTRL+C)
def signal_handler(signum, frame):
	global s
	global led2
	global motor_pin
	s.close()
	GPIO.output(led2, 0)
	GPIO.output(motor_pin, 0)
	GPIO.cleanup()
	sys.exit()

# This function is called when PIR detects a person. This function changes the value of timestamp variable whenever a person is detected
def MOTION(PIR_PIN):
	global timestamp
	global pir_off
	print("Person detected")
	if(pir_off == 0):
		#print("Timestamp changed)
		timestamp = time.time()

# This function controls the LED on the basis of the variable timestamp. The variable timestamp is set on the basis of PIR. The value stored in this variable is compared with current timestamp to determine the time when the person was sensed by the PIR. If the time is > 10 seconds, then LED is turned off otherwise it remains on.
def check_motion():
	global motion_detected
	global led2
	GPIO.output(led2,0)
	while True:
		if(time.time() - timestamp > 10):
			GPIO.output(led2,0)
		elif(pir_off == 0):
			GPIO.output(led2,1)

# This function monitors the occupancy of the room and controls the PIR sensor & servo motor. If the room is occupied, then it turns the PIR sensor & motor on. If the room is unoccupied for some time, then it turns the PIR, motor and LED off.
def check():
	global count
	global pir_off
	global led3
	global motor_pin
	while True:
		GPIO.output(led3,1)
		GPIO.output(motor_pin, 1)
		pir_off = 0;
		counter = 0
		while(count == 0):
			counter = counter + 1
			if(counter > 3000000):
				pir_off = 1;
				GPIO.output(led2, 0)
				GPIO.output(motor_pin, 0)
				GPIO.output(led3,0)
						
# This function creates a server. The server waits for the client(smartdoor R-pi) to join. Once a connection is established, it starts receiving data from the client. "1" means that the person has entered the room & "2" means thar person has exited the room. So, on receiving this value, it accordingly modifies the value of "count" variable which determines the no of persons in the room.		
def server():
	global count
	global s
	HOST = ''
	PORT = 8888

	try:
		s.bind((HOST, PORT))
	except socket.error , msg:
		print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
		sys.exit()
	s.listen(1)
	conn, addr = s.accept()
	while 1:
		data = conn.recv(1)
		if not data:
			break;
		print("data received is " + data + "\n")
		if(data == "1"):
			count = count + 1
		elif(data == "2"):
			count = count - 1
		print("Updated count is" + str(count) + "\n")
		
	conn.close()
	s.close()	

try:
	signal.signal(signal.SIGINT, signal_handler)
	GPIO.add_event_detect(PIR_PIN, GPIO.RISING, callback=MOTION, bouncetime=200)
	# creating three threads, one will work as a server, the other will run the check function(i.e. will control the PIR & servo motor on the basis of the occupancy) and the third one will run the check_motion(i.e. will control the LED) function
	thread.start_new_thread(check_motion, ())
	thread.start_new_thread(check, ())
	thread.start_new_thread(server, ())
except:
	print("Error in threads")

while True:
	pass

