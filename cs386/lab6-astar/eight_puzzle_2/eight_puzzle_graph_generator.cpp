#include<iostream>
#include<vector>
#include<stdlib.h>
#include<cmath>
using namespace std;

class state
{
	public:
	vector<int> tiles; // this has the tiles in row major form , blank : 9
	
	state()
	{}
	
	state( vector<int> v )
	{
		for(int i=0; i<v.size(); i++)
		{
			tiles.push_back(v[i]);
		}
	
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


// return index of goal state
int find_goal()
{
	for(int i=0; i< states.size(); i++)
	{
		bool flag = true; 
		for(int j=0; j<9; j++)
		{
			if( states[i].tiles[j] != j+1)
			{
				flag = false;
				break;
			}
			
		}
		if(flag)
			return i;
	}
	return -1;
}

int find_index(int k, vector<int> v)
{
	for(int i=0; i<v.size();i++)
	{
		if (v[i] == k)
			return i;
	}
}

void compute_h_values_manhattan(int goal)
{
	for(int i=0;i<states.size();i++)
	{
		int displacement = 0;
		for(int j=0; j<9; j++)
		{
			int index = find_index(j+1, states[i].tiles);
			int x1 = index/3;
			int x2 = j/3;
			int y1 = index%3;
			int y2 = j%3;
			
			displacement += (abs(x1-x2) + abs(y1-y2)); 
		}
		h_vals.push_back(displacement);
	}
}

void compute_h_values_num_displaced(int goal)
{
	// heuristic is num displaced tiles
	for(int i=0;i<states.size();i++)
	{
		int num_displaced = 0;
		
		for(int j=0; j<9; j++)
		{
			if( states[i].tiles[j] != j+1)
			{
				num_displaced++;
			}
			
		}
		
		h_vals.push_back(num_displaced);
	}
}


void compute_h_values_zero(int goal)
{
	for(int i=0;i<states.size();i++)
		h_vals.push_back(0);
}

///////////////////////////////////////////////////////
void compute_h_values_own_heuristic(int goal)
{
	// heuristic is manhattan dist of blank tile
	for(int i=0;i<states.size();i++)
	{
		int displacement =0 ;
		int index = find_index(9, states[i].tiles);
		int x1 = index/3;
		int x2 = 2;
		int y1 = index%3;
		int y2 = 2;
	
		displacement += (abs(x1-x2) + abs(y1-y2)); 
		h_vals.push_back(displacement);
	}	
	
	


}


//////////////////////////////////////////////////////

int state_exist(state s)
{
	for(int i=0; i<states.size(); i++)
	{
		bool flag = true;
		for(int j=0; j<9; j++)
		{
			if( states[i].tiles[j] != s.tiles[j])
			{
				flag = false;
				break;
			}
			
		}
		if(flag)
			return i;
		
	}
	return -1;
}

vector<int> swap_indices( int i, int j, vector<int> s)
{
	int num1 = s[i];
	s[i] = s[j];
	s[j] = num1;
	return s;
}

vector<state> find_nbrs(state st)
{
	vector<int> s = st.tiles;
	vector<state> v;
	if( s[0] == 9)
	{
		state s1( swap_indices( 0, 1, s));
		state s2( swap_indices( 0, 3, s));
		v.push_back(s1);
		v.push_back(s2);
	}
	
	if( s[1] == 9)
	{
		state s1( swap_indices( 1, 0, s));
		state s2( swap_indices( 1, 2, s));
		state s3( swap_indices( 1, 4, s));
		v.push_back(s1);
		v.push_back(s2);
		v.push_back(s3);
	}
	
	if( s[2] == 9)
	{
		state s1( swap_indices( 2, 1, s));
		state s2( swap_indices( 2, 5, s));
		v.push_back(s1);
		v.push_back(s2);
	}
	
	if( s[3] == 9)
	{
		state s1( swap_indices( 3, 0, s));
		state s2( swap_indices( 3, 4, s));
		state s3( swap_indices( 3, 6, s));
		v.push_back(s1);
		v.push_back(s2);
		v.push_back(s3);
	}
	
	if( s[4] == 9)
	{
		state s1( swap_indices( 4, 1, s));
		state s2( swap_indices( 4, 3, s));
		state s3( swap_indices( 4, 5, s));
		state s4( swap_indices( 4, 7, s));
		v.push_back(s1);
		v.push_back(s2);
		v.push_back(s3);
		v.push_back(s4);
	}
	
	if( s[5] == 9)
	{
		state s1( swap_indices( 5, 2, s));
		state s2( swap_indices( 5, 4, s));
		state s3( swap_indices( 5, 8, s));
		v.push_back(s1);
		v.push_back(s2);
		v.push_back(s3);
	}
	
	if( s[6] == 9)
	{
		state s1( swap_indices( 6, 3, s));
		state s2( swap_indices( 6, 7, s));
		v.push_back(s1);
		v.push_back(s2);
	}
	
	if( s[7] == 9)
	{
		state s1( swap_indices( 7, 4, s));
		state s2( swap_indices( 7, 6, s));
		state s3( swap_indices( 7, 8, s));
		v.push_back(s1);
		v.push_back(s2);
		v.push_back(s3);
	}
	
	if( s[8] == 9)
	{
		state s1( swap_indices( 8, 5, s));
		state s2( swap_indices( 8, 7, s));
		v.push_back(s1);
		v.push_back(s2);
	}
	return v;
}


void find_all_states()
{
	int curr = 0;
	//int check = 0;
	while ( curr < states.size() )
	{
		state s = states[curr];
		vector<state> neighbours = find_nbrs(s);
		//cout<<"check "<< check << endl;
		//check++;
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


void check_reachability( vector<int> vec)
{
	for(int i=0; i< vec.size(); i++)
	{
		if(vec[i] == 9) 
		{
			vec.erase(vec.begin() + i);
			break;
		}	
	}
	
	int num_inversions = 0;
	for(int i=0 ;i< vec.size() ; i++)
	{
		for(int j=0; j < i; j++)
		{
			if(vec[i] < vec[j])
				num_inversions ++;
		}
	}
	
	if(num_inversions%2 == 1)
	{
		cout<<" Goal state is not reachable from the chosen start state" <<endl;
		exit(0);
	}
}

int main()
{
	// push start state in states
	/*
	it was
	2 9 3
	1 8 5
	4 7 6
	in the cases considered for slides
	*/
	
	// take input for start state from user
	//enter tiles in row major order ( 9 for blank)
	
	vector<int> start_v;
	start_v.resize(9);
	for(int i=0; i<9; i++)
	{
		cin>> start_v[i];
		//cout<<"a"<<endl;
	}
	
	state s(start_v);
	states.push_back(s);
	
	
	/////////////////////////////////////////////////////////////////////////////////
	// check reachability, i.e find no of inverso=ions in start_v. If it is odd, unreachable
	check_reachability(start_v);
	
	/////////////////////////////////////////////////////////////////////////////////
	
	
	
	//cout<< states.size() << endl;
	find_all_states(); // push all the states in vector, also make edges
	//exit(0); (not exiting)
	
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
		cout<< "goal node not reachable\n";
		exit(1);
	}
	cout<< start_node << " " << goal_node << endl;
		
	//compute all h values and print
	compute_h_values_manhattan(goal_node);
	for(int i=0; i< h_vals.size(); i++)
	{
		cout<< h_vals[i] << endl;
	}
}
