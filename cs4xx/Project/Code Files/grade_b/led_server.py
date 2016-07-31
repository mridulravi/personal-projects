import RPi.GPIO as GPIO
import time
import thread
import socket
import sys
import signal

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

led2=2

GPIO.setup(led2, GPIO.OUT)
count = 0;

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)	# creating a socket
except socket.error:
	print("Failed to create socket")
	sys.exit()

# signal handler (to handle CTRL+C)
def signal_handler(signum, frame):
	global s
	s.close()
	sys.exit()

# This function monitors the occupancy of the room and controls the light. If the room is occupied, then it turns the LED on. If the room is unoccupied for some time, then it turns the LED off.
def check():
	global count
	global led2
	while True:
		GPIO.output(led2,1)
		counter = 0
		while(count == 0):
			counter = counter + 1
			if(counter > 1000000):
				GPIO.output(led2,0)		
	
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
	# creating two threads, one will work as a server while the other will run the check function(i.e. will control the LED on the basis of the occupancy)
	thread.start_new_thread(check, ())
	thread.start_new_thread(server, ())
except:
	print("Error in threads")

while True:
	pass

