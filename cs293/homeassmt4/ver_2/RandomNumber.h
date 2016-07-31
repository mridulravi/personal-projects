#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
using namespace std;


class RNG
{
	public:
	float a,min,max,LC;
	RNG()
	{
		LC=.01;
		srand(time(NULL));
	}
	float Generate(float min,float max)
	{
		if(max > min)
		{
			int s = (max - min) / LC;
			a = min + ((rand() % s) * LC);
			return a;
		}
		else if(max == min)
		{
			a = min;
			return a;
		}
	}
};
