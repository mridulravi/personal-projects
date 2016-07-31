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
  priority_queue<Request> buffer;      //buffer is an STL queue of Requests

  //bool serverBusy;                    //1 if busy, 0 if not
  double avgResponseTime;             //average time from joining the
				      //queue till finishing service

 public:
  Server* tmpS;
  list<Server> svrlist;				   
  list<Server>::iterator svri;
  void enqueue(Request r);
  Request dequeue();
  Request nextReq(); 
  int Buffersize();                 
  //bool isBusy();
  double setAvgResponseTime(double avg){return avgResponseTime=avg;}
  QueueingSystem()
	{		
		/*//Forming list of servers and alloting numbers to them
		for(int i=0;i < 1/*Sn;i++)
		{
			tmpS = new Server;
			tmpS->busy =0;
			tmpS->ID=(i+1);
			tmpS->reqInService=NULL;
			svrlist.push_back(*tmpS);
		}*/
	}//Constructor that initiates empty queueing system
				      
};
#endif  
