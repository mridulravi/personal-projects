;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (MINGW64)
; This file was generated Tue Feb 03 20:12:02 2015
;--------------------------------------------------------
	.module asgn2_3
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _findButtonPress
	.globl _updateDisplay
	.globl _display
	.globl _setSegment
	.globl _t0Delay56ms
	.globl _t0Delay
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _FL
	.globl _P
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _T2CON_7
	.globl _T2CON_6
	.globl _T2CON_5
	.globl _T2CON_4
	.globl _T2CON_3
	.globl _T2CON_2
	.globl _T2CON_1
	.globl _T2CON_0
	.globl _PT2
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ET2
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _T2EX
	.globl _T2
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _B
	.globl _A
	.globl _ACC
	.globl _PSW
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2MOD
	.globl _T2CON
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _fourth
	.globl _third
	.globl _second
	.globl _first
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
G$P0$0$0 == 0x0080
_P0	=	0x0080
G$SP$0$0 == 0x0081
_SP	=	0x0081
G$DPL$0$0 == 0x0082
_DPL	=	0x0082
G$DPH$0$0 == 0x0083
_DPH	=	0x0083
G$PCON$0$0 == 0x0087
_PCON	=	0x0087
G$TCON$0$0 == 0x0088
_TCON	=	0x0088
G$TMOD$0$0 == 0x0089
_TMOD	=	0x0089
G$TL0$0$0 == 0x008a
_TL0	=	0x008a
G$TL1$0$0 == 0x008b
_TL1	=	0x008b
G$TH0$0$0 == 0x008c
_TH0	=	0x008c
G$TH1$0$0 == 0x008d
_TH1	=	0x008d
G$P1$0$0 == 0x0090
_P1	=	0x0090
G$SCON$0$0 == 0x0098
_SCON	=	0x0098
G$SBUF$0$0 == 0x0099
_SBUF	=	0x0099
G$P2$0$0 == 0x00a0
_P2	=	0x00a0
G$IE$0$0 == 0x00a8
_IE	=	0x00a8
G$P3$0$0 == 0x00b0
_P3	=	0x00b0
G$IP$0$0 == 0x00b8
_IP	=	0x00b8
G$T2CON$0$0 == 0x00c8
_T2CON	=	0x00c8
G$T2MOD$0$0 == 0x00c9
_T2MOD	=	0x00c9
G$RCAP2L$0$0 == 0x00ca
_RCAP2L	=	0x00ca
G$RCAP2H$0$0 == 0x00cb
_RCAP2H	=	0x00cb
G$TL2$0$0 == 0x00cc
_TL2	=	0x00cc
G$TH2$0$0 == 0x00cd
_TH2	=	0x00cd
G$PSW$0$0 == 0x00d0
_PSW	=	0x00d0
G$ACC$0$0 == 0x00e0
_ACC	=	0x00e0
G$A$0$0 == 0x00e0
_A	=	0x00e0
G$B$0$0 == 0x00f0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
G$P0_0$0$0 == 0x0080
_P0_0	=	0x0080
G$P0_1$0$0 == 0x0081
_P0_1	=	0x0081
G$P0_2$0$0 == 0x0082
_P0_2	=	0x0082
G$P0_3$0$0 == 0x0083
_P0_3	=	0x0083
G$P0_4$0$0 == 0x0084
_P0_4	=	0x0084
G$P0_5$0$0 == 0x0085
_P0_5	=	0x0085
G$P0_6$0$0 == 0x0086
_P0_6	=	0x0086
G$P0_7$0$0 == 0x0087
_P0_7	=	0x0087
G$IT0$0$0 == 0x0088
_IT0	=	0x0088
G$IE0$0$0 == 0x0089
_IE0	=	0x0089
G$IT1$0$0 == 0x008a
_IT1	=	0x008a
G$IE1$0$0 == 0x008b
_IE1	=	0x008b
G$TR0$0$0 == 0x008c
_TR0	=	0x008c
G$TF0$0$0 == 0x008d
_TF0	=	0x008d
G$TR1$0$0 == 0x008e
_TR1	=	0x008e
G$TF1$0$0 == 0x008f
_TF1	=	0x008f
G$P1_0$0$0 == 0x0090
_P1_0	=	0x0090
G$P1_1$0$0 == 0x0091
_P1_1	=	0x0091
G$P1_2$0$0 == 0x0092
_P1_2	=	0x0092
G$P1_3$0$0 == 0x0093
_P1_3	=	0x0093
G$P1_4$0$0 == 0x0094
_P1_4	=	0x0094
G$P1_5$0$0 == 0x0095
_P1_5	=	0x0095
G$P1_6$0$0 == 0x0096
_P1_6	=	0x0096
G$P1_7$0$0 == 0x0097
_P1_7	=	0x0097
G$T2$0$0 == 0x0090
_T2	=	0x0090
G$T2EX$0$0 == 0x0091
_T2EX	=	0x0091
G$RI$0$0 == 0x0098
_RI	=	0x0098
G$TI$0$0 == 0x0099
_TI	=	0x0099
G$RB8$0$0 == 0x009a
_RB8	=	0x009a
G$TB8$0$0 == 0x009b
_TB8	=	0x009b
G$REN$0$0 == 0x009c
_REN	=	0x009c
G$SM2$0$0 == 0x009d
_SM2	=	0x009d
G$SM1$0$0 == 0x009e
_SM1	=	0x009e
G$SM0$0$0 == 0x009f
_SM0	=	0x009f
G$P2_0$0$0 == 0x00a0
_P2_0	=	0x00a0
G$P2_1$0$0 == 0x00a1
_P2_1	=	0x00a1
G$P2_2$0$0 == 0x00a2
_P2_2	=	0x00a2
G$P2_3$0$0 == 0x00a3
_P2_3	=	0x00a3
G$P2_4$0$0 == 0x00a4
_P2_4	=	0x00a4
G$P2_5$0$0 == 0x00a5
_P2_5	=	0x00a5
G$P2_6$0$0 == 0x00a6
_P2_6	=	0x00a6
G$P2_7$0$0 == 0x00a7
_P2_7	=	0x00a7
G$EX0$0$0 == 0x00a8
_EX0	=	0x00a8
G$ET0$0$0 == 0x00a9
_ET0	=	0x00a9
G$EX1$0$0 == 0x00aa
_EX1	=	0x00aa
G$ET1$0$0 == 0x00ab
_ET1	=	0x00ab
G$ES$0$0 == 0x00ac
_ES	=	0x00ac
G$ET2$0$0 == 0x00ad
_ET2	=	0x00ad
G$EA$0$0 == 0x00af
_EA	=	0x00af
G$P3_0$0$0 == 0x00b0
_P3_0	=	0x00b0
G$P3_1$0$0 == 0x00b1
_P3_1	=	0x00b1
G$P3_2$0$0 == 0x00b2
_P3_2	=	0x00b2
G$P3_3$0$0 == 0x00b3
_P3_3	=	0x00b3
G$P3_4$0$0 == 0x00b4
_P3_4	=	0x00b4
G$P3_5$0$0 == 0x00b5
_P3_5	=	0x00b5
G$P3_6$0$0 == 0x00b6
_P3_6	=	0x00b6
G$P3_7$0$0 == 0x00b7
_P3_7	=	0x00b7
G$RXD$0$0 == 0x00b0
_RXD	=	0x00b0
G$TXD$0$0 == 0x00b1
_TXD	=	0x00b1
G$INT0$0$0 == 0x00b2
_INT0	=	0x00b2
G$INT1$0$0 == 0x00b3
_INT1	=	0x00b3
G$T0$0$0 == 0x00b4
_T0	=	0x00b4
G$T1$0$0 == 0x00b5
_T1	=	0x00b5
G$WR$0$0 == 0x00b6
_WR	=	0x00b6
G$RD$0$0 == 0x00b7
_RD	=	0x00b7
G$PX0$0$0 == 0x00b8
_PX0	=	0x00b8
G$PT0$0$0 == 0x00b9
_PT0	=	0x00b9
G$PX1$0$0 == 0x00ba
_PX1	=	0x00ba
G$PT1$0$0 == 0x00bb
_PT1	=	0x00bb
G$PS$0$0 == 0x00bc
_PS	=	0x00bc
G$PT2$0$0 == 0x00bd
_PT2	=	0x00bd
G$T2CON_0$0$0 == 0x00c8
_T2CON_0	=	0x00c8
G$T2CON_1$0$0 == 0x00c9
_T2CON_1	=	0x00c9
G$T2CON_2$0$0 == 0x00ca
_T2CON_2	=	0x00ca
G$T2CON_3$0$0 == 0x00cb
_T2CON_3	=	0x00cb
G$T2CON_4$0$0 == 0x00cc
_T2CON_4	=	0x00cc
G$T2CON_5$0$0 == 0x00cd
_T2CON_5	=	0x00cd
G$T2CON_6$0$0 == 0x00ce
_T2CON_6	=	0x00ce
G$T2CON_7$0$0 == 0x00cf
_T2CON_7	=	0x00cf
G$CP_RL2$0$0 == 0x00c8
_CP_RL2	=	0x00c8
G$C_T2$0$0 == 0x00c9
_C_T2	=	0x00c9
G$TR2$0$0 == 0x00ca
_TR2	=	0x00ca
G$EXEN2$0$0 == 0x00cb
_EXEN2	=	0x00cb
G$TCLK$0$0 == 0x00cc
_TCLK	=	0x00cc
G$RCLK$0$0 == 0x00cd
_RCLK	=	0x00cd
G$EXF2$0$0 == 0x00ce
_EXF2	=	0x00ce
G$TF2$0$0 == 0x00cf
_TF2	=	0x00cf
G$P$0$0 == 0x00d0
_P	=	0x00d0
G$FL$0$0 == 0x00d1
_FL	=	0x00d1
G$OV$0$0 == 0x00d2
_OV	=	0x00d2
G$RS0$0$0 == 0x00d3
_RS0	=	0x00d3
G$RS1$0$0 == 0x00d4
_RS1	=	0x00d4
G$F0$0$0 == 0x00d5
_F0	=	0x00d5
G$AC$0$0 == 0x00d6
_AC	=	0x00d6
G$CY$0$0 == 0x00d7
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
G$first$0$0==.
_first::
	.ds 2
