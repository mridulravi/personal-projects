#include <stdio.h>
#include <math.h> 
#include <string.h>

int decimal_binary(int n);
char sum(char a, char b, char c);
char carry(char a, char b, char c); 

int main() 
{ 
	int n; 
	char c; 
	printf("Enter a negative integer: ");
	scanf("%d", &n);
	printf("%d in decimal = %d in binary \n", n, decimal_binary(n)); 
	return 0; 
}

int decimal_binary(int n)
{ 
	int rem, i=1, binary=0, lenBinary=1; 
	while (n!=0) 
	{
		rem=n%2; 
		n/=2; 
		binary+=rem*i; 
		i*=10; 
	}
	i = 10;
	while ((binary/i) != 0)
	{ 
		lenBinary++;
		i*=10;
	}
	
	int correction = lenBinary%4;
	char str[10000];
	sprintf(str, "%d", binary);
	char corrstr[20000];
	if (correction == 1)
		{ corrstr[0] = '0'; corrstr[1] = '0'; corrstr[2] = '0';}
	else if (correction == 2)
		{ corrstr[0] = '0'; corrstr[1] = '0';  }
	else if (correction == 3)
		{ corrstr[0] = '0'; }
	//else if (correction == 0)
		//{ corrstr[0] = ""; }
	printf("\n");
	printf("before"); printf("%s", corrstr);
	printf("\n");
	strcat(corrstr,str);
	printf("after"); printf("%s", corrstr);
	printf("\n");
	for (i = 0; i < strlen(corrstr); i++)
	{
		if (corrstr[i] == '1')
			corrstr[i] = '0';
		else if (corrstr[i] == '0')
			corrstr[i] = '1';
	}
	printf("Final");
	printf("%s", corrstr);
	printf("\n");
	char last1[10000];
	for (i = 0; i < strlen(corrstr); i++)
	{
		if (i == (strlen(corrstr)-1))
			{last1[i]='1';}
		else
			{last1[i]='0';}
	}

	printf("last1");
	printf("%s", last1);
	printf("\n");
	char ans[10000];
	char carr[10000];
	for (i = (strlen(corrstr)-1); i >= 0; i--)
	{
		if (i == (strlen(corrstr)-1))
			{ 
			ans[i] = sum(0,corrstr[i],last1[i]);
			carr[i-1] = carry(0,corrstr[i],last1[i]);
			printf("%d", ans[i]);
			printf("\n");
			printf("%d", carr[i-1]);
			printf("\n");
			printf("\n");
			}
		else 
			{
			ans[i] = sum(carr[i],corrstr[i],last1[i]);
			carr[i-1] = carry(carr[i],corrstr[i],last1[i]);
			printf("%d", ans[i]);
			printf("\n");
			printf("%d", carr[i-1]);
			printf("\n");
			printf("\n");
			}
		
	} 
		//ans[i+1] = carr[i+1];
	printf("carry");
	printf("%s", carr);
	printf("\n");

	printf("ans");
	printf("%s", ans);
	printf("\n");

	return carr[3];
		
}


char sum(char a, char b, char c)
{
	if ((a == '0') && (b == '0') && (c == '0'))
		{return '0';}
	else if ((a == '0') && (b == '0') && (c == '1'))
		{return '1';}
	else if ((a == '0') && (b == '1') && (c == '0'))
		{return '1';}
	else if ((a == '0') && (b == '1') && (c == '1'))
		{return '0';}
	else if ((a == '1') && (b == '0') && (c == '0'))
		{return '1';}
	else if ((a == '1') && (b == '0') && (c == '1'))
		{return '0';}
	else if ((a == '1') && (b == '1') && (c == '0'))
		{return '0';}
	else if ((a == '1') && (b == '1') && (c == '1'))
		{return '1';}
}

char carry(char a, char b, char c)
{
	if ((a == '0') && (b == '0') && (c == '0'))
		{return '0';}
	else if ((a == '0') && (b == '0') && (c == '1'))
		{return '0';}
	else if ((a == '0') && (b == '1') && (c == '0'))
		{return '0';}
	else if ((a == '0') && (b == '1') && (c == '1'))
		{return '1';}
	else if ((a == '1') && (b == '0') && (c == '0'))
		{return '0';}
	else if ((a == '1') && (b == '0') && (c == '1'))
		{return '1';}
	else if ((a == '1') && (b == '1') && (c == '0'))
		{return '1';}
	else if ((a == '1') && (b == '1') && (c == '1'))
		{return '1';}
}




