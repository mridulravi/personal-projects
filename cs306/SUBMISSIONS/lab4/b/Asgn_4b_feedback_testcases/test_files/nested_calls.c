int f1(int a)
{
return 2*a;
}

int f2(int b)
{
return 2*b;
}

int f3(int c)
{
return 2*c;
}

main()
{
int x = f3(f2(f1(3)));
}