G$second$0$0==.
_second::
	.ds 2
G$third$0$0==.
_third::
	.ds 2
G$fourth$0$0==.
_fourth::
	.ds 2
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
	C$asgn2_3.c$4$1$45 ==.
;	asgn2_3.c:4: int first=1,second=2,third=3,fourth=4;
	mov	_first,#0x01
	mov	(_first + 1),#0x00
	C$asgn2_3.c$4$1$45 ==.
;	asgn2_3.c:4: 
	mov	_second,#0x02
	mov	(_second + 1),#0x00
	C$asgn2_3.c$4$1$45 ==.
;	asgn2_3.c:4: int first=1,second=2,third=3,fourth=4;
	mov	_third,#0x03
	mov	(_third + 1),#0x00
	C$asgn2_3.c$4$1$45 ==.
;	asgn2_3.c:4: 
	mov	_fourth,#0x04
	mov	(_fourth + 1),#0x00
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 't0Delay'
;------------------------------------------------------------
	G$t0Delay$0$0 ==.
	C$asgn2_3.c$7$0$0 ==.
;	asgn2_3.c:7: void t0Delay()
;	-----------------------------------------
;	 function t0Delay
;	-----------------------------------------
_t0Delay:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	C$asgn2_3.c$9$1$1 ==.
;	asgn2_3.c:9: TMOD=0x01;
	mov	_TMOD,#0x01
	C$asgn2_3.c$10$1$1 ==.
