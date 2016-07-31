// take input and change the return address to another function


#include<stdio.h>
#include<string.h>


void foo(char * input){
	char a[10];
	a[0] = 'a';
	//scanf("%s",a);
	strcpy(a,input);
	/*
	
	*/
}

void bar(){
	printf("I am hacked\n");
}

int main(int argc, char *argv[]){

	printf("the address of bar is %p\n",bar);
	foo(argv[1]);
	return 0;
}


// Observations
/*
1) pass the address of the function to be called as hex digits using perl script in reverse order
2) see the assembly code to determine the position of the return address relative to the char array
3) we are unable to determine why there is no seg fault -- after foo (we think when ret is called from bar, control goes to the address location which stores the input string.This is a valid address, hence no seg fault. But why exit from program?

check the exit status of the last process using "echo $?" 
Now, when program will try to execute the data at that location (thinking it is an instruction), it will face problem. Hence it exits with status 139 (which means memory access bug in our code)

-->    exit code 139 (people say this means memory fragmentation)

No, it means that your program died with signal 11 (SIGSEGV on Linux and most other UNIXes), also known as segmentation fault.

-->    Could anybody tell me why the run fails but debug doesn't?

Your program exhibits undefined behavior, and can do anything (that includes appearing to work correctly sometimes).

link:- http://stackoverflow.com/questions/15600296/counter-exit-code-139-when-running-but-gdb-make-it-through


*/





