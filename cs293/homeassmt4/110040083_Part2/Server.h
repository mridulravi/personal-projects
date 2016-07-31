//Generic server of a queueing system
#include "Request.h"
#include<cstdlib>
#include<iostream>
class Server {


  public:

  int ID;			// server's ID
  bool busy;			// 0 if idle, 1 if busy

  Request* reqInService;	// Pointer to request in service

  Server(int id=0, bool b=0) {
    ID = id;
    busy=b;
    reqInService=NULL;
  }
    
  bool isBusy(){ return busy;}  
};
