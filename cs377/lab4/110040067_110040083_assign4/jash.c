#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include<time.h>
#include<fcntl.h>
#include<sys/shm.h>

#define MAXLINE 1000
#define DEBUG 0
#define true 1
#define false 0

//declarations for functions
char ** tokenize(char*);
int execute(char ** tokens);
int runCommand(char ** tokens);
int changeDirectory(char ** tokens);
void execCron(char * filename);
void parallelCommand(char * input);
int check_syntax(char ** tokens);
int executePipe(char ** tokens);

// global variable
int ppid;
int grp_id[MAXLINE];
int grpCounter;

/*
	Testing Portion:-
		1) cd works on parent process, even if it is in a file which is run via "run <filename>" command
		2) Execution of built-in jash commands(cd and run) :- working completely, made calls to other batch files in batch file itself. If any command does not work properly, then it stops the processing of the batch file and prints an abort message(for this we are returning 0 and 1 from each function, 0 means success and 1 means failure)
		3) File execution : working correctly, no problem in it.
		4) Ctrl-C kills only child process, no effect on parent process
		5) cron working properly --- nested crons also working, parallel inside cron also working
		6) Parallel also working fine, parallel inside parallel is not allowed
		7) Exit command implemented
		8) handler working 
		9) I/O redirection working
		10) pipelining working
		11) concurrent also working
*/

// handler to handle the SIGINT signal 
// will exit the process if it is a child process, for parent process(original jash process ), it will print a $ on a new line 
void handler(int num){
	if(ppid!= getpid()){
		exit(129);
	}
	else{
		printf("\n$ ");
		fflush(stdout);
	}
}

int main(int argc, char** argv){
	ppid = getpid();
	//Setting the signal interrupt to its default function.
	signal(SIGINT, handler);

	bzero(grp_id, MAXLINE);
	grpCounter = 0;
	
	//Allocating space to store the previous commands.
	int numCmds = 0;
	char **cmds = (char **)malloc(1000 * sizeof(char *));

	int printDollar = 1;

	char input[MAXLINE];
	char** tokens;

	int notEOF = 1;
	int i;

	FILE* stream = stdin;

	while(notEOF) { 
		if (printDollar == 1){ 
			printf("$ "); // the prompt
			fflush(stdin);
		}
		bzero(input, MAXLINE);
		char *in = fgets(input, MAXLINE, stream); //taking input one line at a time

		//Checking for EOF
		if (in == NULL){
			if (DEBUG) printf("EOF found\n");
			break;
		}

		//add the command to the command list.
		cmds[numCmds] = (char *)malloc(sizeof(input));
		strcpy(cmds[numCmds++], input); 

		// Calling the tokenizer function on the input line   
		tokens = tokenize(input);	
		if(tokens[0] == NULL){
			continue;
		}
		// first check whether the input line is valid, that is if there is only one operator of any kind, i.e. only 1 "<" not 2 "<"
		// creating a function, check_syntax which returns 1 if any error, else returns 0
		
		if(check_syntax(tokens) != 0){
			continue;		
		}
		
		int pipePresent = 0, counter = 0;
		
		for(;tokens[counter]!=NULL;counter++)
		{
			if(strcmp(tokens[counter], "|") == 0)
			{
				pipePresent = 1;
				break;
			}		
		}

		// if pipe is present in the command, then presentPipe will be set to 1
		if(pipePresent)
		{
			executePipe(tokens);
			continue;			// after this the loop will again start from the beginning
		}
		
		if(strcmp(tokens[0],"exit") == 0){
			// have to kill all child before killing the parent process
			//kill(0,SIGKILL);		// kills all the processes in the process group of the parent process
			kill(0, SIGINT); // kills all foreground processes 
			int myCounter = 0;
			for(;myCounter<grpCounter;myCounter++){	
				kill(grp_id[myCounter], 9);			// for killing all background processes
			}
			exit(0);
			// can also use kill(0, SIGINT); exit(0);			// it will kill all the child and then we will exit from the parent
			//one other way is to use a data structure where we should insert all the process id's and later on use that to kill all the child process
		}
		else if(strcmp(tokens[0],"cd") == 0){
			// calling changeDirectory function
			changeDirectory(tokens);
		}
		else if(strcmp(tokens[0],"run") == 0){
			if(runCommand(tokens) == 1){
				printf("Aborting the running of bash file\n");
				continue;
			}
		}
		else if(strcmp(tokens[0],"cron") ==0){
			if(tokens[1] != NULL && tokens[2] == NULL){
				execCron(tokens[1]);
			}
			else{
				printf("Usage:\n	cron <filename>\n");
				continue;
			}
		}
		else if(strcmp(tokens[0], "parallel") == 0){
			parallelCommand(input);
			continue;
		}
		else{
			execute(tokens);
		}
	}
  
	printf("Print and deallocate %s\n", tokens[0]);
	// Freeing the allocated memory	
	for(i=0;tokens[i]!=NULL;i++){
		free(tokens[i]);
	}
	free(tokens);
	kill(0, SIGINT);
	int myCounter = 0;
	for(;myCounter<grpCounter;myCounter++){
		kill(grp_id[myCounter], 9);
	}
	return 0;
}

