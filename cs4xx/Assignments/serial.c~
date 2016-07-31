#include <mcs51/at89x52.h>

void main(void)
{
	TMOD=0x20;
	TH1=0xFA; //4800 baud rate
	SCON=0x50;
	TR1=1;
	SBUF='A';
	while(TI==0);
	TI=0;
}