;	asgn2_3.c:10: TL0=0x00;
	mov	_TL0,#0x00
	C$asgn2_3.c$11$1$1 ==.
;	asgn2_3.c:11: TH0=0xF5;
	mov	_TH0,#0xF5
	C$asgn2_3.c$12$1$1 ==.
;	asgn2_3.c:12: TR0=1;
	setb	_TR0
	C$asgn2_3.c$13$1$1 ==.
;	asgn2_3.c:13: while(	TF0==0 );
00101$:
	jnb	_TF0,00101$
	C$asgn2_3.c$14$1$1 ==.
;	asgn2_3.c:14: TR0=0;
	clr	_TR0
	C$asgn2_3.c$15$1$1 ==.
;	asgn2_3.c:15: TF0=0;
	clr	_TF0
	C$asgn2_3.c$16$1$1 ==.
	XG$t0Delay$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 't0Delay56ms'
;------------------------------------------------------------
	G$t0Delay56ms$0$0 ==.
	C$asgn2_3.c$19$1$1 ==.
;	asgn2_3.c:19: void t0Delay56ms(void)
;	-----------------------------------------
;	 function t0Delay56ms
;	-----------------------------------------
_t0Delay56ms:
	C$asgn2_3.c$21$1$3 ==.
;	asgn2_3.c:21: TMOD=0x01;
	mov	_TMOD,#0x01
	C$asgn2_3.c$22$1$3 ==.
;	asgn2_3.c:22: TL0=0x00;
	mov	_TL0,#0x00
	C$asgn2_3.c$23$1$3 ==.
;	asgn2_3.c:23: TH0=0x35;
	mov	_TH0,#0x35
	C$asgn2_3.c$24$1$3 ==.
;	asgn2_3.c:24: TR0=1;
	setb	_TR0
	C$asgn2_3.c$25$1$3 ==.
;	asgn2_3.c:25: while(	TF0==0 );
00101$:
	jnb	_TF0,00101$
	C$asgn2_3.c$26$1$3 ==.
;	asgn2_3.c:26: TR0=0;
	clr	_TR0
	C$asgn2_3.c$27$1$3 ==.
;	asgn2_3.c:27: TF0=0;	
	clr	_TF0
	C$asgn2_3.c$28$1$3 ==.
	XG$t0Delay56ms$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'setSegment'
;------------------------------------------------------------
;x                         Allocated to registers r6 r7 
;------------------------------------------------------------
	G$setSegment$0$0 ==.
	C$asgn2_3.c$32$1$3 ==.
;	asgn2_3.c:32: void setSegment(int x)
;	-----------------------------------------
;	 function setSegment
;	-----------------------------------------
_setSegment:
	mov	r6,dpl
	mov	r7,dph
	C$asgn2_3.c$34$1$5 ==.
;	asgn2_3.c:34: if(x==0)
	mov	a,r6
	orl	a,r7
	jnz	00146$
	C$asgn2_3.c$36$2$6 ==.
;	asgn2_3.c:36: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$37$2$6 ==.
;	asgn2_3.c:37: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$38$2$6 ==.
;	asgn2_3.c:38: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$39$2$6 ==.
;	asgn2_3.c:39: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$40$2$6 ==.
;	asgn2_3.c:40: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$41$2$6 ==.
;	asgn2_3.c:41: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$42$2$6 ==.
;	asgn2_3.c:42: P0_6=1;
	setb	_P0_6
	ljmp	00148$
00146$:
	C$asgn2_3.c$44$1$5 ==.
;	asgn2_3.c:44: else if(x==1)
	cjne	r6,#0x01,00143$
	cjne	r7,#0x00,00143$
	C$asgn2_3.c$46$2$7 ==.
;	asgn2_3.c:46: P0_0=1;
	setb	_P0_0
	C$asgn2_3.c$47$2$7 ==.
;	asgn2_3.c:47: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$48$2$7 ==.
;	asgn2_3.c:48: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$49$2$7 ==.
;	asgn2_3.c:49: P0_3=1;
	setb	_P0_3
	C$asgn2_3.c$50$2$7 ==.
;	asgn2_3.c:50: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$51$2$7 ==.
;	asgn2_3.c:51: P0_5=1;
	setb	_P0_5
	C$asgn2_3.c$52$2$7 ==.
;	asgn2_3.c:52: P0_6=1;
	setb	_P0_6
	ljmp	00148$
00143$:
	C$asgn2_3.c$54$1$5 ==.
;	asgn2_3.c:54: else if(x==2)
	cjne	r6,#0x02,00140$
	cjne	r7,#0x00,00140$
	C$asgn2_3.c$56$2$8 ==.
;	asgn2_3.c:56: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$57$2$8 ==.
;	asgn2_3.c:57: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$58$2$8 ==.
;	asgn2_3.c:58: P0_2=1;
	setb	_P0_2
	C$asgn2_3.c$59$2$8 ==.
;	asgn2_3.c:59: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$60$2$8 ==.
;	asgn2_3.c:60: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$61$2$8 ==.
;	asgn2_3.c:61: P0_5=1;
	setb	_P0_5
	C$asgn2_3.c$62$2$8 ==.
