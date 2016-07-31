	.file	"code2.c"
	.text
	.globl	foo
	.type	foo, @function
foo:
	pushl	%ebp
	
	movl	%esp, %ebp
	subl	$40, %esp
	movb	$97, -18(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	strcpy
	leave
	ret
	.size	foo, .-foo
	.section	.rodata
.LC0:
	.string	"I am hacked"
	.text
	.globl	bar
	.type	bar, @function
bar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$.LC0, (%esp)
	call	puts
	leave
	ret
	.size	bar, .-bar
	.section	.rodata
.LC1:
	.string	"the address of bar is %p\n"
.LC2:
	.string	"Checking main"
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC1, %eax
	movl	$bar, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	foo
	movl	$.LC2, (%esp)
	call	puts
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
