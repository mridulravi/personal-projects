/*************************
Event class describes a simulation "event". A simulation "event" is
defined by an ID, a type and a time at which the event is scheduled.
**********************/

#ifndef EVENT_H                           // avoid repeated expansion
#define EVENT_H
#include <iostream>
using namespace std;

//Enumerated type and namespace to use mnemonics for Event types
namespace EventTypeNames { enum eventType {ARRIVAL,DEPARTURE};}
using namespace EventTypeNames;

class Event {

 private:
  int ID;
  eventType type; 
  double time;
  
 public:
  Event() {ID=0; type=ARRIVAL; time=0.0;}  //default constructor
					   //creates an arrival event
					   //at time 0
  Event(int id, eventType ty, double ti);  
  bool operator<(const Event& e) const;   //overload "<" to compare events
  void print(ostream & outstream=cout) const; //forgot why I needed this
  double getTime() const;                   //accessor method
  int getType() const;                      //accessor method
};


#endif