;	asgn2_3.c:62: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00140$:
	C$asgn2_3.c$64$1$5 ==.
;	asgn2_3.c:64: else if(x==3)
	cjne	r6,#0x03,00137$
	cjne	r7,#0x00,00137$
	C$asgn2_3.c$66$2$9 ==.
;	asgn2_3.c:66: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$67$2$9 ==.
;	asgn2_3.c:67: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$68$2$9 ==.
;	asgn2_3.c:68: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$69$2$9 ==.
;	asgn2_3.c:69: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$70$2$9 ==.
;	asgn2_3.c:70: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$71$2$9 ==.
;	asgn2_3.c:71: P0_5=1;
	setb	_P0_5
	C$asgn2_3.c$72$2$9 ==.
;	asgn2_3.c:72: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00137$:
	C$asgn2_3.c$74$1$5 ==.
;	asgn2_3.c:74: else if(x==4)
	cjne	r6,#0x04,00134$
	cjne	r7,#0x00,00134$
	C$asgn2_3.c$76$2$10 ==.
;	asgn2_3.c:76: P0_0=1;
	setb	_P0_0
	C$asgn2_3.c$77$2$10 ==.
;	asgn2_3.c:77: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$78$2$10 ==.
;	asgn2_3.c:78: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$79$2$10 ==.
;	asgn2_3.c:79: P0_3=1;
	setb	_P0_3
	C$asgn2_3.c$80$2$10 ==.
;	asgn2_3.c:80: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$81$2$10 ==.
;	asgn2_3.c:81: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$82$2$10 ==.
;	asgn2_3.c:82: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00134$:
	C$asgn2_3.c$84$1$5 ==.
;	asgn2_3.c:84: else if(x==5)
	cjne	r6,#0x05,00131$
	cjne	r7,#0x00,00131$
	C$asgn2_3.c$86$2$11 ==.
;	asgn2_3.c:86: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$87$2$11 ==.
;	asgn2_3.c:87: P0_1=1;
	setb	_P0_1
	C$asgn2_3.c$88$2$11 ==.
;	asgn2_3.c:88: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$89$2$11 ==.
;	asgn2_3.c:89: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$90$2$11 ==.
;	asgn2_3.c:90: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$91$2$11 ==.
;	asgn2_3.c:91: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$92$2$11 ==.
;	asgn2_3.c:92: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00131$:
	C$asgn2_3.c$94$1$5 ==.
;	asgn2_3.c:94: else if(x==6)
	cjne	r6,#0x06,00128$
	cjne	r7,#0x00,00128$
	C$asgn2_3.c$96$2$12 ==.
;	asgn2_3.c:96: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$97$2$12 ==.
;	asgn2_3.c:97: P0_1=1;
	setb	_P0_1
	C$asgn2_3.c$98$2$12 ==.
;	asgn2_3.c:98: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$99$2$12 ==.
;	asgn2_3.c:99: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$100$2$12 ==.
;	asgn2_3.c:100: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$101$2$12 ==.
;	asgn2_3.c:101: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$102$2$12 ==.
;	asgn2_3.c:102: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00128$:
	C$asgn2_3.c$104$1$5 ==.
;	asgn2_3.c:104: else if(x==7)
	cjne	r6,#0x07,00125$
	cjne	r7,#0x00,00125$
	C$asgn2_3.c$106$2$13 ==.
;	asgn2_3.c:106: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$107$2$13 ==.
;	asgn2_3.c:107: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$108$2$13 ==.
;	asgn2_3.c:108: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$109$2$13 ==.
;	asgn2_3.c:109: P0_3=1;
	setb	_P0_3
	C$asgn2_3.c$110$2$13 ==.
;	asgn2_3.c:110: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$111$2$13 ==.
;	asgn2_3.c:111: P0_5=1;
	setb	_P0_5
	C$asgn2_3.c$112$2$13 ==.
;	asgn2_3.c:112: P0_6=1;
	setb	_P0_6
	ljmp	00148$
00125$:
	C$asgn2_3.c$114$1$5 ==.
;	asgn2_3.c:114: else if(x==8)
	cjne	r6,#0x08,00122$
	cjne	r7,#0x00,00122$
	C$asgn2_3.c$116$2$14 ==.
;	asgn2_3.c:116: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$117$2$14 ==.
;	asgn2_3.c:117: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$118$2$14 ==.
;	asgn2_3.c:118: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$119$2$14 ==.
;	asgn2_3.c:119: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$120$2$14 ==.
;	asgn2_3.c:120: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$121$2$14 ==.
;	asgn2_3.c:121: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$122$2$14 ==.
;	asgn2_3.c:122: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00122$:
	C$asgn2_3.c$124$1$5 ==.
;	asgn2_3.c:124: else if(x==9)
	cjne	r6,#0x09,00119$
	cjne	r7,#0x00,00119$
	C$asgn2_3.c$126$2$15 ==.
;	asgn2_3.c:126: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$127$2$15 ==.
;	asgn2_3.c:127: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$128$2$15 ==.
;	asgn2_3.c:128: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$129$2$15 ==.
;	asgn2_3.c:129: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$130$2$15 ==.
;	asgn2_3.c:130: P0_4=1;
	setb	_P0_4
	C$asgn2_3.c$131$2$15 ==.
;	asgn2_3.c:131: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$132$2$15 ==.
;	asgn2_3.c:132: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00119$:
	C$asgn2_3.c$134$1$5 ==.
