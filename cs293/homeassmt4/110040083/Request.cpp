#include "Request.h"

//Constructor with argument defaults
Request::Request(int id=0, double atime=0.0, double stime=0.0) {
  
  ID = id;
  serverAssigned=0;
  arrivalTime=atime;
  serviceTime=stime;
}

//Operator overload, a request r1 is "less than" a request r2 if the 
//"age" of r1 in the system is lesser than the "age" of r2.
//This will happen if r1's arrival time is greater (more recent) than
//r2's arrival time

bool Request::operator<(const Request& r) const  {
  return (arrivalTime > r.arrivalTime);
}

double Request::getArrivalTime() {
  return arrivalTime;
}
  
double Request::getServiceTime() {
  return serviceTime;
}

int Request::getID() {
  return ID;
}
