CS-377 LAB ASSIGNMENT 4
###############################################################

Abhishek Gupta 		110040067
Mridul Ravi Jain 	110040083
################################################################


This is our second submission for Lab Assignment-4.
We have successfully implemented everything in Sections-(i), (ii), (iii), (iv) and (v).

Each section has been implemented as a function, which may call other helper functions.

For cd: 			changeDirectory(char ** tokens) 
For run:			runCommand(char ** tokens) 
For file executions, >, <, >> 
and background processes:	execute(char ** tokens)
For cron:			execCron(char * filename) 
For parallel:			parallelCommand(char * input)
For Syntax Checking		check_syntax(char ** tokens)
For |				executePipe(char ** tokens) 


##################################################################

We have also submitted a Makefile which compiles our program into an executable called jash.
Command to compile and run the program are:

make
./jash

This will open our implemented 'jash' shell.
Note that Ctrl + C does NOT kill our parent process(it does not kill background processes as well), so press Ctrl + D or give command:

	exit

It will kill all the child processess along with the parent process.
To erase the executable do: 

make clean

##################################################################
