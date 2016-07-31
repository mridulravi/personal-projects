#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;


class state
{
	public:
	int num_miss; // no of missionaries on left bank
	int num_cann; // " "  " cannibals " "  "  "  "
	int bank; // 0:left, 1: right
	
	state()
	{}
	
	state( int n1, int n2, int b)
	{
		num_miss = n1;
		num_cann = n2;
		bank = b;
	}
};

class edge
{
	public:
	int i1;
	int i2;
	float cost;
	
	edge() 
	{}
	
	edge( int n1, int n2, float c)
	{
		i1 = n1;
		i2 = n2;
		cost = c;
	}
};

vector<state> states;
vector<edge> edges;
vector<float> h_vals;
int num_ppl; // no of missionaries/ cannibals


// return index of goal state
int find_goal()
{
	for(int i=0; i< states.size(); i++)
	{
		if((states[i].num_miss == 0) && (states[i].num_cann == 0) && (states[i].bank == 1))
		{
			return i;
		}
	}
	
	return -1; // error
	
}

void compute_h_values_n_minus_1(int goal)
{

	for(int i=0;i<states.size(); i++)
	{
		if ( i == goal)
			h_vals.push_back(0);
		else
		{
			h_vals.push_back(states[i].num_miss + states[i].num_cann - 1);
		}	
	}
}


void compute_h_values_n_by_2(int goal)
{

	for(int i=0;i<states.size(); i++)
	{
		if ( i == goal)
			h_vals.push_back(0);
		else
		{
			h_vals.push_back((states[i].num_miss + states[i].num_cann) / 2.0);
		}	
	}
}

void compute_h_values_2n_minus_1(int goal)
{

	for(int i=0;i<states.size(); i++)
	{
		if ( i == goal)
			h_vals.push_back(0);
		else
		{
			h_vals.push_back(2*(states[i].num_miss + states[i].num_cann) - 1);
		}	
	}
}

void compute_h_values_2n_plus_1(int goal)
{

	for(int i=0;i<states.size(); i++)
	{
		if ( i == goal)
			h_vals.push_back(0);
		else
		{
			h_vals.push_back(2*(states[i].num_miss + states[i].num_cann) + 1);
		}	
	}
}



bool edge_exist( edge e)
{
	for(int i=0; i< edges.size(); i++)
	{
		int i1 = edges[i].i1;
		int i2= edges[i].i2;
		
		if( ( e.i1 == i1 && e.i2 == i2 ) || ( e.i2 == i1 && e.i1 == i2))
			return true;
	}
	return false;

}

int state_exist(state s)
{
	for(int i=0; i< states.size(); i++)
	{
		int left = states[i].num_miss;
		int right = states[i].num_cann;
		int bank = states[i].bank;
		
		if((s.num_miss == states[i].num_miss) && (s.num_cann == states[i].num_cann) && (s.bank == states[i].bank) )
			return i;
	}
	return -1;
}

