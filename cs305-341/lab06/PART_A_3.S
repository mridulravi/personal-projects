		.data		
		
		.text
		.global	main
main:
		addf 	f3, f1, f2
		subf 	f5, f3, f1
		addf 	f6, f5, f3
		addf 	f7, f6, f5
		subf 	f8, f6, f7
		subf 	f9, f8, f7
		movf 	f10, f9
		addf 	f11, f10, f9
		addf 	f12, f11, f10
		subf 	f13, f12, f11

Finish:		
		trap		0	
