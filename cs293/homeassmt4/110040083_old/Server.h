//Generic server of a queueing system
#include "Request.h"
 
class Server {


 private:

  int ID;
  bool busy;
  
  double cummulativeBusyPeriod;
  double serviceFinishTime;

  Request* reqInService;

 public:
  Server(int id=0, bool b=0) {
    ID = id;
    busy=b;
    cummulativeBusyPeriod=0;
    serviceFinishTime=MAXDOUBLE;
    reqInService=NULL;
  }
    
  bool isBusy();  
  Request & getReqInService();

  void setReqInService(Request& reqInService);
}
