int fun1(int, int);
int fun2(int);
main()
{
	int x;
	x = fun1 (fun1(5,2), fun1(7, 3) );
}

int fun1(int a, int b)
{
	int x;
	x=a-b;
	return (fun2(x));
} 

int fun2(int a)
{
	return a*a;
}
