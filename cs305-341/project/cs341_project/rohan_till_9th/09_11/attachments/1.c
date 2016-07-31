#pragma check_stack(off)

#include <string.h>
#include <stdio.h> 

void foo()
{
    char buf[10];
    buf[0]='a';
    printf("Buffer starts from:%p\n",buf);
    //printf("My stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n\n");
    //strcpy(buf, input);
    scanf("%s",buf);
    printf("%s\n", buf);

    //printf("Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n%p\n\n\n");
}

void bar(void)
{
    printf("Augh! I've been hacked!\n");
}

int main()
{
    //Blatant cheating to make life easier on myself
    printf("Address of foo = %p\n", foo);
    //printf("sdfsfsf");
    printf("Address of bar = %p\n", bar);
   /* if (argc != 2) 
	{
        printf("Please supply a string as an argument!\n");
        return -1;
	} 
*/
	foo();
    return 0;
}
