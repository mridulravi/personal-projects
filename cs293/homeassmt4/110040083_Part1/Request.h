/*************
Describes a request in a  queueing system. A request is described by
an ID, which server it is assigned to run on (in case multiple
servers), its arrival time and its service time
******************/

#ifndef REQ_H                           // avoid repeated expansion
#define REQ_H

class Request {

 private:
  int ID;                     // ID to uniquely identify the request
  int serverAssigned;         //Which server, in case of multiple servers
  
  double arrivalTime;
  double serviceTime;         //Time required to process the request

 public:
  //Various accessor functions
  double getArrivalTime();   
  double getServiceTime();
  int getID();
  int getServerAssigned();
  
  //Overload the less than operator to compare Requests
  bool operator<(const Request& r) const;

  //Constructor: request should always be created with an ID, arrival
  //time, and service time
  Request(int id, double atime, double stime);
};

#endif
