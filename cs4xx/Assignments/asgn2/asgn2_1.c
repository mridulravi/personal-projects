#include <mcs51/at89x52.h>

// Delay of 56 ms
void t0Delay()
{
	TMOD=0x01;
	TL0=0x00;
	TH0=0x35;
	TR0=1;
	while(	TF0==0 );
	TR0=0;
	TF0=0;	
}

//P0_0 is connected to button
//P1 connected to LEDs
void main(void){

	int acc=0;
	P1=acc;
	while(1)
	{
 		if(P0_0==0)
 		{
 			acc = acc +1;
 			P1 = acc;
 			t0Delay();
 			while(P0_0==0);
 		}
	} 
}