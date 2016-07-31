#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"version1.h"
using namespace std;



Simulator::Simulator()
{
	ttlBfrlength = 0;
	Sn =1;
}
	
void Simulator::start() //starts simulation and simultaneously updates metrics.
{	int i,flag;
	//First Customer Initialize 
	tmpC = new Customer;
	tmpC->id = 1;
	initialTime = rg.Generate(Arrmin,Arrmax);
	tmpC->arrtime = initialTime;
	CurrentEvent.C = tmpC;
	CurrentEvent.time = initialTime;
	CurrentEvent.type = "arrival";
	CurrentTime = initialTime;
	//Bfr.maxsize = 20-Sn;
	//BusySvr = 0;
	lastEventTime = initialTime;
		
	//Forming Server
	tmpS = new Server;
	tmpS->state =0;
	tmpS->setnum(1);
	svrlist.push_back(*tmpS);
		
	//cout<<"CurrentTime"<<"\t"<<"Event type"<<"  "<<"\t"<<"Server 1 state"<<"\t"<<"Server 2 "<<endl;
	cout<<"Time"<<"\t"<<"Event_Type"<<"\t"<<"Customer_No."<<"\t"<<"Buffer_length"<<"\t";
	for(svri=svrlist.begin();svri!=svrlist.end();svri++)
	{
		cout<<"Server"<<svri->num()<<"_state"<<"\t";
	}
	cout<<"Next_Event(time-type)"<<endl;
	
	
	//Starting Simulation
	while(Mcs.totalDep < Depmax)
	{	
		ttlBfrlength = ttlBfrlength + (CurrentTime - lastEventTime)*(Bfr.Q.size()); //Calculation of Bufferlength average
		Mcs.ttlTimeBusySvr = Mcs.ttlTimeBusySvr + (CurrentTime - lastEventTime)*(Mcs.BusySvr); //Calculation of server utility
		//cout<<ttlBfrlength<<endl;
		if(CurrentEvent.type == "arrival") 
		{	
			//cout<<"Arrival Event"<<endl;
			Mcs.totalArr++;
			Bfr.arrival(CurrentEvent.C);
			
			//next arrival event formation
			temp = new Event;
			temp->time = CurrentTime + rg.Generate(Arrmin,Arrmax);
			temp->type = "arrival";
			tmpC = new Customer;
			tmpC->id = ((CurrentEvent.C)->id) + 1;
			tmpC->arrtime = temp->time;
			temp->sn = 0;
			(CurrentEvent.C)->next = tmpC;
			temp->C = tmpC;
			El.AddEvent(*temp);
			//checking wether there is an idle server
			if(Bfr.full == 0) //if buffer is not full
			{
				svri = svrlist.begin();
				flag=0;
				while(svri != svrlist.end())
				{ 
					if(svri->state == 0) //if idle server found
					{
					
						//forming departure event of current customer
						temp = new Event;
						temp->time = CurrentTime + rg.Generate(Sermin,Sermax);
						temp->type ="departure";
						temp->C = CurrentEvent.C;
						temp->sn = svri->num();
						
						svri->currentC = CurrentEvent.C;
						
						svri->state = 1;
						//ttlTimeBusySvr
						//svri->stateChngTime = CurrentTime;
						Bfr.departure();
						Mcs.BusySvr++;
						El.AddEvent(*temp);
						flag=1;
						break;
						//Mcs.avgWaitTime = (Mcs.avgWaitTime*Mcs.totalDep)/(Mcs.totalDep + 1);
					}
					else{svri++;}
				}
				
				//display of simulation
				cout<<CurrentTime<<"\t"<<CurrentEvent.type;
		   		cout<<"\t"<<"\t"<<((CurrentEvent.C)->id)<<"\t"<<"\t"<<(Bfr.Q.size())+Mcs.BusySvr<<"\t"<<"\t";
		   		for(svri=svrlist.begin();svri!=svrlist.end();svri++)
				{
					if(svri->state ==1){cout<<"busy"<<"\t"<<"\t";}
					else{cout<<"idle"<<"\t"<<"\t";}
				}
				cout<<((El.lst).top()).time<<"-"<<((El.lst).top()).type<<endl;
			
			}
			else{cout<<CurrentTime<<"\t"<<"Customer no. "<<(CurrentEvent.C)->id<<" turned away due to full buffer"<<endl;}
			
		}
		else if(CurrentEvent.type == "departure") //Handling Departure Event 
		{	//cout<<"Departure Event"<<endl;
			Mcs.totalDep++;
			if(Bfr.Q.size() != 0) 
			{	//cout<<"Buffer not empty"<<endl;
			
				//Scheduling next departure event if buffer is not empty
				temp = new Event;
				temp->time = CurrentTime  +rg.Generate(Sermin,Sermax);
				//cout<<temp->time<<endl;
				temp->type = "departure";
				//cout<<temp->type<<endl;
				temp->sn = CurrentEvent.sn;
				//cout<<temp->sn<<endl;
				temp->C = *(Bfr.Q.begin());
				//cout<<(temp->C)->id<<endl;
				//cout<<"Customer also set";
				Bfr.departure();
				El.AddEvent(*temp);
				Mcs.ttlWaitTime = Mcs.ttlWaitTime + CurrentTime - (temp->C)->arrtime ;
				
			}
			else if (Bfr.Q.size() == 0){
				//cout<<"Buffer Empty"<<endl;
				//Setting state of server idle if buffer is empty furthur
				svri = svrlist.begin();
				while(svri != svrlist.end())
				{if (svri->num() == CurrentEvent.sn) {svri->state = 0;
									Mcs.BusySvr--;
									break;}
				else {svri++;}}
				
			}
			//Display of simulation
		   	cout<<CurrentTime<<"\t"<<CurrentEvent.type;
		   	cout<<"\t"<<((CurrentEvent.C)->id)<<"\t"<<"\t"<<(Bfr.Q.size())+Mcs.BusySvr<<"\t"<<"\t";
		   	for(svri=svrlist.begin();svri!=svrlist.end();svri++)
			{
				if(svri->state ==1){cout<<"busy"<<"\t"<<"\t";}
				else{cout<<"idle"<<"\t"<<"\t";}
			}
			cout<<((El.lst).top()).time<<"-"<<((El.lst).top()).type<<endl;
			
			
		}
		//calling next event
		lastEventTime = CurrentTime;
		CurrentEvent = El.DoEvent();
		CurrentTime = CurrentEvent.time;
	}
	//calculating averages when all simulations are done
	Mcs.CbfrFull = Bfr.Outs;
	Mcs.Queuelength = ttlBfrlength/lastEventTime;
	Mcs.AvgTimeSvrBusy = Mcs.ttlTimeBusySvr/(Sn*lastEventTime);
}	

