#include "hilbert.hh"

vector<wff*> lhs_print;

wff::wff(wff *a, wff *b, char c)
{
		lhs = a;
		rhs = b;
		val = c;
}

void wff::implement_dt()
{
	
	
	if(rhs==NULL)		//Will apply the f transformation using axiom 3
	{
		
		
		if(val!='f')
		{
			int itr=0;
			for(itr=0;itr<lhs_print.size();itr++)
			{
				lhs_print[itr]->print();
				cout<<",";
			}
			
			cout<<"(";
			print();
			cout<<"->f)";
		
			cout<<"\t Derives\t";
			cout<<"f\n";
		}
		
		
	}
	else
	{
		int itr=0;
		for(itr=0;itr<lhs_print.size();itr++)
		{
			lhs_print[itr]->print();
			cout<<", ";
		}
		
		//print LHS
		lhs->print();
		cout<<"\t Derives\t";
		rhs->print();
		cout<<endl;
		lhs_print.push_back(lhs);
		rhs->implement_dt();
	}
}

void wff::print()
{
	if(rhs==NULL)
	{
		cout<<val;
		return;
	}

	cout<<"(";
	lhs->print();
	cout<<"->";		
	rhs->print();
	cout<<")";
	return;
}

