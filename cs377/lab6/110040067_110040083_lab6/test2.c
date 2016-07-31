#include<stdio.h>
#include<stdlib.h>
#include<sys/syscall.h>

int main()
{

	int i=0;
	long int j;
	syscall(401, 233);
	for(;i<1000;i++)
	{
		j = i*i;
	}

	printf("test2 completing execution\n");

	return 0;
}