int executePipe(char ** tokens)
{
	int status;
	int fd[2];
	if(pipe(fd) == -1)	// now fd[0] stores the file descriptor of the reading end and fd[1] stores the descriptor of the writing end
	{
		perror("pipe:");
		exit(1);
	}	
	int pid = fork();
	if(pid == 0){
		// a child process inherits descriptors from its parents
		if(close(fd[0]) == -1)			// since child wouldn't read,therefore closing its reading descriptor
		{
			perror("close:");
			exit(1);
		}
		int i=0;
		for(;tokens[i]!=NULL;i++)
		{
			if(strcmp(tokens[i], "|") == 0)
			{
				tokens[i] = NULL;
				break;
			}
		}
	
		close(1);
		dup(fd[1]);
		
		if(execvp(tokens[0], tokens) == -1)
		{
			perror("execvp:");
			exit(1);
		}

		if(close(fd[1]) == -1)			
		{
			perror("close:");
			exit(1);
		}
		exit(0);
	}
	
	if(!fork()){
		// a child process inherits descriptors from its parents
		if(close(fd[1]) == -1)			// since child wouldn't write, therefore closing its writing descriptor
		{
			perror("close:");
			exit(1);
		}
		int i=0, j=0;
		int temp = 0;
		char * newTokens[MAXLINE];
		bzero(newTokens, MAXLINE);
		for(;tokens[i]!=NULL;i++)
		{
			if(temp)
			{
				newTokens[j] = (char *) malloc(sizeof(tokens[i]) * sizeof(char));
				strcpy(newTokens[j++], tokens[i]);
			}
			else if(strcmp(tokens[i], "|") == 0)
			{
				temp = 1;
			}
		}
		
		close(0);
		dup(fd[0]);
		
		if(execvp(newTokens[0], newTokens) == -1)
		{
			perror("execvp:");
			exit(1);
		}
		
		if(close(fd[0]) == -1)			
		{
			perror("close:");
			exit(1);
		}
		exit(0);
	}
	return 0;
}

int check_syntax(char ** tokens){
	// these are the tokens for a line
	// < is not present twice, < is followed by a valid file(which exists), a file name is given after > or >>
	// no << is present
	// > or >> should not be present twice
	// pipe should not be present with <, >, >> or &
	// "&" should be present at the end of the file only
	
	int inputOp = 0, outputOp = 0, i=0, pipeCount = 0, andCount = 0;
	for(;tokens[i]!=NULL;i++)
	{
		if(strcmp(tokens[i], "<") == 0){
			inputOp++;
			// check if the next is a valid file
			if(tokens[i+1] == NULL){
				printf("File name not given\n");
				return 1;
			}
			else{
				FILE * temp = fopen(tokens[i+1], "r");
				if(temp==NULL){
					printf("File not present\n");
					return 1;
				}
				fclose(temp);
			}
			
		}
		else if( (strcmp(tokens[i], ">") == 0) || (strcmp(tokens[i], ">>") == 0) ){
			outputOp++;
			if(tokens[i+1] == NULL){
				printf("File name not given\n");
				return 1;
			}
		}
		else if(strcmp(tokens[i], "|") == 0)
		{	
			pipeCount++;
		}
		else if(strcmp(tokens[i], "&") == 0)
		{
			andCount++;
			if(tokens[i+1] != NULL)
			{
				printf("'&' should be present at the end of the command only\n");
				return 1;
			}
		}
	}
	if(inputOp>=2){
		printf("Input redirection done more than once\n");
		return 1;
	}
	else if(outputOp>=2){
		printf("Output redirection done more than once\n");
		return 1;
	}
	if(pipeCount > 0 && (inputOp > 0 || outputOp > 0))
	{
		printf("Pipe with Ridirection prohibited\n");
		return 1;
	}
	if(pipeCount > 0 && andCount > 0){
		printf("Pipe with & prohibited\n");
		return 1;
	}
	if(pipeCount >=2)
	{
		printf("2 or more pipes are not allowed in a command\n");
		return 1;
	}
	if(andCount >= 2)
	{
		printf("2 or more '&' are not allowed in a command\n");
		return 1;
	}
	return 0;
}


