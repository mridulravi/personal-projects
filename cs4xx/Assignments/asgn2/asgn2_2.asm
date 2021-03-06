;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (MINGW64)
; This file was generated Sat Jan 31 22:26:39 2015
;--------------------------------------------------------
	.module asgn2_2
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _t0Delay56ms
	.globl _display
	.globl _setSegment
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
	C$asgn2_2.c$4$0$0 ==.
;	asgn2_2.c:4: void t0Delay()
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
	C$asgn2_2.c$6$1$1 ==.
;	asgn2_2.c:6: TMOD=0x01;
	mov	_TMOD,#0x01
	C$asgn2_2.c$7$1$1 ==.
;	asgn2_2.c:7: TL0=0x00;
	mov	_TL0,#0x00
	C$asgn2_2.c$8$1$1 ==.
;	asgn2_2.c:8: TH0=0xE5;
	mov	_TH0,#0xE5
	C$asgn2_2.c$9$1$1 ==.
;	asgn2_2.c:9: TR0=1;
	setb	_TR0
	C$asgn2_2.c$10$1$1 ==.
;	asgn2_2.c:10: while(	TF0==0 );
00101$:
	jnb	_TF0,00101$
	C$asgn2_2.c$11$1$1 ==.
;	asgn2_2.c:11: TR0=0;
	clr	_TR0
	C$asgn2_2.c$12$1$1 ==.
;	asgn2_2.c:12: TF0=0;
	clr	_TF0
	C$asgn2_2.c$13$1$1 ==.
	XG$t0Delay$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'setSegment'
;------------------------------------------------------------
;x                         Allocated to registers r6 r7 
;------------------------------------------------------------
	G$setSegment$0$0 ==.
	C$asgn2_2.c$16$1$1 ==.
;	asgn2_2.c:16: void setSegment(int x)
;	-----------------------------------------
;	 function setSegment
;	-----------------------------------------
_setSegment:
	mov	r6,dpl
	mov	r7,dph
	C$asgn2_2.c$18$1$3 ==.
;	asgn2_2.c:18: if(x==0)
	mov	a,r6
	orl	a,r7
	jnz	00128$
	C$asgn2_2.c$20$2$4 ==.
;	asgn2_2.c:20: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$21$2$4 ==.
;	asgn2_2.c:21: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$22$2$4 ==.
;	asgn2_2.c:22: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$23$2$4 ==.
;	asgn2_2.c:23: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$24$2$4 ==.
;	asgn2_2.c:24: P0_4=0;
	clr	_P0_4
	C$asgn2_2.c$25$2$4 ==.
;	asgn2_2.c:25: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$26$2$4 ==.
;	asgn2_2.c:26: P0_6=1;
	setb	_P0_6
	ljmp	00130$
00128$:
	C$asgn2_2.c$28$1$3 ==.
;	asgn2_2.c:28: else if(x==1)
	cjne	r6,#0x01,00125$
	cjne	r7,#0x00,00125$
	C$asgn2_2.c$30$2$5 ==.
;	asgn2_2.c:30: P0_0=1;
	setb	_P0_0
	C$asgn2_2.c$31$2$5 ==.
;	asgn2_2.c:31: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$32$2$5 ==.
;	asgn2_2.c:32: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$33$2$5 ==.
;	asgn2_2.c:33: P0_3=1;
	setb	_P0_3
	C$asgn2_2.c$34$2$5 ==.
;	asgn2_2.c:34: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$35$2$5 ==.
;	asgn2_2.c:35: P0_5=1;
	setb	_P0_5
	C$asgn2_2.c$36$2$5 ==.
;	asgn2_2.c:36: P0_6=1;
	setb	_P0_6
	ljmp	00130$
00125$:
	C$asgn2_2.c$38$1$3 ==.
;	asgn2_2.c:38: else if(x==2)
	cjne	r6,#0x02,00122$
	cjne	r7,#0x00,00122$
	C$asgn2_2.c$40$2$6 ==.
;	asgn2_2.c:40: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$41$2$6 ==.
;	asgn2_2.c:41: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$42$2$6 ==.
;	asgn2_2.c:42: P0_2=1;
	setb	_P0_2
	C$asgn2_2.c$43$2$6 ==.
