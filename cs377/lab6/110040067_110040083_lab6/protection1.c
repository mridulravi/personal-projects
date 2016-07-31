#include<stdio.h>
#include<stdlib.h>
#include<sys/syscall.h>
#include "temp.h"

int main()
{
	char a[5];
	a[0] = 'a';
	a[1] = 'b';
	a[2] = 'c';
	a[3] = 'd';
	a[4] = 'e';

	syscall(403, 5, a, 10, 1);
	syscall(402, 5, a, 10, 1);
	return 0;

}