// This function is for running "run" command
int runCommand(char ** tokens){
	// open the file and read each line, then execute each command
	FILE * fp;
	int status;
	int i;
	fp = fopen(tokens[1], "r");
	if(fp == NULL){
		printf("Error in opening file\n");
		return 1;
	}
	char myInput[MAXLINE];
	char ** myTokens;
	// This loop will read each line of the batch file and try to execute the comman by calling the required function
	// In case of error, it will return 1 which we will use in the main function to determine that some instruction did not stop properly
	// On detecting that(error in executing instruction) in the main, we will print the message for aborting run command
	while(fgets(myInput, MAXLINE, fp) !=NULL){
		myTokens = tokenize(myInput);
		// so cd and run will not fork a new process, they will run in this process only

		if(check_syntax(myTokens) != 0){
			return 1;
			//continue;		
		}
		int pipePresent = 0, counter = 0;
		
		for(;myTokens[counter]!=NULL;counter++)
		{
			if(strcmp(myTokens[counter], "|") == 0)
			{
				pipePresent = 1;
				//printf("Pipe is present in the command\n");
				break;
			}		
		}

		// if pipe is present in the command, then presentPipe will be set to 1
		if(pipePresent)
		{
			executePipe(myTokens);
			continue;			// after this the loop will again start from the beginning
		}

		if(strcmp(myTokens[0],"cd")==0){
			if(changeDirectory(myTokens) != 0){
				return 1;
			}
		}
		else if(strcmp(myTokens[0],"run")==0){
			if(runCommand(myTokens) !=0){
				return 1;
			}	
		}
		else if(strcmp(myTokens[0],"cron")==0){
			if(myTokens[1] != NULL && myTokens[2] == NULL){
				execCron(myTokens[1]);
			}
			else{
				printf("Usage:\n	cron <filename>\n");
				return 1;
			}
		}
		else if(strcmp(myTokens[0], "parallel") == 0){
			parallelCommand(myInput);
		}
		else{
			if(execute(myTokens)!=0){
				return 1;
			}
		}
		bzero(myInput,MAXLINE);	
	}
	fclose(fp);
	return 0;
}

// This fucntion is used for changing directory
int changeDirectory(char ** tokens){
	if(tokens[2] == NULL){
		if(chdir(tokens[1])!=0){
			printf("Directory not found\n");
			perror("cd:");
			return 1;
		}
		else{
			return 0;
		}
	}	
	else{
		printf("Usage:\ncd directory\n");
		return 1;
	}

}

