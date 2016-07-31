#ifndef HILBERT_HH
#define HILBERT_HH
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class wff
{
public:
	char val;
//	bool atomic;
	wff * lhs;
	wff * rhs;
	void implement_dt();
	void print();
	
	wff(wff * a, wff *b, char c);
	
};

#endif
