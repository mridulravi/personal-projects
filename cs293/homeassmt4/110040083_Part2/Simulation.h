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
  double sumWaitTimes;		   //performance metrics
    
  int customersArrived;		   //How many customers have arrived for service
  int customersDeparted;           //How many customers have finished service
  int customersDropped;		   //How many customers gone without being served
				   //because of full buffer
  int MaxBufReached;		   //Max queue length reached (excluding those in service)
  double MaxWaitTime;		   // Max waiting time
  map<double,double> serviceTime;  //<arrival time, service time> map
  
 public:
  
  vector<double> waitTimeVector;  // vector for storing the waiting times
  vector<double>::iterator it;    
  vector<double> speedvector;     // vector for storing the server speeds
  vector<double>::iterator its;
  Server* tmpS;
  list<Server>::iterator SvrIt;
  list<Server> ServerList;	  // servers list
  int Sn;			  // no of servers
  int Buffer_Size;		  // maximum permissible buffer length
  double S;			  // step size by which server speed is changed at a probe
  double P;			  // probe intervel
  // Min speed, Max speed that the server can operate at (in MIPS)
  double min_speed, max_speed,serverSpeed;
  // Job Queue size thresholds
  int Jlow, Jhigh;
  // request no.
  int reqID;
  // for output to server.log and request.log
  ofstream ReqOut;
  ofstream SerOut;
  // variable for storing processing_end times
  // and last arrival ( used in probe event handler)
  double temp,Maxtemp,LastArrival;
  int ProbeNumber;
  //Constructor, initializes the simulation.
  Simulation() {
   		double a, s;    		
		cout<<"Number of servers(s) : ";
		cin >> Sn;
		cout<<"Maximum number of requests that are waiting in the system not including those in service :";
		cin >> Buffer_Size;
		cout<<"Min speed, Max speed that the server can operate at (in MIPS) : ";
		cin >> min_speed >> max_speed;
		cout<<"Step size S (in mips) : ";
		cin >> S;
		cout<<"probe interval P (in seconds) : ";
		cin >> P;
		cout<<"Job Queue size thresholds : ";
		cin >> Jlow >> Jhigh;

		//Forming list of servers and alloting numbers to them
		//initially all are idle
		// and have no req in service
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
    
    sumWaitTimes=0.0;
    customersArrived =0;
    customersDeparted =0;
    customersDropped=0;
    MaxBufReached=0;
    MaxWaitTime=0.0;
    reqID=0;
    temp=0;
    
    ProbeNumber=1;
    ReqOut.open("request.log");
    SerOut.open("server.log");
    serverSpeed=min_speed;
    //create the first arrival event, by reading standard input for an arrival
    //time and a service time
    cin >> a >> s;
    LastArrival = a;
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
      Maxtemp=a+(s/serverSpeed);
      eventList.push(e);          //Now that event is created, throw
				  //it into the priority queue.
      static Event firstprobe(0,PROBE,P,0);
      eventList.push(firstprobe);
      customersArrived++;
    
    }
  }
  
  void run(QueueingSystem q);     // Will start the event handling

  //Event handlers
  void arrival_event_handler(Event e);   
  void departure_event_handler(Event e);
  void probe_event_handler(Event e);
};
  
#endif
  
  