// For all the commands except the mentioned commands, this function is used
int execute(char ** tokens){
	int status, pid;
	int i=0, isPresent = 0;
 	pid = fork();
	for(i=0;tokens[i]!=NULL;i++)
	{
		if(strcmp(tokens[i],"&") ==0)
		{
			isPresent = 1;
			grp_id[grpCounter++] = pid;
			break;
		}
 	}
	if(pid == 0){
		// now i have to run the commands, they are in tokens array

		// now if there are < or this, then i have to change the file descriptors associated with them
		char inputFile[MAXLINE];
		char outputFile[MAXLINE];
		bzero(inputFile, MAXLINE);
		bzero(outputFile, MAXLINE);
		int j=0, andPresent = 0;
		i=0;
		int infd, outfd;
		
		char * newTokens[MAXLINE];
		bzero(newTokens, MAXLINE);
		for(;tokens[i]!=NULL;i++)
		{
			if(strcmp(tokens[i], "<") == 0)
			{
				strcpy(inputFile, tokens[i+1]);
				if( (infd = open(inputFile, O_RDONLY)) < 0)
				{
					perror("open :");
					exit(1);
				}
				close(0);
				dup(infd);
				i++;
				continue;
			}
			
			if(strcmp(tokens[i], ">") == 0)
			{
				strcpy(outputFile, tokens[i+1]);
				if( (outfd = open(outputFile, O_CREAT | O_RDWR,S_IRUSR | S_IWUSR) ) <0)
				{
					perror("open :");
					exit(1);
				}
				close(1);
				dup(outfd);
				i++;
				continue;
			}
			
			if(strcmp(tokens[i], ">>") == 0)
			{
				strcpy(outputFile, tokens[i+1]);
				if( (outfd = open(outputFile, O_CREAT | O_RDWR | O_APPEND ,S_IRUSR | S_IWUSR) ) <0)
				{
					perror("open :");
					exit(1);
				}
				close(1);
				dup(outfd);
				i++;
				continue;
			}
			
			if(strcmp(tokens[i], "&") == 0){
				andPresent = 1;
				if( setsid() == -1){
					perror("setsid:");
					return 1;
				}
				continue;
			}
			
			newTokens[j] = (char *) malloc(sizeof(tokens[i]) * sizeof(char) );
			strcpy(newTokens[j++], tokens[i]);
		}
		
		if(execvp(newTokens[0], newTokens) == -1){
			perror("execvp:");
			exit(1);
			//printf("command not found\n");
		}
		exit(0);
	}
	if(isPresent)
	{
		return 0;
	}
	wait(&status);
	return status;
}

// This function is used for "cron" function
void execCron(char * filename){
	if(!fork()){
		FILE * fp;
		char inp[MAXLINE];
		fp = fopen(filename, "r");			// opening the file
		if(fp == NULL){
			printf("Error in opening file\n");
			exit(1);
		}
		char ** tokens;
		while(true){	
			fseek(fp, 0 , SEEK_SET);		// go to the beginning of the file	
			time_t now = time(0);
			int myTime[5];
			struct tm* tm_struct = localtime(&now);
			myTime[0] = tm_struct -> tm_min;		// storing the current min
			myTime[1] = tm_struct -> tm_hour;		// storing the current hour
			myTime[2] = tm_struct -> tm_mday;		// storing the current month day
			myTime[3] = tm_struct -> tm_mon;		// storing the current month
			myTime[4] = tm_struct -> tm_wday;		// storing the current week day		
			
			//printf("myTime[0]: %d, myTime[1]: %d, myTime[2]: %d, myTime[3]: %d, myTime[4]: %d\n", myTime[0], myTime[1], myTime[2], myTime[3], myTime[4]); 
				
			while(fgets(inp, MAXLINE, fp)!=NULL){	// reading from the file
				// now check the 				
				int check = true;
				tokens = tokenize(inp);
				int i = 0;
				for(i=0;i<5;i++){
					if(strcmp(tokens[i],"*") != 0){
						if(atoi(tokens[i]) != myTime[i]){
							check = false;				// if any of the time parameter is not equal then skip this instruction
						}
					}				
				}
				if(check){					// if the time matched completely with, then execute the command
					if(!fork()){
						if(strcmp(tokens[5],"cd") == 0){
							if(changeDirectory(&tokens[5])!=0){
								exit(1);
							}
						}
						else if(strcmp(tokens[5],"run") == 0){
							if(runCommand(&tokens[5]) != 0){
								printf("Aborting the running of bash file\n");
								exit(1);
							}
						}
						else if(strcmp(tokens[5],"cron")==0){
							if(tokens[6] != NULL && tokens[7] == NULL){
								execCron(tokens[6]);
							}
							else{
								printf("Usage:\n	cron <filename>\n");
								exit(1);
							}
						}
						else if(strcmp(tokens[5], "parallel") == 0){
							char * tempStr = strstr(inp, tokens[5]);
							parallelCommand(tempStr);		// this is also wrong
						}						
						else{
							char * tempStr = strstr(inp, tokens[5]);
							
							if(execute(tokenize(tempStr))!=0){
								exit(1);
							}
						}						
						exit(0);
					}
				}
			}
			sleep(60);
		}
		exit(0);
	}
}


