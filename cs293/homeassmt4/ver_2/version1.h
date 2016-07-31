#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"Metrics.h"
#include"RandomNumber.h"
#include"Buffer.h"
using namespace std;



class Simulator{
	public:
	//AvgArrTimeRange Arrmin-Arrmax
	float Arrmin,Arrmax,Sermin,Sermax,Coutmin,Coutmax;
	int Depmax;
	EventList El;
	Event* temp;
	Customer Cus;
	Customer* tmpC;
	Server* tmpS;
	Buffer Bfr;
	Metrics Mcs;
	float CurrentTime;
	Event CurrentEvent;
	int Sn;
	float lastEventTime, ttlBfrlength, initialTime;
	list<Server> svrlist;
	list<Server>::iterator svri;
	list<Customer*>::iterator Ci;
	RNG rg;
	Simulator();	
	void start();
};
