/*****************

Main Simulation class. Comprises of an event list, a current
simulation clock, a queueing system that is being simulated and some
counters and metrics.

************/

#ifndef SIMULATION_H                           // avoid repeated expansion
#define SIMULATION_H

#include<queue>
#include<map>
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
  int customersDeparted;           //How many customers have finished service
  int customersDropped;
  map<double,double> serviceTime;  //<arrival time, service time> map
				   

 public:

  //Constructor, initializes the simulation.
  Simulation() {
    double a, s;
    
    //Initialize clock and all counters/accummulators 

    simTime = 0.0;                  
    sumRespTimes=0.0;
    customersDeparted =0;
    customersDropped=0;
    //create the first arrival event, by reading standard input for an arrival
    //time and a service time
    cin >> a >> s;

    //a=-1 indicates end of input
    if (a != -1) {
      static Event e(0,ARRIVAL,a); //create an event with ID 0, as
				   //this will be the first event, and
				   //we know it is an ARRIVAL event at
				   //time "a" as was read from
				   //input. This needs to be "static"
				   //because the Event just created
				   //should live after function
				   //exits. 
      
      serviceTime[a] = s;          //Stores the service time 's' of
				   //the request that arrived at time 'a'

      eventList.push(e);          //Now that event is created, throw
				  //it into the priority queue. 
    }
  }

  void run(QueueingSystem q);     // Will start the event handling

  //Event handlers
  void arrival_event_handler(Event e);   
  void departure_event_handler(Event e);
};
  
#endif
  
  
