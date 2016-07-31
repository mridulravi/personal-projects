		.data		
		
		.text
		.global	main
main:
		lw 	r1, 0(r0)
		lw 	r2, 0(r0)
		add 	r3, r1, r2
		sw 	0(r6), r3
		lw	r4, 0(r0)
		add 	r5, r1, r4
		sw 	0(r7), r5 

Finish:		;*** end
		trap		0	
