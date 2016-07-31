#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"Customer.h"
using namespace std;


class Server{
	private:
	int number;
	public:
	
	bool state;
	Customer* currentC;
	
	Server()
	{
		state=0;
	}
	int num()
	{
		return number;
	}
	void setnum(int k)
	{
		number = k;
	}
};
