//Generic server of a queueing system
#include "Request.h"
#include<cstdlib>
#include<iostream>
class Server {


  public:

  int ID;
  bool busy;
  
  //double cummulativeBusyPeriod;
  //double serviceFinishTime;

  Request* reqInService;


  Server(int id=0, bool b=0) {
    ID = id;
    busy=b;
    //cummulativeBusyPeriod=0;
    //serviceFinishTime=MAXDOUBLE;
    reqInService=NULL;
  }
    
  bool isBusy(){ return busy;}  
  //Request & getReqInService();

  //void setReqInService(Request& reqInService);
};