vector<state> find_nbrs(state s)
{
	vector<state> v;
	int miss = s.num_miss;
	int cann = s.num_cann;
	int bank = s.bank;
	
	if( bank == 0) // on left bank currently
	{
		// 2 missionaries cross
		if( (miss >= 2) && ( ((miss-2) >= cann) || ((miss-2) == 0 ) ) && ((3-miss+2)>=(3-cann)) ) 
		{
			state s1 (miss -2 , cann, 1);
			v.push_back(s1);
		}
		
		// 2 cannibals cross
		if( (cann >= 2) && ( (miss >= (cann-2)) || (miss == 0 ) ) && ( ((3-miss)>=(3-cann+2)) || (miss == 3 ) ) ) 
		{
			state s1 (miss , cann - 2, 1);
			v.push_back(s1);
		}
		
		// 1 missionary crosses
		if( (miss >= 1) && ( ((miss-1) >= cann) || ((miss-1) == 0 ) ) &&  ((3-miss+1)>=(3-cann)) ) 
		{
			state s1 (miss - 1 , cann, 1);
			v.push_back(s1);
		}
		
		// 1 cannibal crosses
		if( (cann >= 1) && ( (miss >= (cann - 1)) || (miss == 0 ) ) && ( ((3-miss)>=(3-cann+1)) || (miss == 3 ) ) ) 
		{
			state s1 (miss  , cann - 1, 1);
			v.push_back(s1);
		}
		
		// 1 missionary and 1 cannibal cross
		if( (miss >= 1) && (cann >=1) && ((miss-1) >= (cann -1))  && ((3-miss+1)>=(3-cann+1)) ) 
		{
			state s1 (miss -1 , cann -1, 1);
			v.push_back(s1);
		}
	}
	
	else if (bank == 1) //on right bank currently
	{
		// 2 missionaries cross
		if( ((3-miss) >= 2) && ((miss+2) >= cann) && ( ((3-miss-2)>=(3-cann)) || ((3-miss-2) == 0 )  ) ) 
		{
			state s1 (miss +2 , cann, 0);
			v.push_back(s1);
		}
		
		// 2 cannibals cross
		if( ((3-cann) >= 2) && ( (miss >= (cann+2)) || (miss == 0 ) ) && ( ((3-miss)>=(3-cann-2)) || ((3-miss) == 0 ) ) ) 
		{
			state s1 (miss , cann + 2, 0);
			v.push_back(s1);
		}
		
		// 1 missionary crosses
		if( ((3-miss) >= 1) && ((miss+1) >= cann) && ( ((3-miss-1)>=(3-cann)) || ((3-miss-1) == 0 ) )) 
		{
			state s1 (miss + 1 , cann, 0);
			v.push_back(s1);
		}
		
		// 1 cannibal crosses
		if( ((3-cann) >= 1) && ( (miss >= (cann + 1)) || (miss == 0 ) ) && ( ((3-miss)>=(3-cann-1)) || ((3-miss) == 0 ) ) ) 
		{
			state s1 (miss  , cann + 1, 0);
			v.push_back(s1);
		}
		
		// 1 missionary and 1 cannibal cross
		if( ((3-miss) >= 1)&&((3-cann) >=1) && ((miss+1) >= (cann+1)) &&  ((3-miss-1)>=(3-cann-1)) ) 
		{
			state s1 (miss +1 , cann +1, 0);
			v.push_back(s1);
		}
	
	}
	
	return v;
}

void find_all_states()
{
	int curr = 0;
	while ( curr < states.size() )
	{
		state s = states[curr];
		vector<state> neighbours = find_nbrs(s);
		for(int i=0; i< neighbours.size(); i++)
		{
			int index = state_exist(neighbours[i]); // find index of state if it exists, else -1
			if ( index == -1)
			{
				// push back into states, add edge ( cost is 1 for all neighbours)
				states.push_back(neighbours[i]);
				edge e( curr, states.size() -1, 1);
				edges.push_back(e);
			}
			
			else 
			{
				edge e( curr, index, 1);
				if(!edge_exist(e))
					edges.push_back(e);
			}
		}
		
		curr++;	
	}
}

int main()
{
	num_ppl = 3;
	state s(num_ppl,num_ppl, 0);
	states.push_back(s);
	
	find_all_states(); // push all the states in vector, also make edges
	
	// print num states and num edges
	cout<<states.size()<<endl;
	cout<<edges.size()<<endl;
	
	// print edges
	for(int i=0; i<edges.size(); i++)
	{
		cout<< edges[i].i1 << " " << edges[i].i2 << " " << edges[i].cost <<endl;
	}
	
	// print start and goal node id ( start node index = 0)
	int start_node = 0;
	int goal_node = find_goal();
	if ( goal_node == -1) 
	{
		cout<< "goal node not found\n";
		exit(1);
	}
	cout<< start_node << " " << goal_node << endl;
		
	//compute all h values and print
	compute_h_values_n_by_2(goal_node);
	for(int i=0; i< h_vals.size(); i++)
	{
		cout<< h_vals[i] << endl;
	}
}