;	asgn2_2.c:43: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$44$2$6 ==.
;	asgn2_2.c:44: P0_4=0;
	clr	_P0_4
	C$asgn2_2.c$45$2$6 ==.
;	asgn2_2.c:45: P0_5=1;
	setb	_P0_5
	C$asgn2_2.c$46$2$6 ==.
;	asgn2_2.c:46: P0_6=0;
	clr	_P0_6
	ljmp	00130$
00122$:
	C$asgn2_2.c$48$1$3 ==.
;	asgn2_2.c:48: else if(x==3)
	cjne	r6,#0x03,00119$
	cjne	r7,#0x00,00119$
	C$asgn2_2.c$50$2$7 ==.
;	asgn2_2.c:50: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$51$2$7 ==.
;	asgn2_2.c:51: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$52$2$7 ==.
;	asgn2_2.c:52: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$53$2$7 ==.
;	asgn2_2.c:53: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$54$2$7 ==.
;	asgn2_2.c:54: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$55$2$7 ==.
;	asgn2_2.c:55: P0_5=1;
	setb	_P0_5
	C$asgn2_2.c$56$2$7 ==.
;	asgn2_2.c:56: P0_6=0;
	clr	_P0_6
	ljmp	00130$
00119$:
	C$asgn2_2.c$58$1$3 ==.
;	asgn2_2.c:58: else if(x==4)
	cjne	r6,#0x04,00116$
	cjne	r7,#0x00,00116$
	C$asgn2_2.c$60$2$8 ==.
;	asgn2_2.c:60: P0_0=1;
	setb	_P0_0
	C$asgn2_2.c$61$2$8 ==.
;	asgn2_2.c:61: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$62$2$8 ==.
;	asgn2_2.c:62: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$63$2$8 ==.
;	asgn2_2.c:63: P0_3=1;
	setb	_P0_3
	C$asgn2_2.c$64$2$8 ==.
;	asgn2_2.c:64: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$65$2$8 ==.
;	asgn2_2.c:65: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$66$2$8 ==.
;	asgn2_2.c:66: P0_6=0;
	clr	_P0_6
	ljmp	00130$
00116$:
	C$asgn2_2.c$68$1$3 ==.
;	asgn2_2.c:68: else if(x==5)
	cjne	r6,#0x05,00113$
	cjne	r7,#0x00,00113$
	C$asgn2_2.c$70$2$9 ==.
;	asgn2_2.c:70: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$71$2$9 ==.
;	asgn2_2.c:71: P0_1=1;
	setb	_P0_1
	C$asgn2_2.c$72$2$9 ==.
;	asgn2_2.c:72: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$73$2$9 ==.
;	asgn2_2.c:73: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$74$2$9 ==.
;	asgn2_2.c:74: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$75$2$9 ==.
;	asgn2_2.c:75: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$76$2$9 ==.
;	asgn2_2.c:76: P0_6=0;
	clr	_P0_6
	sjmp	00130$
00113$:
	C$asgn2_2.c$78$1$3 ==.
;	asgn2_2.c:78: else if(x==6)
	cjne	r6,#0x06,00110$
	cjne	r7,#0x00,00110$
	C$asgn2_2.c$80$2$10 ==.
;	asgn2_2.c:80: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$81$2$10 ==.
;	asgn2_2.c:81: P0_1=1;
	setb	_P0_1
	C$asgn2_2.c$82$2$10 ==.
;	asgn2_2.c:82: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$83$2$10 ==.
;	asgn2_2.c:83: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$84$2$10 ==.
;	asgn2_2.c:84: P0_4=0;
	clr	_P0_4
	C$asgn2_2.c$85$2$10 ==.
;	asgn2_2.c:85: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$86$2$10 ==.
;	asgn2_2.c:86: P0_6=0;
	clr	_P0_6
	sjmp	00130$
00110$:
	C$asgn2_2.c$88$1$3 ==.
;	asgn2_2.c:88: else if(x==7)
	cjne	r6,#0x07,00107$
	cjne	r7,#0x00,00107$
	C$asgn2_2.c$90$2$11 ==.
