#include <mcs51/at89x52.h>


int first=1,second=2,third=3,fourth=4;

//very small delay between segment switching
void t0Delay()
{
	TMOD=0x01;
	TL0=0x00;
	TH0=0xF5;
	TR0=1;
	while(	TF0==0 );
	TR0=0;
	TF0=0;
}

// Delay of 56 ms
void t0Delay56ms(void)
{
	TMOD=0x01;
	TL0=0x00;
	TH0=0x35;
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
	else if(x==10)//A
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=1;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==11)//B
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==12)//C
	{
		P0_0=0;
 		P0_1=1;
 		P0_2=1;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=1;
	}
	else if(x==13)//D
	{
		P0_0=0;
 		P0_1=0;
 		P0_2=0;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=1;
	}
	else if(x==14)//E
	{
		P0_0=0;
 		P0_1=1;
 		P0_2=1;
 		P0_3=0;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
	else if(x==15)//F
	{
		P0_0=0;
 		P0_1=1;
 		P0_2=1;
 		P0_3=1;
 		P0_4=0;
 		P0_5=0;
 		P0_6=0;
	}
}

//Switch between segemnts
void display(void){

	P3_3=0;
 	P3_2=1;
 	P3_1=1;
 	P3_0=1;
 	setSegment(first);
 	t0Delay();
 	P3_3=1;
 	P3_2=0;
 	P3_1=1;
 	P3_0=1;
 	setSegment(second);
 	t0Delay();
 	P3_3=1;
 	P3_2=1;
 	P3_1=0;
 	P3_0=1;
 	setSegment(third);
 	t0Delay();
 	P3_3=1;
 	P3_2=1;
 	P3_1=1;
 	P3_0=0;
 	setSegment(fourth);
 	t0Delay();
}



void updateDisplay(int input)  
{
	first=second;
	second=third;
	third=fourth;
	fourth=input;
}

void findButtonPress(void)
{
	// set rows low one by one and check which col is low
	P1_0 = 0;
	if(P1_4 == 0)
	{
		updateDisplay(0);
 		t0Delay56ms();
		while(P1_4==0);
	}
	if(P1_5 == 0)
	{
		updateDisplay(1);
 		t0Delay56ms();
		while(P1_5==0);
	}
	if(P1_6 == 0)
	{
		updateDisplay(2);
 		t0Delay56ms();
		while(P1_6==0);
	}
	if(P1_7 == 0)
	{
		updateDisplay(3);
 		t0Delay56ms();
		while(P1_7==0);
	}

	P1_0 = 1;
	P1_1 = 0;
	
	if(P1_4 == 0)
	{
		updateDisplay(4);
 		t0Delay56ms();
		while(P1_4==0);
	}
	if(P1_5 == 0)
	{
		updateDisplay(5);
 		t0Delay56ms();
		while(P1_5==0);
	}
	if(P1_6 == 0)
	{
		updateDisplay(6);
 		t0Delay56ms();
		while(P1_6==0);
	}
	if(P1_7 == 0)
	{
		updateDisplay(7);
 		t0Delay56ms();
		while(P1_7==0);
	}

	P1_1 = 1;
	P1_2 = 0;
	
	if(P1_4 == 0)
	{
		updateDisplay(8);
 		t0Delay56ms();
		while(P1_4==0);
	}
	if(P1_5 == 0)
	{
		updateDisplay(9);
 		t0Delay56ms();
		while(P1_5==0);
	}
	if(P1_6 == 0)
	{
		updateDisplay(10);
 		t0Delay56ms();
		while(P1_6==0);
	}
	if(P1_7 == 0)
	{
		updateDisplay(11);
 		t0Delay56ms();
		while(P1_7==0);
	}

	P1_2 = 1;
	P1_3 = 0;
	
	if(P1_4 == 0)
	{
		updateDisplay(12);
 		t0Delay56ms();
		while(P1_4==0);
	}
	if(P1_5 == 0)
	{
		updateDisplay(13);
 		t0Delay56ms();
		while(P1_5==0);
	}
	if(P1_6 == 0)
	{
		updateDisplay(14);
 		t0Delay56ms();
		while(P1_6==0);
	}
	if(P1_7 == 0)
	{
		updateDisplay(15);
 		t0Delay56ms();
		while(P1_7==0);
	}

	P1_3 = 1;							
}


/*
P0_0 to A
P0_1 to B
P0_2 to C
P0_3 to D
P0_4 to E
P0_5 to F
P0_6 to G
P1_0 to R1
P1_1 to R2
P1_2 to R3
P1_3 to R4
P1_4 to C4
P1_5 to C3
P1_6 to C2
P1_7 to C1
P3_0 to CN1_0
P3_1 to CN1_1
P3_2 to CN1_2
P3_3 to CN1_3
*/

void main(void)
{
	first=1;
	second=2;
	third=3;
	fourth=4;
	
	while(1)
	{
		findButtonPress();
		display();
	}
}

