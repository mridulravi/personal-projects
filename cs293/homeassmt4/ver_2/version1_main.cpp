#include<iostream>
#include<queue>
#include<math.h>
#include"version1.h"

using namespace std;

int main()
{	int x;
	Simulator S;
	cout<<"Enter Inter Arrival Time Range"<<endl;
	cin>>S.Arrmin>>S.Arrmax;
	cout<<"Enter Service Time Range"<<endl;
	cin>>S.Sermin>>S.Sermax;

	cout<<"Enter maximum Departures"<<endl;
	cin>>S.Depmax;

	cout<<"Enter maximum Buffer length"<<endl;
	cin>>x;
	S.Bfr.maxsize = x-1;
	cout<<endl;
	S.start();
		cout<<endl;
	cout<<"Average Waiting Time = "<<S.Mcs.CalculateAvgWaitTime()<<endl;
	cout<<"Total Departures = "<<S.Mcs.totalDep<<endl;
	cout<<"Total Arrivals = "<<S.Mcs.totalArr<<endl;
	cout<<"Fraction of Customers Successfully Serviced = "<<(S.Mcs.totalDep)/(S.Mcs.totalArr)<<endl;
	cout<<"Fraction of time Server was busy= "<<S.Mcs.AvgTimeSvrBusy<<endl;
	cout<<"Average Queue length = "<<S.Mcs.Queuelength<<endl;
	cout<<"Fraction of Customers Out due to full buffer = "<<S.Mcs.CalculateFractionBfrfull()<<endl;

	return 0;

}
