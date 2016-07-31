#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"Eventlist.h"
using namespace std;




class Buffer{
	public:
	list<Customer*> Q;
	int maxsize, Outs;
	bool full;
	Buffer()
	{Outs = 0;
	full=0;}
	void arrival(Customer* C)
	{		
		if (Q.size() < maxsize)
		{Q.push_back(C);
		full=0;}
		else
		{
			Outs++;
			full =1;
			
		}
	}
	Customer* departure()
	{
		Customer* x = *(Q.begin());
		Q.erase(Q.begin());
		return x;
	}
};
