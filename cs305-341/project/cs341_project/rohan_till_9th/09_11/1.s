	.file	"1.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"My stack looks like:\n%p\n%p\n%p\n%p\n%p\n% p\n\n"
.LC1:
	.string	"Again repeating it!"
	.align 4
.LC2:
	.string	"Now the stack looks like:\n%p\n%p\n%p\n%p\n%p\n%p\n\n"
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	$.LC1, (%esp)
	call	puts
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	strcpy
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	puts
	movl	$.LC2, %eax
	movl	%eax, (%esp)
	call	printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.section	.rodata
.LC3:
	.string	"Augh! I've been hacked!"
	.text
	.globl	bar
	.type	bar, @function
bar:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$.LC3, (%esp)
	call	puts
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	bar, .-bar
	.section	.rodata
.LC4:
	.string	"Address of foo = %p\n"
.LC5:
	.string	"Address of bar = %p\n"
	.align 4
.LC6:
	.string	"Please supply a string as an argument!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC4, %eax
	movl	$foo, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC5, %eax
	movl	$bar, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	cmpl	$2, 8(%ebp)
	je	.L4
	movl	$.LC6, (%esp)
	call	puts
	movl	$-1, %eax
	jmp	.L5
.L4:
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	foo
	movl	$0, %eax
.L5:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
