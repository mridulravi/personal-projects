#include "Event.h"
#include "declarations.h"
using namespace std;

Event::Event(int id=0, eventType ty=ARRIVAL, double ti=0.0) {
  ID=id; type=ty; time=ti;
}

//Overload "less than" operator
//Less then is redefined to make it work with the STL priority queue
//which is a max-heap. We want min-heap.
//This will get the needed effect.
bool Event::operator<(const Event& e) const  {
  return (time > e.time);
}
void Event::print(ostream & outstream) const {
  outstream << "ID: " << ID << ", type=" << type << ", time=" << time << endl;
}
  
double Event::getTime() const { return time;}
int Event::getType() const {return type;}
