int add(int, int, int );
int sub(int, int, int);

void main()
{
	int a=1, b=2,c=3,d;
	if(a>b)
		if(b>c)
			d=add(a,b,c);
	else
		d= sub(c,b,a);
}

int add(int a, int b, int c)
{
	return(a+b+c);
}

int sub(int a, int b, int c)
{
	return(a-b-c);
}