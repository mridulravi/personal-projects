int fn(int c, float d)
{
	c = 4;
	return c + 1;
}

main()
{
	int a = 3;
	float b = 5;
	int result;

	result = fn(a,b+a);
}


