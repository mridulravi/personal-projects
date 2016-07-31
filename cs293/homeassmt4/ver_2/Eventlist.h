#include<iostream>
#include<queue>
#include<cstdlib>
#include<math.h>
#include<list>
#include<time.h>
#include"Event.h"
using namespace std;



class Compare
{
	public:
	bool operator() (Event a, Event b)
	{return (a.time >= b.time);}
};

class EventList{
	public:
	priority_queue<Event, vector<Event>, Compare> lst;
	void AddEvent(Event E)
	{lst.push(E);}
	
	Event DoEvent()
	{Event x;
	x = (lst.top());
	lst.pop();
	return x;}
};
