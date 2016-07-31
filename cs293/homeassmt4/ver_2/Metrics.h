#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
using namespace std;



class Metrics{
public:
	float totalDep, totalArr, BusySvr;
	float ttlWaitTime,avgWaitTime, Queuelength;
	float CbfrFull;
	float ttlTimeBusySvr,AvgTimeSvrBusy,ttlTimeouts;
	Metrics()
	{
		totalDep=0;
		ttlWaitTime =0;
		totalArr=0; 
		BusySvr=0; 
		Queuelength=0;
		ttlTimeBusySvr = 0;
		ttlTimeouts = 0;
				
	
	}
	float CalculateAvgWaitTime()
	{
		return ttlWaitTime/(totalDep + BusySvr);
	}
	float CalculateFractionBfrfull()
	{	float x= (CbfrFull/totalArr);
		return x;
	}
	
};