;	asgn2_3.c:134: else if(x==10)//A
	cjne	r6,#0x0A,00116$
	cjne	r7,#0x00,00116$
	C$asgn2_3.c$136$2$16 ==.
;	asgn2_3.c:136: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$137$2$16 ==.
;	asgn2_3.c:137: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$138$2$16 ==.
;	asgn2_3.c:138: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$139$2$16 ==.
;	asgn2_3.c:139: P0_3=1;
	setb	_P0_3
	C$asgn2_3.c$140$2$16 ==.
;	asgn2_3.c:140: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$141$2$16 ==.
;	asgn2_3.c:141: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$142$2$16 ==.
;	asgn2_3.c:142: P0_6=0;
	clr	_P0_6
	ljmp	00148$
00116$:
	C$asgn2_3.c$144$1$5 ==.
;	asgn2_3.c:144: else if(x==11)//B
	cjne	r6,#0x0B,00113$
	cjne	r7,#0x00,00113$
	C$asgn2_3.c$146$2$17 ==.
;	asgn2_3.c:146: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$147$2$17 ==.
;	asgn2_3.c:147: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$148$2$17 ==.
;	asgn2_3.c:148: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$149$2$17 ==.
;	asgn2_3.c:149: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$150$2$17 ==.
;	asgn2_3.c:150: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$151$2$17 ==.
;	asgn2_3.c:151: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$152$2$17 ==.
;	asgn2_3.c:152: P0_6=0;
	clr	_P0_6
	sjmp	00148$
00113$:
	C$asgn2_3.c$154$1$5 ==.
;	asgn2_3.c:154: else if(x==12)//C
	cjne	r6,#0x0C,00110$
	cjne	r7,#0x00,00110$
	C$asgn2_3.c$156$2$18 ==.
;	asgn2_3.c:156: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$157$2$18 ==.
;	asgn2_3.c:157: P0_1=1;
	setb	_P0_1
	C$asgn2_3.c$158$2$18 ==.
;	asgn2_3.c:158: P0_2=1;
	setb	_P0_2
	C$asgn2_3.c$159$2$18 ==.
;	asgn2_3.c:159: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$160$2$18 ==.
;	asgn2_3.c:160: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$161$2$18 ==.
;	asgn2_3.c:161: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$162$2$18 ==.
;	asgn2_3.c:162: P0_6=1;
	setb	_P0_6
	sjmp	00148$
00110$:
	C$asgn2_3.c$164$1$5 ==.
;	asgn2_3.c:164: else if(x==13)//D
	cjne	r6,#0x0D,00107$
	cjne	r7,#0x00,00107$
	C$asgn2_3.c$166$2$19 ==.
;	asgn2_3.c:166: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$167$2$19 ==.
;	asgn2_3.c:167: P0_1=0;
	clr	_P0_1
	C$asgn2_3.c$168$2$19 ==.
;	asgn2_3.c:168: P0_2=0;
	clr	_P0_2
	C$asgn2_3.c$169$2$19 ==.
;	asgn2_3.c:169: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$170$2$19 ==.
;	asgn2_3.c:170: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$171$2$19 ==.
;	asgn2_3.c:171: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$172$2$19 ==.
;	asgn2_3.c:172: P0_6=1;
	setb	_P0_6
	sjmp	00148$
00107$:
	C$asgn2_3.c$174$1$5 ==.
;	asgn2_3.c:174: else if(x==14)//E
	cjne	r6,#0x0E,00104$
	cjne	r7,#0x00,00104$
	C$asgn2_3.c$176$2$20 ==.
;	asgn2_3.c:176: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$177$2$20 ==.
;	asgn2_3.c:177: P0_1=1;
	setb	_P0_1
	C$asgn2_3.c$178$2$20 ==.
;	asgn2_3.c:178: P0_2=1;
	setb	_P0_2
	C$asgn2_3.c$179$2$20 ==.
;	asgn2_3.c:179: P0_3=0;
	clr	_P0_3
	C$asgn2_3.c$180$2$20 ==.
;	asgn2_3.c:180: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$181$2$20 ==.
;	asgn2_3.c:181: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$182$2$20 ==.
;	asgn2_3.c:182: P0_6=0;
	clr	_P0_6
	sjmp	00148$
00104$:
	C$asgn2_3.c$184$1$5 ==.
;	asgn2_3.c:184: else if(x==15)//F
	cjne	r6,#0x0F,00148$
	cjne	r7,#0x00,00148$
	C$asgn2_3.c$186$2$21 ==.
;	asgn2_3.c:186: P0_0=0;
	clr	_P0_0
	C$asgn2_3.c$187$2$21 ==.
;	asgn2_3.c:187: P0_1=1;
	setb	_P0_1
	C$asgn2_3.c$188$2$21 ==.
;	asgn2_3.c:188: P0_2=1;
	setb	_P0_2
	C$asgn2_3.c$189$2$21 ==.
;	asgn2_3.c:189: P0_3=1;
	setb	_P0_3
	C$asgn2_3.c$190$2$21 ==.
;	asgn2_3.c:190: P0_4=0;
	clr	_P0_4
	C$asgn2_3.c$191$2$21 ==.
;	asgn2_3.c:191: P0_5=0;
	clr	_P0_5
	C$asgn2_3.c$192$2$21 ==.
;	asgn2_3.c:192: P0_6=0;
	clr	_P0_6
00148$:
	C$asgn2_3.c$194$1$5 ==.
	XG$setSegment$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'display'
;------------------------------------------------------------
	G$display$0$0 ==.
	C$asgn2_3.c$197$1$5 ==.
