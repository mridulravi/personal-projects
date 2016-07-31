int fn(int c, int d)
{
	if(c==1)
	  return d;
	return d + fn(c-1,d);	
}

main()
{
	int a = 3;
	int b = 5;
	int c;
	c = fn(a,b);
}


