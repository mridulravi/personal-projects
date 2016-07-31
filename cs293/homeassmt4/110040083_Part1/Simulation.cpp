/**********
Implements the methods of the Simulation class. Simulation comprises
of the main event processing loop, and the handling of the events.
 *********/

#include "Event.h"
#include "Simulation.h"
#include "QueueingSystem.h"
#include "declarations.h"
//#include "Server.h"
using namespace std;

void Simulation::run(QueueingSystem q){
  Event nextEvent;
  cout << endl;
  //Process events until no more events in the event list
  while (!eventList.empty()) {
    //Pop next event 
    nextEvent = eventList.top();
    eventList.pop();
    //Advance simulation clock to time of this event
    simTime = nextEvent.getTime();
    cout << simTime;
    if (nextEvent.getType() == ARRIVAL)  
    {
	cout << " ARRIVAL ";
	
    }
    else if (nextEvent.getType() == DEPARTURE) 
    {
	cout << " DEPARTURE ";
    }
   if(sys.Buffersize() != 0)
	cout <<" ( "<<sys.nextReq().getArrivalTime()<<" , "<<sys.nextReq().getServiceTime()<<" ) ";
   else
	cout <<" ( INF , INF ) ";
   cout<< "  "<< sys.Buffersize() ;
	if(!eventList.empty())
	{
		if (eventList.top().getType() == ARRIVAL)		
		cout <<" ARRIVAL "<<endl;
		else if (eventList.top().getType() == DEPARTURE)		
		cout <<" DEPARTURE "<<endl;
	}
	else
		cout <<" NONE "<<endl;
 
    //Event handling switch. Call the correct event handler  based on event type.
    if (nextEvent.getType() == ARRIVAL)  
    {	
	arrival_event_handler(nextEvent);
    }
    else if (nextEvent.getType() == DEPARTURE) 
    {
	departure_event_handler(nextEvent);
    }
  }
  //Simulation loop over. 
  sort (myvector.begin(), myvector.end());
 
  cout << "Number of requests arrived (including dropped): "<< customersArrived << endl;
  cout << "Number of requests serviced: "<< customersDeparted << endl;
  cout << "Number of requests dropped: "<< customersDropped << endl;
  cout << "Average waiting time: " << q.setAvgWaitingTime(sumWaitTimes/customersDeparted) << endl;   					
  cout << "Average service time: " <<q.setAvgResponseTime(sumRespTimes/customersDeparted) -
				  q.setAvgWaitingTime(sumWaitTimes/customersDeparted) << endl;
  cout << "90%ile of waiting time: "<< myvector[ceil(0.9*myvector.size())-1]<<endl;
  cout << "Maximum waiting time: " << MaxWaitTime << endl;
  cout << "Max queue length reached: " << MaxBufReached << endl;

  ReqOut.close();
}


/*****
Arrival event handler first creates request object from the event
information. Then checks if queueing system is busy. If busy,
request must be enqueued, else, processing can start
immediately. Arrival event handler also looks up the next arrival and
creates the next arrival event.
*****/

void Simulation::arrival_event_handler(Event e) {
  
  //Process the arrival. First create request object from event time,
  //which is the request arrival time, which allows us to get the
  //service time from the map that was created earlier
  //cout << "Req ID = " << reqID<<endl;
  Request req(reqID,e.getTime(),serviceTime[e.getTime()]); 
  reqID++;
   if (sys.Buffersize() < Buffer_Size)
   {	
	sys.enqueue(req);	
	SvrIt = ServerList.begin();
	while(SvrIt != ServerList.end())
	{	
		if(SvrIt->busy == 0) //if idle server found
		{
			Request* tempReq;
			
			Request tempReq2=sys.dequeue();
			tempReq = &tempReq2;
			SvrIt->reqInService=tempReq;
			SvrIt->busy = 1;
			sumRespTimes += serviceTime[e.getTime()];
			myvector.push_back (0);
			
			ReqOut<<tempReq2.getID()<<"  "<<tempReq2.getArrivalTime()<<"  "<<simTime
			<<"  "<< simTime+tempReq2.getServiceTime()<<"  "<< simTime-tempReq2.getArrivalTime()
			<<"  "<< tempReq2.getServiceTime()<<endl;
			Event serviceEvent(0,DEPARTURE,simTime+(*tempReq).getServiceTime(),SvrIt->ID);
			eventList.push(serviceEvent);
			
			break; 
		}
		else
		{SvrIt++;}
	}
   }
   else 
	{customersDropped++;}

  if (sys.Buffersize() >= MaxBufReached)
	MaxBufReached = sys.Buffersize() ;
/*  if(sys.Buffersize() != 0)
	cout <<" ( "<<sys.nextReq().getArrivalTime()<<" , "<<sys.nextReq().getServiceTime()<<" ) ";
  else
	cout <<" ( INF , INF ) ";

  cout<< "  "<< sys.Buffersize() ;*/

  //Schedule next arrival - read next arrival and service times, put into event list.
  double a, s;
  cin >> a >> s;
  
  if (a != -1) {
    Event  arrivalEvent(0,ARRIVAL,a,0);
    eventList.push(arrivalEvent);
    serviceTime[a] = s/serverSpeed;
    customersArrived++;
    sumServTimes+=s;
  }  
 
}