;	asgn2_3.c:197: void display(void){
;	-----------------------------------------
;	 function display
;	-----------------------------------------
_display:
	C$asgn2_3.c$199$1$23 ==.
;	asgn2_3.c:199: P3_3=0;
	clr	_P3_3
	C$asgn2_3.c$200$1$23 ==.
;	asgn2_3.c:200: P3_2=1;
	setb	_P3_2
	C$asgn2_3.c$201$1$23 ==.
;	asgn2_3.c:201: P3_1=1;
	setb	_P3_1
	C$asgn2_3.c$202$1$23 ==.
;	asgn2_3.c:202: P3_0=1;
	setb	_P3_0
	C$asgn2_3.c$203$1$23 ==.
;	asgn2_3.c:203: setSegment(first);
	mov	dpl,_first
	mov	dph,(_first + 1)
	lcall	_setSegment
	C$asgn2_3.c$204$1$23 ==.
;	asgn2_3.c:204: t0Delay();
	lcall	_t0Delay
	C$asgn2_3.c$205$1$23 ==.
;	asgn2_3.c:205: P3_3=1;
	setb	_P3_3
	C$asgn2_3.c$206$1$23 ==.
;	asgn2_3.c:206: P3_2=0;
	clr	_P3_2
	C$asgn2_3.c$207$1$23 ==.
;	asgn2_3.c:207: P3_1=1;
	setb	_P3_1
	C$asgn2_3.c$208$1$23 ==.
;	asgn2_3.c:208: P3_0=1;
	setb	_P3_0
	C$asgn2_3.c$209$1$23 ==.
;	asgn2_3.c:209: setSegment(second);
	mov	dpl,_second
	mov	dph,(_second + 1)
	lcall	_setSegment
	C$asgn2_3.c$210$1$23 ==.
;	asgn2_3.c:210: t0Delay();
	lcall	_t0Delay
	C$asgn2_3.c$211$1$23 ==.
;	asgn2_3.c:211: P3_3=1;
	setb	_P3_3
	C$asgn2_3.c$212$1$23 ==.
;	asgn2_3.c:212: P3_2=1;
	setb	_P3_2
	C$asgn2_3.c$213$1$23 ==.
;	asgn2_3.c:213: P3_1=0;
	clr	_P3_1
	C$asgn2_3.c$214$1$23 ==.
;	asgn2_3.c:214: P3_0=1;
	setb	_P3_0
	C$asgn2_3.c$215$1$23 ==.
;	asgn2_3.c:215: setSegment(third);
	mov	dpl,_third
	mov	dph,(_third + 1)
	lcall	_setSegment
	C$asgn2_3.c$216$1$23 ==.
;	asgn2_3.c:216: t0Delay();
	lcall	_t0Delay
	C$asgn2_3.c$217$1$23 ==.
;	asgn2_3.c:217: P3_3=1;
	setb	_P3_3
	C$asgn2_3.c$218$1$23 ==.
;	asgn2_3.c:218: P3_2=1;
	setb	_P3_2
	C$asgn2_3.c$219$1$23 ==.
;	asgn2_3.c:219: P3_1=1;
	setb	_P3_1
	C$asgn2_3.c$220$1$23 ==.
;	asgn2_3.c:220: P3_0=0;
	clr	_P3_0
	C$asgn2_3.c$221$1$23 ==.
;	asgn2_3.c:221: setSegment(fourth);
	mov	dpl,_fourth
	mov	dph,(_fourth + 1)
	lcall	_setSegment
	C$asgn2_3.c$222$1$23 ==.
;	asgn2_3.c:222: t0Delay();
	lcall	_t0Delay
	C$asgn2_3.c$223$1$23 ==.
	XG$display$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'updateDisplay'
;------------------------------------------------------------
;input                     Allocated to registers r6 r7 
;------------------------------------------------------------
	G$updateDisplay$0$0 ==.
	C$asgn2_3.c$239$1$23 ==.
;	asgn2_3.c:239: void updateDisplay(int input)  
;	-----------------------------------------
;	 function updateDisplay
;	-----------------------------------------
_updateDisplay:
	mov	r6,dpl
	mov	r7,dph
	C$asgn2_3.c$241$1$25 ==.
;	asgn2_3.c:241: first=second;
	mov	_first,_second
	mov	(_first + 1),(_second + 1)
	C$asgn2_3.c$242$1$25 ==.
;	asgn2_3.c:242: second=third;
	mov	_second,_third
	mov	(_second + 1),(_third + 1)
	C$asgn2_3.c$243$1$25 ==.
;	asgn2_3.c:243: third=fourth;
	mov	_third,_fourth
	mov	(_third + 1),(_fourth + 1)
	C$asgn2_3.c$244$1$25 ==.
;	asgn2_3.c:244: fourth=input;
	mov	_fourth,r6
	mov	(_fourth + 1),r7
	C$asgn2_3.c$245$1$25 ==.
	XG$updateDisplay$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'findButtonPress'
;------------------------------------------------------------
	G$findButtonPress$0$0 ==.
	C$asgn2_3.c$247$1$25 ==.
;	asgn2_3.c:247: void findButtonPress(void)
;	-----------------------------------------
;	 function findButtonPress
;	-----------------------------------------
_findButtonPress:
	C$asgn2_3.c$250$1$27 ==.
;	asgn2_3.c:250: P1_0 = 0;
	clr	_P1_0
	C$asgn2_3.c$251$1$27 ==.
;	asgn2_3.c:251: if(P1_4 == 0)
	jb	_P1_4,00105$
	C$asgn2_3.c$253$2$28 ==.
;	asgn2_3.c:253: updateDisplay(0);
	mov	dptr,#0x0000
	lcall	_updateDisplay
	C$asgn2_3.c$254$2$28 ==.
;	asgn2_3.c:254: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$255$2$28 ==.
;	asgn2_3.c:255: while(P1_4==0);
00101$:
	jnb	_P1_4,00101$
00105$:
	C$asgn2_3.c$257$1$27 ==.
;	asgn2_3.c:257: if(P1_5 == 0)
	jb	_P1_5,00110$
	C$asgn2_3.c$259$2$29 ==.
;	asgn2_3.c:259: updateDisplay(1);
	mov	dptr,#0x0001
	lcall	_updateDisplay
	C$asgn2_3.c$260$2$29 ==.
;	asgn2_3.c:260: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$261$2$29 ==.
;	asgn2_3.c:261: while(P1_5==0);
00106$:
	jnb	_P1_5,00106$
00110$:
	C$asgn2_3.c$263$1$27 ==.
;	asgn2_3.c:263: if(P1_6 == 0)
	jb	_P1_6,00115$
	C$asgn2_3.c$265$2$30 ==.
;	asgn2_3.c:265: updateDisplay(2);
	mov	dptr,#0x0002
	lcall	_updateDisplay
	C$asgn2_3.c$266$2$30 ==.
;	asgn2_3.c:266: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$267$2$30 ==.
;	asgn2_3.c:267: while(P1_6==0);
00111$:
	jnb	_P1_6,00111$
00115$:
	C$asgn2_3.c$269$1$27 ==.
;	asgn2_3.c:269: if(P1_7 == 0)
	jb	_P1_7,00120$
	C$asgn2_3.c$271$2$31 ==.
;	asgn2_3.c:271: updateDisplay(3);
	mov	dptr,#0x0003
	lcall	_updateDisplay
	C$asgn2_3.c$272$2$31 ==.
;	asgn2_3.c:272: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$273$2$31 ==.
;	asgn2_3.c:273: while(P1_7==0);
00116$:
	jnb	_P1_7,00116$
00120$:
	C$asgn2_3.c$276$1$27 ==.
;	asgn2_3.c:276: P1_0 = 1;
	setb	_P1_0
	C$asgn2_3.c$277$1$27 ==.
;	asgn2_3.c:277: P1_1 = 0;
	clr	_P1_1
	C$asgn2_3.c$279$1$27 ==.
;	asgn2_3.c:279: if(P1_4 == 0)
	jb	_P1_4,00125$
	C$asgn2_3.c$281$2$32 ==.
;	asgn2_3.c:281: updateDisplay(4);
	mov	dptr,#0x0004
	lcall	_updateDisplay
	C$asgn2_3.c$282$2$32 ==.
;	asgn2_3.c:282: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$283$2$32 ==.
;	asgn2_3.c:283: while(P1_4==0);
00121$:
	jnb	_P1_4,00121$
00125$:
	C$asgn2_3.c$285$1$27 ==.
;	asgn2_3.c:285: if(P1_5 == 0)
	jb	_P1_5,00130$
	C$asgn2_3.c$287$2$33 ==.
;	asgn2_3.c:287: updateDisplay(5);
	mov	dptr,#0x0005
	lcall	_updateDisplay
	C$asgn2_3.c$288$2$33 ==.
;	asgn2_3.c:288: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$289$2$33 ==.
;	asgn2_3.c:289: while(P1_5==0);
00126$:
	jnb	_P1_5,00126$
00130$:
	C$asgn2_3.c$291$1$27 ==.
;	asgn2_3.c:291: if(P1_6 == 0)
	jb	_P1_6,00135$
	C$asgn2_3.c$293$2$34 ==.
;	asgn2_3.c:293: updateDisplay(6);
	mov	dptr,#0x0006
	lcall	_updateDisplay
	C$asgn2_3.c$294$2$34 ==.
;	asgn2_3.c:294: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$295$2$34 ==.
;	asgn2_3.c:295: while(P1_6==0);
00131$:
	jnb	_P1_6,00131$
00135$:
	C$asgn2_3.c$297$1$27 ==.
;	asgn2_3.c:297: if(P1_7 == 0)
	jb	_P1_7,00140$
	C$asgn2_3.c$299$2$35 ==.
;	asgn2_3.c:299: updateDisplay(7);
	mov	dptr,#0x0007
	lcall	_updateDisplay
	C$asgn2_3.c$300$2$35 ==.
;	asgn2_3.c:300: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$301$2$35 ==.
;	asgn2_3.c:301: while(P1_7==0);
00136$:
	jnb	_P1_7,00136$
00140$:
	C$asgn2_3.c$304$1$27 ==.
;	asgn2_3.c:304: P1_1 = 1;
	setb	_P1_1
	C$asgn2_3.c$305$1$27 ==.
;	asgn2_3.c:305: P1_2 = 0;
	clr	_P1_2
	C$asgn2_3.c$307$1$27 ==.
;	asgn2_3.c:307: if(P1_4 == 0)
	jb	_P1_4,00145$
	C$asgn2_3.c$309$2$36 ==.
;	asgn2_3.c:309: updateDisplay(8);
	mov	dptr,#0x0008
	lcall	_updateDisplay
	C$asgn2_3.c$310$2$36 ==.
;	asgn2_3.c:310: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$311$2$36 ==.
;	asgn2_3.c:311: while(P1_4==0);
00141$:
	jnb	_P1_4,00141$
00145$:
	C$asgn2_3.c$313$1$27 ==.
;	asgn2_3.c:313: if(P1_5 == 0)
	jb	_P1_5,00150$
	C$asgn2_3.c$315$2$37 ==.
;	asgn2_3.c:315: updateDisplay(9);
	mov	dptr,#0x0009
	lcall	_updateDisplay
	C$asgn2_3.c$316$2$37 ==.
;	asgn2_3.c:316: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$317$2$37 ==.
;	asgn2_3.c:317: while(P1_5==0);
00146$:
	jnb	_P1_5,00146$
00150$:
	C$asgn2_3.c$319$1$27 ==.
;	asgn2_3.c:319: if(P1_6 == 0)
	jb	_P1_6,00155$
	C$asgn2_3.c$321$2$38 ==.
;	asgn2_3.c:321: updateDisplay(10);
	mov	dptr,#0x000A
	lcall	_updateDisplay
	C$asgn2_3.c$322$2$38 ==.
;	asgn2_3.c:322: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$323$2$38 ==.
;	asgn2_3.c:323: while(P1_6==0);
00151$:
	jnb	_P1_6,00151$
00155$:
	C$asgn2_3.c$325$1$27 ==.
;	asgn2_3.c:325: if(P1_7 == 0)
	jb	_P1_7,00160$
	C$asgn2_3.c$327$2$39 ==.
;	asgn2_3.c:327: updateDisplay(11);
	mov	dptr,#0x000B
	lcall	_updateDisplay
	C$asgn2_3.c$328$2$39 ==.
;	asgn2_3.c:328: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$329$2$39 ==.
;	asgn2_3.c:329: while(P1_7==0);
00156$:
	jnb	_P1_7,00156$
00160$:
	C$asgn2_3.c$332$1$27 ==.
;	asgn2_3.c:332: P1_2 = 1;
	setb	_P1_2
	C$asgn2_3.c$333$1$27 ==.
;	asgn2_3.c:333: P1_3 = 0;
	clr	_P1_3
	C$asgn2_3.c$335$1$27 ==.
;	asgn2_3.c:335: if(P1_4 == 0)
	jb	_P1_4,00165$
	C$asgn2_3.c$337$2$40 ==.
;	asgn2_3.c:337: updateDisplay(12);
	mov	dptr,#0x000C
	lcall	_updateDisplay
	C$asgn2_3.c$338$2$40 ==.
;	asgn2_3.c:338: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$339$2$40 ==.
;	asgn2_3.c:339: while(P1_4==0);
00161$:
	jnb	_P1_4,00161$
00165$:
	C$asgn2_3.c$341$1$27 ==.
;	asgn2_3.c:341: if(P1_5 == 0)
	jb	_P1_5,00170$
	C$asgn2_3.c$343$2$41 ==.
;	asgn2_3.c:343: updateDisplay(13);
	mov	dptr,#0x000D
	lcall	_updateDisplay
	C$asgn2_3.c$344$2$41 ==.
;	asgn2_3.c:344: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$345$2$41 ==.
;	asgn2_3.c:345: while(P1_5==0);
00166$:
	jnb	_P1_5,00166$
00170$:
	C$asgn2_3.c$347$1$27 ==.
;	asgn2_3.c:347: if(P1_6 == 0)
	jb	_P1_6,00175$
	C$asgn2_3.c$349$2$42 ==.
;	asgn2_3.c:349: updateDisplay(14);
	mov	dptr,#0x000E
	lcall	_updateDisplay
	C$asgn2_3.c$350$2$42 ==.
;	asgn2_3.c:350: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$351$2$42 ==.
;	asgn2_3.c:351: while(P1_6==0);
00171$:
	jnb	_P1_6,00171$
00175$:
	C$asgn2_3.c$353$1$27 ==.
;	asgn2_3.c:353: if(P1_7 == 0)
	jb	_P1_7,00180$
	C$asgn2_3.c$355$2$43 ==.
;	asgn2_3.c:355: updateDisplay(15);
	mov	dptr,#0x000F
	lcall	_updateDisplay
	C$asgn2_3.c$356$2$43 ==.
;	asgn2_3.c:356: t0Delay56ms();
	lcall	_t0Delay56ms
	C$asgn2_3.c$357$2$43 ==.
;	asgn2_3.c:357: while(P1_7==0);
00176$:
	jnb	_P1_7,00176$
00180$:
	C$asgn2_3.c$360$1$27 ==.
;	asgn2_3.c:360: P1_3 = 1;							
	setb	_P1_3
	C$asgn2_3.c$361$1$27 ==.
	XG$findButtonPress$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
	G$main$0$0 ==.
	C$asgn2_3.c$363$1$27 ==.
;	asgn2_3.c:363: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	C$asgn2_3.c$365$1$45 ==.
;	asgn2_3.c:365: first=1;
	mov	_first,#0x01
	mov	(_first + 1),#0x00
	C$asgn2_3.c$366$1$45 ==.
;	asgn2_3.c:366: second=2;
	mov	_second,#0x02
	mov	(_second + 1),#0x00
	C$asgn2_3.c$367$1$45 ==.
;	asgn2_3.c:367: third=3;
	mov	_third,#0x03
	mov	(_third + 1),#0x00
	C$asgn2_3.c$368$1$45 ==.
;	asgn2_3.c:368: fourth=4;
	mov	_fourth,#0x04
	mov	(_fourth + 1),#0x00
	C$asgn2_3.c$370$1$45 ==.
;	asgn2_3.c:370: while(1)
00102$:
	C$asgn2_3.c$372$2$46 ==.
;	asgn2_3.c:372: findButtonPress();
	lcall	_findButtonPress
	C$asgn2_3.c$373$2$46 ==.
;	asgn2_3.c:373: display();
	lcall	_display
	sjmp	00102$
	C$asgn2_3.c$375$1$45 ==.
	XG$main$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
