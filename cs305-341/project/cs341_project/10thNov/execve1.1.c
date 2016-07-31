#include<stdio.h>
int main(){
	char* name[1];
	name[0] = "/bin/sh";
	//name[1] = NULL;
	execve(name[0], NULL, NULL);
	return 0;
	
}
