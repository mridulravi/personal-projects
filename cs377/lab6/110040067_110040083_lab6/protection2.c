#include<stdio.h>
#include<stdlib.h>
#include<sys/syscall.h>
#include "temp.h"

int main()
{
	char a[5];
	a[0] = 'A';
	a[1] = 'B';
	a[2] = 'C';
	a[3] = 'D';
	a[4] = 'E';

	syscall(403, 5, a, 10, 1);
	syscall(402, 5, a, 10, 1);
	return 0;

}
