#include<stdio.h>

char shellcode[] = "\x31\xdb\x89\xd8\x40\xcd";

void func() {
   int *ret;

   ret = (int)&ret + 8;
   (*ret) = (int)shellcode;
   //(*ret) = (*ret) + 12;

}

void main(){
	func();
	printf("in main after func\n");
	printf("skipped 1 instruction\n");
}