;	asgn2_2.c:90: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$91$2$11 ==.
;	asgn2_2.c:91: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$92$2$11 ==.
;	asgn2_2.c:92: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$93$2$11 ==.
;	asgn2_2.c:93: P0_3=1;
	setb	_P0_3
	C$asgn2_2.c$94$2$11 ==.
;	asgn2_2.c:94: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$95$2$11 ==.
;	asgn2_2.c:95: P0_5=1;
	setb	_P0_5
	C$asgn2_2.c$96$2$11 ==.
;	asgn2_2.c:96: P0_6=1;
	setb	_P0_6
	sjmp	00130$
00107$:
	C$asgn2_2.c$98$1$3 ==.
;	asgn2_2.c:98: else if(x==8)
	cjne	r6,#0x08,00104$
	cjne	r7,#0x00,00104$
	C$asgn2_2.c$100$2$12 ==.
;	asgn2_2.c:100: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$101$2$12 ==.
;	asgn2_2.c:101: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$102$2$12 ==.
;	asgn2_2.c:102: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$103$2$12 ==.
;	asgn2_2.c:103: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$104$2$12 ==.
;	asgn2_2.c:104: P0_4=0;
	clr	_P0_4
	C$asgn2_2.c$105$2$12 ==.
;	asgn2_2.c:105: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$106$2$12 ==.
;	asgn2_2.c:106: P0_6=0;
	clr	_P0_6
	sjmp	00130$
00104$:
	C$asgn2_2.c$108$1$3 ==.
;	asgn2_2.c:108: else if(x==9)
	cjne	r6,#0x09,00130$
	cjne	r7,#0x00,00130$
	C$asgn2_2.c$110$2$13 ==.
;	asgn2_2.c:110: P0_0=0;
	clr	_P0_0
	C$asgn2_2.c$111$2$13 ==.
;	asgn2_2.c:111: P0_1=0;
	clr	_P0_1
	C$asgn2_2.c$112$2$13 ==.
;	asgn2_2.c:112: P0_2=0;
	clr	_P0_2
	C$asgn2_2.c$113$2$13 ==.
;	asgn2_2.c:113: P0_3=0;
	clr	_P0_3
	C$asgn2_2.c$114$2$13 ==.
;	asgn2_2.c:114: P0_4=1;
	setb	_P0_4
	C$asgn2_2.c$115$2$13 ==.
;	asgn2_2.c:115: P0_5=0;
	clr	_P0_5
	C$asgn2_2.c$116$2$13 ==.
;	asgn2_2.c:116: P0_6=0;
	clr	_P0_6
00130$:
	C$asgn2_2.c$118$1$3 ==.
	XG$setSegment$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'display'
;------------------------------------------------------------
;x                         Allocated to registers r6 r7 
;unitDigit                 Allocated to registers 
;tensDigit                 Allocated to registers 
;------------------------------------------------------------
	G$display$0$0 ==.
	C$asgn2_2.c$120$1$3 ==.
