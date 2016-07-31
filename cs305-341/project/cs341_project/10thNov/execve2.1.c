void main(){
__asm__(
"xorl   %ebx,%ebx;"
"movl   %ebx,%eax;"
"inc %ebx;"
"inc    %eax;"
"int    $0x80;"
);
}


//inc %ebx makes exit status 1

