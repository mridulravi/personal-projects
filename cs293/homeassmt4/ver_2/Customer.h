#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
using namespace std;


class Customer{
	public:
	Customer* next;
	int id;
	float arrtime;
	Customer()
	{next = NULL;}
};
