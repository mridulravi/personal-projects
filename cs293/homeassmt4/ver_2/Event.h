#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"Server.h"
using namespace std;



class Event
{
	public:
	Customer* C;
	int sn;
	float time;
	string type;   //arr for arrival, dep for departure, and out for Customer timeout
	
};
