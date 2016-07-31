#include<iostream>
#include<queue>
#include<math.h>
#include"version3.h"

using namespace std;

int main()
{	int x;
	Simulator S;
	cout<<"Enter Inter Arrival Time Range"<<endl;
	cin>>S.Arrmin>>S.Arrmax;
	cout<<"Enter Service Time Range"<<endl;
	cin>>S.Sermin>>S.Sermax;
	
	cout<<"Enter Time-out Time Range"<<endl;
	cin>>S.Coutmin>>S.Coutmax;
	cout<<"Enter maximum Departures"<<endl;
	cin>>S.Depmax;
	cout<<"Number of Servers"<<endl;
	cin>>S.Sn;
	cout<<"Buffer length including Servers"<<endl;
	cin>>x;
	S.Bfr.maxsize = x - S.Sn;
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
	cout<<"Total Timeouts = "<<S.Mcs.ttlTimeouts<<endl;
	cout<<"Fraction of Customers timed out = "<<(S.Mcs.ttlTimeouts)/(S.Mcs.totalArr)<<endl;
	return 0;

}
