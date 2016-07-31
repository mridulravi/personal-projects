/*********
QueueingSystem is the class that captures all aspects of the queueing
system being simulated. A queueing system is defined by

a buffer for queueing requests
the server state
the performance metrics associated with the system

Operations are to enqueue, dequeue and setting the metrics
************/
#ifndef QS_H                           // avoid repeated expansion
#define QS_H

#include<list>
#include<queue>                        //STL queue template
using namespace std;              
#include "Request.h"                   //defines Request class
#include "Server.h"
class QueueingSystem {             
  
 private:
  queue<Request> buffer;      	      //buffer is an STL queue of Requests

  double avgResponseTime;             //average time from joining the
				      //queue till finishing service
  double avgWaitingTime;
  double avgServiceTime;
  

 public:
  int Sn;
  Server* tmpS;
  list<Server> svrlist;				   
  list<Server>::iterator svri;
  void enqueue(Request r);
  Request dequeue();
  Request nextReq(); 
  int Buffersize();                 
  
  double setAvgResponseTime(double Ravg){return avgResponseTime=Ravg;}

  double setAvgWaitingTime(double Wavg){return avgWaitingTime=Wavg;}

  double setAvgServiceTime(double Savg){return avgServiceTime=Savg;} 

  QueueingSystem()
	{}		
					      
};
#endif  
