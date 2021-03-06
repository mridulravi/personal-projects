/*****************

Main Simulation class. Comprises of an event list, a current
simulation clock, a queueing system that is being simulated and some
counters and metrics.

************/

#ifndef SIMULATION_H                           // avoid repeated expansion
#define SIMULATION_H
#include<iostream>
#include<queue>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include<math.h>
#include "Event.h"
#include "QueueingSystem.h"

class Simulation {

 private:
  priority_queue<Event> eventList; //Eventlist implemented using STL
				   //priority queue. This will allows
				   //us to get the "most imminent
				   //event" in O(1) time. I think the 
				   //"less than" operator in event is
				   //reversed because by default STL
				   //pq is a max-heap, whereas we want
				   //a min-heap. Please verify this

  double simTime;                  //Simulation clock.
  QueueingSystem sys;              //The system being simulated

  double sumRespTimes;             //Intermediate counters for
				   //performance metrics
  double sumServTimes; 
  double sumWaitTimes;   
  int customersArrived;
  int customersDeparted;           //How many customers have finished service
  int customersDropped;
  int MaxBufReached;
  double MaxWaitTime;
  map<double,double> serviceTime;  //<arrival time, service time> map
  
 public:
  
  vector<double> myvector;
  vector<double>::iterator it;
  Server* tmpS;
  list<Server>::iterator SvrIt;
  list<Server> ServerList;
  int Sn;
  int Buffer_Size;
  double S;
  double P;
  double min_speed, max_speed,serverSpeed;
  int Jlow, Jhigh;
  int reqID;
  ofstream ReqOut;
  //Constructor, initializes the simulation.
  Simulation() {
   		double a, s;    		
		cout<<"Number of servers(s) : ";
		cin >> Sn;
		cout<<"Maximum number of requests that are waiting in the system not including those in service :";
		cin >> Buffer_Size;
		cout<<"Min speed, Max speed that the server can operate at (in MIPS - million instructions per second) : ";
		cin >> min_speed >> max_speed;
		cout<<"Step size S (in mips) : ";
		cin >> S;
		cout<<"probe interval P (in seconds) : ";
		cin >> P;
		cout<<"Job Queue size thresholds : ";
		cin >> Jlow >> Jhigh;

		//Forming list of servers and alloting numbers to them
		for(int i=0;i < Sn;i++)
		{
			tmpS = new Server;
			tmpS->busy =0;
			tmpS->ID=(i+1);
			tmpS->reqInService=NULL;
			ServerList.push_back(*tmpS);
		}
    //Initialize clock and all counters/accummulators 

    simTime = 0.0;                  
    sumRespTimes=0.0;
    sumServTimes=0.0;
    sumWaitTimes=0.0;
    customersArrived =0;
    customersDeparted =0;
    customersDropped=0;
    MaxBufReached=0;
    MaxWaitTime=0.0;
    reqID=0;
    ReqOut.open("request.log");
    serverSpeed=min_speed;
    //create the first arrival event, by reading standard input for an arrival
    //time and a service time
    cin >> a >> s;

    //a=-1 indicates end of input
    if (a != -1) {
      static Event e(0,ARRIVAL,a,0);//create an event with ID 0, as
				    //this will be the first event, and
				    //we know it is an ARRIVAL event at
				    //time "a" as was read from
				    //input. This needs to be "static"
				    //because the Event just created
				    //should live after function
				    //exits.
      serviceTime[a] = s/serverSpeed; //Stores the service time 's' of
				    //the request that arrived at time 'a'

      eventList.push(e);          //Now that event is created, throw
				  //it into the priority queue.
      customersArrived++;
      sumServTimes+=s;
    }
  }
  
  void run(QueueingSystem q);     // Will start the event handling

  //Event handlers
  void arrival_event_handler(Event e);   
  void departure_event_handler(Event e);
};
  
#endif
  
  
