/**********
Implements the methods of the Simulation class. Simulation comprises
of the main event processing loop, and the handling of the events.
 *********/

#include "Event.h"
#include "Simulation.h"
#include "QueueingSystem.h"
#include "declarations.h"
using namespace std;

void Simulation::run(QueueingSystem q){
  Event nextEvent;

  //Process events until no more events in the event list
  while (!eventList.empty()) {
    //Pop next event 
    nextEvent = eventList.top();
    eventList.pop();

    //Advance simulation clock to time of this event
    simTime = nextEvent.getTime();
    cout << "Simtime: " << simTime << " Event Type= " << nextEvent.getType() ;
    //Event handling switch. Call the correct event handler  based on event type.
    if (nextEvent.getType() == ARRIVAL)  
      {arrival_event_handler(nextEvent);/*cout<< " Size of Buffer = "<< sys.Buffersize() <<endl;*/}
    else if (nextEvent.getType() == DEPARTURE) 
      {departure_event_handler(nextEvent);/*cout<< " Size of Buffer = "<< sys.Buffersize() <<endl;*/}
  }
  //Simulation loop over, now calculate and print the  average response time 
  cout << "Customers Dropped = "<< customersDropped << endl;
  cout << "Customers Departed = "<< customersDeparted << endl;
  cout << "Avg response time = " <<
    q.setAvgResponseTime(sumRespTimes/customersDeparted) << endl;
}


/*****
Arrival event handler first creates request object from the event
information. Then checks if queueing system is busy. If busy,
request must be enqueued, else, processing can start
immediately. Arrival event handler also looks up the next arrival and
creates the next arrival event.
*****/

void Simulation::arrival_event_handler(Event e) {
  //There are some couts here for debugging. Commented those out. Not removed.
  
  //  cout << "At time=" << e.getTime() << "  Arrival Event Handled\n";
  
  //Process the arrival. First create request object from event time,
  //which is the request arrival time, which allows us to get the
  //service time from the map that was created earlier
  Request req(0,e.getTime(),serviceTime[e.getTime()]); 
  
//  cout << "In aeh service time of " << e.getTime() << " is " << serviceTime[e.getTime()] << endl;

  //Check if system busy
  if (!sys.isBusy()) {
    //       cout << "Req service time=" << req.getServiceTime() << endl;

    //If not busy  start service, (Schedule departure
    //event). Departure event time is current time plus service time
    Event serviceEvent(0,DEPARTURE,simTime+req.getServiceTime());     
    //    cout << serviceEvent << endl;

    //Add departure event into event list.
    eventList.push(serviceEvent);  
  }

  //Put newly created request in queueing system buffer
  //If it came to an idle server, processing will start immediately
  //(departure event would have gotten created in the if block above)
   if (sys.Buffersize() < 5) 
	sys.enqueue(req);// if x is the buffer size(as per assg. statement), do it < x+1
   else 
	customersDropped++;
  cout<< " Size of Buffer = "<< sys.Buffersize() << endl;
  //Schedule next arrival - read next arrival and service times, put into event list   
   //Read comments in Simulation.h
  double a, s;
  cin >> a >> s;
  //  cout << "a=" << a << "s=" << s << endl;
  if (a != -1) {
    Event  arrivalEvent(0,ARRIVAL,a);
    eventList.push(arrivalEvent);
    serviceTime[a] = s;
  }  
  //cout << "service time of " <<a<< " is "<< serviceTime[a];

}


/*******
Departure event handler needs to deque and update performance metric
accummulators, and reset system busy state if necessary. If queue is
not empty, departure event for the next request should be created and
added to event list
**********/
void Simulation::departure_event_handler(Event e) {

  //Dequeue done request
  Request reqdone = sys.dequeue();
  cout<< " Size of Buffer = "<< sys.Buffersize() << endl;
  //  cout <<"At time=" << e.getTime() << "request arrived at " << 
  //    reqdone.getArrivalTime() << " departed" << endl;

  //Update counters, metrics
  customersDeparted++;

  //When customer departs, we get one response time sample, add it to
  //the sum which we will later use for average. This is where we use
  //the arrival time that was stored in the request object
  sumRespTimes += e.getTime()- reqdone.getArrivalTime(); 
							 							 
  //cout << e.getTime()- reqdone.getArrivalTime() << endl;
 
 if (sys.isBusy()) {  // System is not empty, so it can be busy 
   Request reqNext = sys.nextReq(); //Returns without dequeuing, the
				    //request object that is being
				    //currently processed

   //This request's departure needs to be scheduled, i.e. created and added to
   //event list
   Event serviceEvent(0,DEPARTURE,simTime+reqNext.getServiceTime()); //create event 
    //    cout << serviceEvent << endl;
   eventList.push(serviceEvent);  //add to event list
  }
} 
