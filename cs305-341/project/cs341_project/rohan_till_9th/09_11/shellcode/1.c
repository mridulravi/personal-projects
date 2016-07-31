#pragma check_stack(off)

#include <string.h>
#include <stdio.h> 

void foo(const char* input)
{
    char buf[90];
    printf("Buffer starts from:%p\n",buf);
    printf("My stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
    strcpy(buf, input);
    printf("%s\n", buf);

    printf("Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n\n\n");
}

void bar(void)
{
    printf("Augh! I've been hacked!\n");
}

int main(int argc, char* argv[])
{
    //Blatant cheating to make life easier on myself
    int i=0;
    printf("Address of foo = %p\n", foo);
    printf("Address of bar = %p\n", bar);
    printf("%d\n",argc);
    for(;i<argc;i++)
    printf("%x\n",argv[i]);
    
    if (argc < 2) 
	{
        printf("Please supply a string as an argument!\n");
        return -1;
	} 
	foo(argv[1]);
    return 0;
}
