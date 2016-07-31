import RPi.GPIO as GPIO
import time
import socket
import sys

state_11 = 0;
state_16 = 0;

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)	# creating a socket
except socket.error:
	print("Failed to create socket")
	sys.exit()

# This function is called when a rising edge is detected by pin 11. This function checks whether pin 16 has already received a rising edge or not. If yes, then it means an exit (so it sends "2" to the server, and resets the value of the variables(state_11 & state_16) ). If not, then it changes the value of the variable state_11 to 1
def event_handler_11(pin):
	global state_11
	global state_16
	# Now check the value of the other parameter and based on that, take decision
	print("Inside function 11")
	if(state_16 == 1):
		## Then exit
		try :
			s.send("2")
		except socket.error:
			print("send failed")
			sys.exit()
		print("Exit")
		state_11 = 0;
		state_16 = 0;
	else :
		state_11 = 1;		

# This function is called when a rising edge is detected by pin 16. This function checks whether pin 11 has already received a rising edge or not. If yes, then it means an entry (so it sends "1" to the server, and resets the value of the variables(state_11 & state_16) ). If not, then it changes the value of the variable state_16	to 1
def event_handler_16(pin):
	global state_11
	global state_16
	# Now check the value of the other parameter and based on that, take decision
	print("Inside function 16")
	if(state_11 == 1):
		## Then entry
		try :
			s.send("1")
		except socket.error:
			print("send failed")
			sys.exit()	
		print("Person has entered the room")
		state_11 = 0;
		state_16 = 0;
	else :
		state_16 = 1;


def main():

	# connect to the server
	
	host="10.129.23.66"
	port=8888
	try:
		remote_ip=socket.gethostbyname(host);
	except socket.gaierror:
		print("Error in gethostbyname");
		sys.exit()
	s.connect((remote_ip, port))

	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(11, GPIO.IN)
	GPIO.setup(16, GPIO.IN)

	GPIO.add_event_detect(11, GPIO.RISING, callback=event_handler_11, bouncetime=500)
	# now the pin 11 will work as an input pin and on detecting a RISING edge, the function event_handler_11 will be called
	
	GPIO.add_event_detect(16, GPIO.RISING, callback=event_handler_16, bouncetime=500)
	# now the pin 16 will work as an input pin and on detecting a RISING edge, the function event_handler_16 will be called

	while True:
		a=2

	GPIO.cleanup()
	s.close()

main()
