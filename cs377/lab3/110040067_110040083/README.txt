CS-377 LAB ASSIGNMENT 3
###############################################################

Abhishek Gupta 		110040067
Mridul Ravi Jain 	110040083
################################################################


This is our second submission for Lab Assignment-3.
We have successfully implemented everything till Section-7.

Each section has been implemented as a function, which may call other helper functions.

For cd: 		changeDirectory(char ** tokens) : this function takes as argument the tokens formed by the absolute or 
			relative path of the directory you wish to switch to. We display an error message if the directory does 
			not  exist.
For run:		runCommand(char ** tokens) : function takes as argument the tokens formed by  a command in the batch file 
			containing a list of commands separated by newline. Our shell program executes them one by one and if one 
			of them executes erroneously we print the `error' and abort the batch without exiting the shell.

For other commands:	execute(char ** tokens) : 
For cron:		execCron(char * filename) : 
For parallel:		parallelCommand(char * input)

##################################################################

We have also submitted a Makefile which compiles our program into an executable called jash.
Commands to compile and run the program are:

make
./jash

This will open our implemented 'jash' shell.

Note that Ctrl + C does NOT kill our parent process, so press Ctrl + D to exit from the program.

##################################################################
