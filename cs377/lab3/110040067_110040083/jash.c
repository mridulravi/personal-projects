#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include<time.h>

#define MAXLINE 1000
#define DEBUG 0
#define true 1
#define false 0

//declarations
char ** tokenize(char*);
int execute(char ** tokens);
int runCommand(char ** tokens);
int changeDirectory(char ** tokens);
void execCron(char * filename);
void parallelCommand(char * input);
int ppid;


// handler to handle the SIGINT signal 
// will exit the process if it is a child process, for parent process(original jash process ), it will print a $ on a new line 
void handler(int num){
	// this should happen for child process only
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
			//exit(0);
		}

		//add the command to the command list.
		cmds[numCmds] = (char *)malloc(sizeof(input));
		strcpy(cmds[numCmds++], input); 

		// Calling the tokenizer function on the input line   
		tokens = tokenize(input);	
		if(tokens[0] == NULL){
			continue;
		}

		if(strcmp(tokens[0],"cd") == 0){
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
		else if(strcmp(myTokens[0], "parallelCommand") == 0){
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
	int status, pid = fork();
	if(pid == 0){
		// now i have to run the commands, they are in tokens array

		if(execvp(tokens[0], tokens) == -1){
			perror("execvp:");
			exit(1);
			//printf("command not found\n");
		}
		exit(0);
	}
	wait(&status);
	return status;
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
						//	printf("In cd of cron\n");
						//	fflush(stdout);
							if(changeDirectory(&tokens[5])!=0){
								exit(1);
							}
						}
						else if(strcmp(tokens[5],"run") == 0){
						//	printf("In run of cron\n");
						//	fflush(stdout);
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
						else if(strcmp(tokens[5], "parallelCommand") == 0){
							parallelCommand(inp);
						}						
						else{
							if(execute(&tokens[5])!=0){
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
		    		else{
		    			execute(args);
		    			exit(0);
		    		}
		    	}
		    	else {
		    		for(j=0;j<=index;j++)	
		    			{ free(args[j]); }; 
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
	    		else{
	    			execute(args);
	    			exit(0);
	    		}
	    	}
}

