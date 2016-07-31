#include <mcs51/at89x52.h>

//very small delay between segment switching
void t0Delay()
{
	TMOD=0x01;
	TL0=0x00;
	TH0=0xE5;
	TR0=1;
	while(	TF0==0 );
	TR0=0;
	TF0=0;
}

// set segment values for each digit
void setSegment(int x)
{
	if(x==0)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=1;
	}
	else if(x==1)
	{
		P0_0=1;
 		P0_1=0;
 		P0_2=0;
 		P0_3=1;
 		P0_4=1;
 		P0_5=1;
 		P0_6=1;
	}
	else if(x==2)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=1;
 		P0_3=0;
 		P0_4=0;
 		P0_5=1;
 		P0_6=0;
	}
	else if(x==3)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=1;
 		P0_5=1;
 		P0_6=0;
	}
	else if(x==4)
	{
		P0_0=1;
 		P0_1=0;
 		P0_2=0;
 		P0_3=1;
 		P0_4=1;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==5)
	{
		P0_0=0;
 		P0_1=1;
 		P0_2=0;
 		P0_3=0;
 		P0_4=1;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==6)
	{
		P0_0=0;
 		P0_1=1;
 		P0_2=0;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==7)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=1;
 		P0_4=1;
 		P0_5=1;
 		P0_6=1;
	}
	else if(x==8)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==9)
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=1;
 		P0_5=0;
 		P0_6=0;
	}
}

void display(int x){

	int unitDigit, tensDigit;
	unitDigit=x%10;
 	setSegment(unitDigit);
 	P1_1=1;
 	P1_0=0;
 	t0Delay();
 	tensDigit=x/10;
 	setSegment(tensDigit);
 	P1_1=0;
 	P1_0=1;
 	t0Delay();
}

// Delay of 56 ms
void t0Delay56ms()
{
	TMOD=0x01;
	TL0=0x00;
	TH0=0x35;
	TR0=1;
	while(	TF0==0 );
	TR0=0;
	TF0=0;	
}

/*
P0_0 to A
P0_1 to B
P0_2 to C
P0_3 to D
P0_4 to E
P0_5 to F
P0_6 to G
P0_7 to SW1
P1_0 to CN1_2
P1_1 to CN1_3
*/
void main(void)
{
	int acc=0;
	display(acc);
	while(1)
	{
 		if(P0_7==0)
 		{
 			acc = acc +1;
 			acc=acc%100;
 			t0Delay56ms();
 			while(P0_7==0);
 		}
 		else
 			display(acc);
	} 

}
