#include<iostream>
#include<queue>
#include<math.h>
#include"version2.h"

using namespace std;

int main()
{	int x;
	Simulator S;
	cout<<"Enter Inter Arrival time range"<<endl;
	cin>>S.Arrmin>>S.Arrmax;
	cout<<"Enter Service time range"<<endl;
	cin>>S.Sermin>>S.Sermax;

	cout<<"Enter maximum Departures"<<endl;
	cin>>S.Depmax;
	cout<<"Number of Servers"<<endl;
	cin>>S.Sn;
	cout<<"Buffer length including Servers"<<endl;
	cin>>x;
	S.Bfr.maxsize = x-S.Sn;
	cout<<endl;
	S.start();
	cout<<endl;
	cout<<"Average Waiting Time = "<<S.Mcs.CalculateAvgWaitTime()<<endl;
	cout<<"Total Departures = "<<S.Mcs.totalDep<<endl;
	cout<<"Total Arrivals = "<<S.Mcs.totalArr<<endl;
	cout<<"Fraction of Customers Successfully Serviced = "<<(S.Mcs.totalDep)/(S.Mcs.totalArr)<<endl;
	cout<<"Fraction of time Server were busy= "<<S.Mcs.AvgTimeSvrBusy<<endl;
	cout<<"Average Queue length = "<<S.Mcs.Queuelength<<endl;
	cout<<"Fraction of Customers Out due to full buffer = "<<S.Mcs.CalculateFractionBfrfull()<<endl;

	return 0;

}
