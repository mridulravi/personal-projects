float fact(float);
int main()
{
	float a=10,c;
	c=fact(a);
return 0;
}

float fact (float f)
{
if(f==0||f==1)
	return 1;
else	
	return f*fact(f-1);
}