// This function is used to run parallelCommand command
void parallelCommand(char * input)
{ 
	char ** token = tokenize(input); 
	int i=1,j; 
	int index = 0; 
	char * args[MAXLINE];
 	char * cmd = token[0]; 
	for(;token[i]!=NULL;i++)
 	{ 
	 	if(strcmp(token[i],":::") !=0)
	 	{
	  		args[index] = (char *)malloc(sizeof(char)*sizeof(token[i]));
	   		strcpy(args[index++],token[i]);
    	} 
    	else
		{ // execute the process and free the token 
	    	if(!fork()){
	    		if(strcmp(args[0],"cd")==0){
	    			changeDirectory(args);
	    			exit(0);
	    		}
    			else if(strcmp(args[0],"run")==0){
    				runCommand(args);
    				exit(0);
    			}
    			// here add other features as well, like cron, parallelCommand
				else if(strcmp(args[0],"cron")==0){
					if(args[1] != NULL && args[2] == NULL){
						execCron(args[1]);
						exit(0);
					}
					else{
						printf("Usage:\n	cron <filename>\n");
						exit(1);
					}
				}
				else if(strcmp(args[0], "parallel") == 0){
					//parallelCommand(input);
					printf("Parallel inside parallel is not allowed\n");
					exit(1);
				}
	    		else{
	    			if(execute(args)!=0){
		    			exit(1);
	    			}
	    			exit(0);
	    		}
	    	}
	    	else {
	    		for(j=0;j<=index;j++)	
    			{ 
    				free(args[j]); 
				} 
	    		index=0; 
	    	} 
    	}
	} 
	if(!fork()){
		if(strcmp(args[0],"cd")==0){
			changeDirectory(args);
			exit(0);
		}
		else if(strcmp(args[0],"run")==0){
			runCommand(args);
			exit(0);
		}
		// here add other features as well, like cron, parallelCommand
		else if(strcmp(args[0],"cron")==0){
			if(args[1] != NULL && args[2] == NULL){
				execCron(args[1]);
				exit(0);
			}
			else{
				printf("Usage:\n	cron <filename>\n");
				exit(1);
			}
		}
		else if(strcmp(args[0], "parallel") == 0){
			printf("Parallel inside parallel is not allowed\n");
			exit(1);
		}
		else{
			execute(args);
			exit(0);
		}
	}
	for(j=0;j<=index;j++)	
	{ 
		free(args[j]); 
	}
}

/*the tokenizer function takes a string of chars and forms tokens out of it*/
char ** tokenize(char* input){
	int i;
	int doubleQuotes = 0;
	
	char *token = (char *)malloc(1000*sizeof(char));
	int tokenIndex = 0;

	char **tokens;
	tokens = (char **) malloc(MAXLINE*sizeof(char**));
 
	int tokenNo = 0;
	
	for(i =0; i < strlen(input); i++){
		char readChar = input[i];
		
		if (readChar == '"'){
			doubleQuotes = (doubleQuotes + 1) % 2;
			if (doubleQuotes == 0){
				token[tokenIndex] = '\0';
				if (tokenIndex != 0){
					tokens[tokenNo] = (char*)malloc(sizeof(token));
					strcpy(tokens[tokenNo++], token);
					tokenIndex = 0; 
				}
			}
		}
		else if (doubleQuotes == 1){
			token[tokenIndex++] = readChar;
		}
		else if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
			token[tokenIndex] = '\0';
			if (tokenIndex != 0){
				tokens[tokenNo] = (char*)malloc(sizeof(token));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0; 
			}
		}
		else{
			token[tokenIndex++] = readChar;
		}
	}
	
	if (doubleQuotes == 1){
		token[tokenIndex] = '\0';
		if (tokenIndex != 0){
			tokens[tokenNo] = (char*)malloc(sizeof(token));
			strcpy(tokens[tokenNo++], token);
		}
	}
	
	return tokens;
}

