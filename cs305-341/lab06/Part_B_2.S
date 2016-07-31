		.data		
		
		.text
		.global	main
main:
		lw 	r1, 0(r0)
		lw 	r2, 0(r0)
		lw	r4, 0(r0)
		lw	r5, 0(r0)
		lw	r6, 0(r0)
		lw	r7, 0(r0)
		lw 	r3, 0(r0)
		add 	r5, r3, r4
		sw 	0(r6), r3
		;sw 	0(r7), r5 

Finish:		;*** end
		trap		0	
