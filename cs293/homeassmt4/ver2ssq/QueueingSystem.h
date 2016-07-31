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

#include<queue>                        //STL queue template
using namespace std;              
#include "Request.h"                   //defines Request class

class QueueingSystem {             
  
 private:
  priority_queue<Request> buffer;      //buffer is an STL queue of Requests

  bool serverBusy;                    //1 if busy, 0 if not
  double avgResponseTime;             //average time from joining the
				      //queue till finishing service
 public:
  void enqueue(Request r);
  Request dequeue();
  Request nextReq();                  
  bool isBusy();
  double setAvgResponseTime(double avg){return avgResponseTime=avg;}
  QueueingSystem() {serverBusy=false;} //Constructor that initiates
				       //empty queueing system
};
#endif  
