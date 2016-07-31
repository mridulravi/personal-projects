#include "heap2.h"
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main()
{
	vector<object.IDtype> first; 
	BinaryHeap<int> P(first);
	//cout<<"enter  current size :";
	//cin >> currentsize
	cout<<P.isEmpty();cout<<endl;
	P.insert(2);P.display();cout<<P.isEmpty();cout<<endl;
	P.deleteMin();cout<<P.isEmpty();cout<<endl;P.displaypos();//P.deleteMin();
	P.insert(9);P.display();cout<<endl;cout<<P.findmin()<<endl;
	P.insert(4);P.display();cout<<endl;cout<<P.findmin()<<endl;
	P.insert(6);P.display();cout<<endl;cout<<P.findmin()<<endl;//P.makeEmpty();
	cout<<P.findmin()<<endl;P.displaypos();cout<<endl;
	//cout<<P.isEmpty();cout<<endl;
	P.insert(0);P.display();cout<<endl;cout<<P.findmin()<<endl;P.displaypos();cout<<endl;
	P.insert(39);P.display();cout<<endl;P.deleteMin();cout<<P.findmin()<<endl;
	P.insert(22);P.display();cout<<endl;cout<<P.findmin()<<endl;
	P.insert(43);P.display();cout<<endl;cout<<P.findmin()<<endl;
	P.insert(31);P.display();cout<<endl;cout<<P.findmin()<<endl;
	P.deleteMin();cout<<P.findmin()<<endl;
	cout<<P.contains(2)<<endl;
	P.display();cout<<endl;
	P.displaypos();cout<<endl;
	return 0;
}