;	asgn2_2.c:120: void display(int x){
;	-----------------------------------------
;	 function display
;	-----------------------------------------
_display:
	C$asgn2_2.c$123$1$15 ==.
;	asgn2_2.c:123: unitDigit=x%10;
	mov	r6,dpl
	mov	r7,dph
	mov	__modsint_PARM_2,#0x0A
	mov	(__modsint_PARM_2 + 1),#0x00
	push	ar7
	push	ar6
	lcall	__modsint
	C$asgn2_2.c$124$1$15 ==.
;	asgn2_2.c:124: setSegment(unitDigit);
	lcall	_setSegment
	C$asgn2_2.c$125$1$15 ==.
;	asgn2_2.c:125: P1_1=1;
	setb	_P1_1
	C$asgn2_2.c$126$1$15 ==.
;	asgn2_2.c:126: P1_0=0;
	clr	_P1_0
	C$asgn2_2.c$127$1$15 ==.
;	asgn2_2.c:127: t0Delay();
	lcall	_t0Delay
	pop	ar6
	pop	ar7
	C$asgn2_2.c$128$1$15 ==.
;	asgn2_2.c:128: tensDigit=x/10;
	mov	__divsint_PARM_2,#0x0A
	mov	(__divsint_PARM_2 + 1),#0x00
	mov	dpl,r6
	mov	dph,r7
	lcall	__divsint
	C$asgn2_2.c$129$1$15 ==.
;	asgn2_2.c:129: setSegment(tensDigit);
	lcall	_setSegment
	C$asgn2_2.c$130$1$15 ==.
;	asgn2_2.c:130: P1_1=0;
	clr	_P1_1
	C$asgn2_2.c$131$1$15 ==.
;	asgn2_2.c:131: P1_0=1;
	setb	_P1_0
	C$asgn2_2.c$132$1$15 ==.
;	asgn2_2.c:132: t0Delay();
	lcall	_t0Delay
	C$asgn2_2.c$133$1$15 ==.
	XG$display$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 't0Delay56ms'
;------------------------------------------------------------
	G$t0Delay56ms$0$0 ==.
	C$asgn2_2.c$136$1$15 ==.
;	asgn2_2.c:136: void t0Delay56ms()
;	-----------------------------------------
;	 function t0Delay56ms
;	-----------------------------------------
_t0Delay56ms:
	C$asgn2_2.c$138$1$16 ==.
;	asgn2_2.c:138: TMOD=0x01;
	mov	_TMOD,#0x01
	C$asgn2_2.c$139$1$16 ==.
;	asgn2_2.c:139: TL0=0x00;
	mov	_TL0,#0x00
	C$asgn2_2.c$140$1$16 ==.
;	asgn2_2.c:140: TH0=0x35;
	mov	_TH0,#0x35
	C$asgn2_2.c$141$1$16 ==.
;	asgn2_2.c:141: TR0=1;
	setb	_TR0
	C$asgn2_2.c$142$1$16 ==.
;	asgn2_2.c:142: while(	TF0==0 );
00101$:
	jnb	_TF0,00101$
	C$asgn2_2.c$143$1$16 ==.
;	asgn2_2.c:143: TR0=0;
	clr	_TR0
	C$asgn2_2.c$144$1$16 ==.
;	asgn2_2.c:144: TF0=0;	
	clr	_TF0
	C$asgn2_2.c$145$1$16 ==.
	XG$t0Delay56ms$0$0 ==.
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;acc                       Allocated to registers r6 r7 
;------------------------------------------------------------
	G$main$0$0 ==.
	C$asgn2_2.c$159$1$16 ==.
;	asgn2_2.c:159: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	C$asgn2_2.c$161$1$16 ==.
;	asgn2_2.c:161: int acc=0;
	mov	r6,#0x00
	mov	r7,#0x00
	C$asgn2_2.c$162$1$18 ==.
;	asgn2_2.c:162: display(acc);
	mov	dptr,#0x0000
	push	ar7
	push	ar6
	lcall	_display
	pop	ar6
	pop	ar7
	C$asgn2_2.c$163$1$18 ==.
;	asgn2_2.c:163: while(1)
00108$:
	C$asgn2_2.c$165$2$19 ==.
;	asgn2_2.c:165: if(P0_7==0)
	jb	_P0_7,00105$
	C$asgn2_2.c$167$3$20 ==.
;	asgn2_2.c:167: acc = acc +1;
	inc	r6
	cjne	r6,#0x00,00125$
	inc	r7
00125$:
	C$asgn2_2.c$168$1$18 ==.
;	asgn2_2.c:168: acc=acc%100;
	mov	__modsint_PARM_2,#0x64
	mov	(__modsint_PARM_2 + 1),#0x00
	mov	dpl,r6
	mov	dph,r7
	lcall	__modsint
	mov	r6,dpl
	mov	r7,dph
	C$asgn2_2.c$169$3$20 ==.
;	asgn2_2.c:169: t0Delay56ms();
	push	ar7
	push	ar6
	lcall	_t0Delay56ms
	pop	ar6
	pop	ar7
	C$asgn2_2.c$170$3$20 ==.
;	asgn2_2.c:170: while(P0_7==0);
00101$:
	jb	_P0_7,00108$
	sjmp	00101$
00105$:
	C$asgn2_2.c$173$2$19 ==.
;	asgn2_2.c:173: display(acc);
	mov	dpl,r6
	mov	dph,r7
	push	ar7
	push	ar6
	lcall	_display
	pop	ar6
	pop	ar7
	sjmp	00108$
	C$asgn2_2.c$176$1$18 ==.
	XG$main$0$0 ==.
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
