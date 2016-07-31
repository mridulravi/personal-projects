#include <string.h>
#include <stdio.h> 

void foo(const char* input)
{
    char buf[10];
    buf[0]='a';
    strcpy(buf, input);
}

void bar(void)
{
    printf("Augh! I've been hacked!\n");
}

int main(int argc, char* argv[])
{
    printf("Address of bar = %p\n", bar);
    if (argc != 2) 
	{
        printf("Please supply a string as an argument!\n");
        return -1;
	} 
	foo(argv[1]);
    return 0;
}