/*******
Departure event handler needs to deque and update performance metric
accummulators, and reset system busy state if necessary. If queue is
not empty, departure event for the next request should be created and
added to event list
**********/
void Simulation::departure_event_handler(Event e) {

  //Update counters, metrics
  customersDeparted++;

 if (sys.Buffersize()!=0)
 {
   Request* tempReq ;				//Returns with dequeuing, the
   Request tempReq2 = sys.dequeue();		//request object that is being
   tempReq = &tempReq2;			        //currently processed
   if (sys.Buffersize() >= MaxBufReached)
	MaxBufReached = sys.Buffersize() ;
  /* if(sys.Buffersize() != 0)
	cout <<" ( "<<sys.nextReq().getArrivalTime()<<" , "<<sys.nextReq().getServiceTime()<<" ) ";
   else
	cout <<" ( INF , INF ) ";
   cout<< "  "<< sys.Buffersize() ;*/
				
   SvrIt = ServerList.begin();
   while(SvrIt != ServerList.end())
   {
	if (SvrIt->ID == e.getServerNo()) 
	{
		SvrIt->busy = 1;
		
		SvrIt->reqInService=tempReq;
		ReqOut<<tempReq2.getID()<<"  "<<tempReq2.getArrivalTime()<<"  "<<simTime
		<<"  "<< simTime+tempReq2.getServiceTime()<<"  "<< simTime-tempReq2.getArrivalTime()
		<<"  "<<tempReq2.getServiceTime()<<endl;
		sumRespTimes += e.getTime()- (*(SvrIt->reqInService)).getArrivalTime()+(*(SvrIt->reqInService)).getServiceTime();
		sumWaitTimes += e.getTime()- (*(SvrIt->reqInService)).getArrivalTime();
		myvector.push_back (e.getTime()- (*(SvrIt->reqInService)).getArrivalTime());
		if ((e.getTime()- (*(SvrIt->reqInService)).getArrivalTime()) >= MaxWaitTime)
			MaxWaitTime = (e.getTime()- (*(SvrIt->reqInService)).getArrivalTime()) ;	
		break;
	}
	else {SvrIt++;}
   }  
   //This request's departure needs to be scheduled, i.e. created and added to
   //event list
   Event serviceEvent(0,DEPARTURE,simTime+(*tempReq).getServiceTime(),e.getServerNo());  //create event 
   eventList.push(serviceEvent); 							 //add to event list	
   		
 }

 else if (sys.Buffersize() == 0)
 {
   if (sys.Buffersize() >= MaxBufReached)
	MaxBufReached = sys.Buffersize() ;
  /* if(sys.Buffersize() != 0)
	cout <<" ( "<<sys.nextReq().getArrivalTime()<<" , "<<sys.nextReq().getServiceTime()<<" ) ";
   else
	cout <<" ( INF , INF ) ";
   cout<< "  "<< sys.Buffersize() ;*/

   SvrIt = ServerList.begin();
   while(SvrIt != ServerList.end())
   {
	if (SvrIt->ID == e.getServerNo()) 
	{
		SvrIt->busy = 0;
		SvrIt->reqInService=NULL;	
		break;
	}
	else {SvrIt++;}
   }   	
 }
} 
