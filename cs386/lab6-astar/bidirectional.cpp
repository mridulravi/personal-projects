/////////////////////////////////////////////////////////////
/*
notes:
1) ids for node and edge are their index in the resp. vectors 



*/
/////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include<queue>
#include<stdlib.h>


//////////////////////////////////////////////////////////////
using namespace std;


//class declarations
class Node 
{
	public:
	vector<int> neighb_edge_ids;
	float h_value;
	float g_value_forward;
	int parent_forward, child_forward;	//Child is not being used currenlty anywhere
	int status_forward; // 0 : not in OL nor in CL, 1: in OL, 2: in CL
	
	float g_value_backward;
	int parent_backward, child_backward;
	int status_backward; // 0 : not in OL nor in CL, 1: in OL, 2: in CL
	
	Node();
	void add_edge(int e);
};

class Edge 
{
	public:
	int node1;
	int node2;
	float weight;
	
	int find_other_end(int n);
	pair<int, int> find_end_points();
	void init_edge ( int n1, int n2, float w);

};

///////////////////////////////////////////////////////
//global variables
vector<Node> nodes;
vector<Edge> edges;
int start_node, goal_node, common_node;
int num_parent_pointer_redirections, num_iterations_for_algo;
vector<int> closed_list_forward;
vector<int> closed_list_backward;
bool is_reachable;
////////////////////////////////////////////////////////

class open_list_member_forward
{
	public:
	int node_num; // gives id of the node
	
	// overload < operator for mi heap
	bool operator<(const open_list_member_forward & rhs) const
	{
		return ( nodes[node_num].g_value_forward + nodes[node_num].h_value ) > ( nodes[rhs.node_num].g_value_forward + nodes[rhs.node_num].h_value ) ;
	}
};


class open_list_member_backward
{
	public:
	int node_num; // gives id of the node
	
	// overload < operator for mi heap
	bool operator<(const open_list_member_backward & rhs) const
	{
		return ( nodes[node_num].g_value_backward + nodes[node_num].h_value ) > ( nodes[rhs.node_num].g_value_backward + nodes[rhs.node_num].h_value ) ;
	}
};

/////////////////////////////////////////////////////
priority_queue<open_list_member_forward> open_list_forward;
priority_queue<open_list_member_backward> open_list_backward;
////////////////////////////////////////////////////

// class method definitions

int Edge::find_other_end(int n)
{
	if( (n != node1) && (n != node2))
	{
		// error, this node not part of this edge
		return -1;
	} 
	
	if ( n == node1) return node2;
	else return node1;	
}

pair<int, int> Edge::find_end_points()
{
	pair<int, int> edge_nodes;
	edge_nodes.first = node1;
	edge_nodes.second = node2;
	return edge_nodes;
}

void Edge::init_edge( int n1, int n2, float w)
{
	node1 = n1;
	node2 = n2;
	weight = w;
}

Node::Node()
{
	parent_forward = -1;
	child_forward = -1;
	status_forward = 0;
	g_value_forward = 0;
	parent_backward = -1;
	child_backward = -1;
	status_backward = 0;
	g_value_backward = 0;
}

void Node::add_edge(int e)
{
	for(int i=0; i< neighb_edge_ids.size(); i++)
	{
		if(neighb_edge_ids[i] == e) return; // edge already in list
	}
	neighb_edge_ids.push_back(e);
	return;
}
/////////////////////////////////////////////

// input format
	/*
	#nodes(n) 
	#edges(m)
	edge 0    ( it has node1 node2 cost)
	edge 1   
	edge 2
	.
	.
	edge m-1	
	
	start_node_id
	goal_node_id
	
	h(node0)
	h(node1)
	.
	.
	h(node n-1)
	
	*/

///////////////////////////////////////////

float find_cost_of_edge_given_ends(int n1, int n2)
{
	for(int i=0; i<edges.size(); i++)
	{
		if((edges[i].node1 == n1 && edges[i].node2 == n2) || (edges[i].node1 == n2 && edges[i].node2 == n1)){
			return edges[i].weight;
		}
	}
	
	return -1; // no such edge found
}
//////////////////////////////////////////

void parent_redirection_forward(int index)
{
	//Iterate through all nodes with its parent set to index and set the appropriate value
	Node n=nodes[index];
	int i=0,other_end;
	float w;
	for(i=0;i<n.neighb_edge_ids.size();i++)
	{
		other_end=edges[n.neighb_edge_ids[i]].find_other_end(index);
		w=edges[n.neighb_edge_ids[i]].weight;
		
		if(nodes[other_end].status_forward==1)	//If the child is in OL, then dont do anything for that node
		{
			if((nodes[other_end].g_value_forward)>(n.g_value_forward+w))
			{	
				nodes[other_end].g_value_forward=n.g_value_forward+w;
				nodes[other_end].parent_forward=index;
			}
		}
		else if(nodes[other_end].status_forward==2)	//If the child is in CL then do recursively on its children
		{
			if((nodes[other_end].g_value_forward)>(n.g_value_forward+w))
			{
				nodes[other_end].g_value_forward=n.g_value_forward+w;
				num_parent_pointer_redirections++;
				nodes[other_end].parent_forward=index;
				//Setting the values of all the children, grand children and so on.
				parent_redirection_forward(other_end);
			}
		}
	}
	
}


void parent_redirection_backward(int index)
{
	//Iterate through all nodes with its parent set to index and set the appropriate value
	Node n=nodes[index];
	int i=0,other_end;
	float w;
	for(i=0;i<n.neighb_edge_ids.size();i++)
	{
		other_end=edges[n.neighb_edge_ids[i]].find_other_end(index);
		w=edges[n.neighb_edge_ids[i]].weight;
		
		if(nodes[other_end].status_backward==1)	//If the child is in OL, then dont do anything for that node
		{
			if((nodes[other_end].g_value_backward)>(n.g_value_backward+w))
			{	
				nodes[other_end].g_value_backward=n.g_value_backward+w;
				nodes[other_end].parent_backward=index;
			}
		}
		else if(nodes[other_end].status_backward==2)	//If the child is in CL then do recursively on its children
		{
			if((nodes[other_end].g_value_backward)>(n.g_value_backward+w))
			{
				nodes[other_end].g_value_backward=n.g_value_backward+w;
				num_parent_pointer_redirections++;
				nodes[other_end].parent_backward=index;
				//Setting the values of all the children, grand children and so on.
				parent_redirection_backward(other_end);
			}
		}
	}
	
}

int forward()
{
	//Pop the top of the priority queue
	open_list_member_forward tmp=open_list_forward.top();
	open_list_forward.pop();
	
	//Push all its neighbours into the open list with its g-value and parent appropriately set
	int ngbr_size=nodes[tmp.node_num].neighb_edge_ids.size();
	int i=0,id;
	float w;
	for(i=0;i<ngbr_size;i++)
	{
		//Find the id of the node on the other end of the edge and the weight of the corresponding edge
		id=edges[nodes[tmp.node_num].neighb_edge_ids[i]].find_other_end(tmp.node_num);
		w=edges[nodes[tmp.node_num].neighb_edge_ids[i]].weight;
		
		if(nodes[id].status_forward==1)	//in OL
		{
			if((nodes[id].g_value_forward)>(nodes[tmp.node_num].g_value_forward+w))
			{	
				nodes[id].g_value_forward=nodes[tmp.node_num].g_value_forward+w;
				nodes[id].parent_forward=tmp.node_num;
			}
		}
		else if(nodes[id].status_forward==2)	//in CL (parent redirection)
		{
			if((nodes[id].g_value_forward)>(nodes[tmp.node_num].g_value_forward+w))
			{
				nodes[id].g_value_forward=nodes[tmp.node_num].g_value_forward+w;
				num_parent_pointer_redirections++;
				nodes[id].parent_forward=tmp.node_num;
			
				//Setting the values of all the children, grand children and so on.
				parent_redirection_forward(id);
			}
		}
		else			// neither in OL nor in CL
		{
			nodes[id].g_value_forward=nodes[tmp.node_num].g_value_forward+w;
			nodes[id].parent_forward=tmp.node_num;
			nodes[id].status_forward=1;
			open_list_member_forward tmp2;
			tmp2.node_num=id;
			open_list_forward.push(tmp2);			
		}
	}
	
	//and push the node expanded in the closed list
	nodes[tmp.node_num].status_forward=2;
	closed_list_forward.push_back(tmp.node_num);
	
	//Test if the top node is the destination, if yes, then terminate the algo else continue.
	if(open_list_forward.empty())
	{
		return 0;
	}
	else
	{
		tmp=open_list_forward.top();
	
		if(tmp.node_num==goal_node)
		{
			is_reachable=true;
		}
		//a_star();
		return 1;
	}
	
}

int backward()
{
	//Pop the top of the priority queue
	open_list_member_backward tmp=open_list_backward.top();
	open_list_backward.pop();
	
	//Push all its neighbours into the open list with its g-value and parent appropriately set
	int ngbr_size=nodes[tmp.node_num].neighb_edge_ids.size();
	int i=0,id;
	float w;
	for(i=0;i<ngbr_size;i++)
	{
		//Find the id of the node on the other end of the edge and the weight of the corresponding edge
		id=edges[nodes[tmp.node_num].neighb_edge_ids[i]].find_other_end(tmp.node_num);
		w=edges[nodes[tmp.node_num].neighb_edge_ids[i]].weight;
		
		if(nodes[id].status_backward==1)	//in OL
		{
			if((nodes[id].g_value_backward)>(nodes[tmp.node_num].g_value_backward+w))
			{	
				nodes[id].g_value_backward=nodes[tmp.node_num].g_value_backward+w;
				nodes[id].parent_backward=tmp.node_num;
			}
		}
		else if(nodes[id].status_backward==2)	//in CL (parent redirection)
		{
			if((nodes[id].g_value_backward)>(nodes[tmp.node_num].g_value_backward+w))
			{
				nodes[id].g_value_backward=nodes[tmp.node_num].g_value_backward+w;
				num_parent_pointer_redirections++;
				nodes[id].parent_backward=tmp.node_num;
			
				//Setting the values of all the children, grand children and so on.
				parent_redirection_backward(id);
			}
		}
		else			// neither in OL nor in CL
		{
			nodes[id].g_value_backward=nodes[tmp.node_num].g_value_backward+w;
			nodes[id].parent_backward=tmp.node_num;
			nodes[id].status_backward=1;
			open_list_member_backward tmp2;
			tmp2.node_num=id;
			open_list_backward.push(tmp2);			
		}
	}
	
	//and push the node expanded in the closed list
	nodes[tmp.node_num].status_backward=2;
	closed_list_backward.push_back(tmp.node_num);
	
	//Test if the top node is the destination, if yes, then terminate the algo else continue.
	if(open_list_backward.empty())
	{
		return 0;
	}
	else
	{
		tmp=open_list_backward.top();
	
		if(tmp.node_num==goal_node)
		{
			is_reachable=true;
		}
		//a_star();
		return 1;
	}
}

bool converge()
{
	int i,j;
	for(i=0;i<closed_list_forward.size();i++)
	for(j=0;j<closed_list_backward.size();j++)
	{
		if(closed_list_forward[i]==closed_list_backward[j])
		{
			common_node=closed_list_forward[i];
			return true;
		}
	}
	return false;
}

// A Star Algo
//Assuming open_list_member with node_num data member
//Assuming that open_list has start node already pushed into first position in the open list and its g value is set to 0.
void a_star()
{
	//Increase the iteration number
	num_iterations_for_algo++;
	
	
	//////////////////////////////////Forward Direction////////////////////
	
	int f=forward();
	
	cout<<"Value of f:"<<f<<endl;
	/////////////////////////////Reverse Direciton/////////////////////////
	
	int r=backward();
	cout<<"Value of r:"<<r<<endl;
	
	
	bool dec=converge();
	
	if(dec)
	{
		is_reachable=true;
		return;		//The intersection is non-empty
	}
	else
	{
		if((f==0)||(r==0))
		{
			cout<<"\n Forward and Backward A star did not meet.\n";
			return;
		}
		else
		{
			a_star();
		}
	}
	
	
	
}

//////////////////////////////////////////

int main(){
	num_parent_pointer_redirections = 0;
	num_iterations_for_algo = 0;
	common_node=-1;
	is_reachable = false;
	
	// take inputs from user/ interface program
	int num_nodes, num_edges;
	cin >> num_nodes >> num_edges;
	nodes.resize(num_nodes);
	edges.resize(num_edges);
	
	int n1, n2;
	float cost;
	
	for(int i=0; i< num_edges; i++)
	{
		cin>>n1>>n2>>cost;
		
		// set the edge and node objects in the global vectors
		edges[i].init_edge(n1, n2, cost);
		nodes[n1].add_edge(i);
		nodes[n2].add_edge(i); 
	}
	
	// input start and goal node ids
	
	cin>>start_node >> goal_node;
	
	// input h values for all nodes
	int h;
	for(int i=0; i< num_nodes; i++)
	{
		cin>> h;
		nodes[i].h_value = h;
	}
	
	
	///////////////////////////////////////////////////////////////////////
	// all inputs taken
	
	// push start node in open list
	open_list_member_forward start;
	start.node_num = start_node;
	open_list_forward.push(start);
	
	//pushing the end node in the open list
	open_list_member_backward end;
	end.node_num = goal_node;
	open_list_backward.push(end);
	
	///////////////////////////////////////////////////////////////////////
	
	// call a_star fun
	
	a_star();
	
	//////////////////////////////////////////////////////////////////////
	
	// print out optimal cost and the optimal path (from start to goal)
	
	if(!is_reachable)
	{
		// there is no path from start to goal node
		cout<< "no path from start to goal node\n\n";
		exit(1);
	}
	
	else 	// a path has been found
	{
		vector<int> path; // will store the path in forward direction
		vector<int> path2;// will store the path in forward direction
		int n = common_node , x;
		float opt_path_cost = 0.0, tmp_cost;
		path.push_back(n);
		while( n != start_node)
		{
			x = nodes[n].parent_forward;
			tmp_cost = find_cost_of_edge_given_ends( n, x);
			if( tmp_cost == -1) 
			{
				// error, no path b/w node and its (supposed) parent
				cout << "no path b/w node and its (supposed) parent\n\n";
				exit(1);
			}
			
			else
			{
				opt_path_cost += tmp_cost;
				n = x;
				path.push_back(n);
			}
		}
		
		n=common_node;	
		//Printing backward
		while( n != goal_node)
		{
			x = nodes[n].parent_backward;
			tmp_cost = find_cost_of_edge_given_ends( n, x);
			if( tmp_cost == -1) 
			{
				// error, no path b/w node and its (supposed) parent
				cout << "no path b/w node and its (supposed) parent\n\n";
				exit(1);
			}
			
			else
			{
				opt_path_cost += tmp_cost;
				n = x;
				path2.push_back(n);
			}
		}
		
		/////////////////////////////////////////////////
		// print path ( stored in reverse order in vector
		cout<< "the optimal path is:\n";
		for(int i=path.size()-1; i >=0;i--)
		{
			cout<< path[i] << " ";
		}
		
		for(int i=0; i <=path.size()-1;i++)
		{
			cout<< path2[i] << " ";
		}
		cout<<endl;
		
		// print opt_path cost
		cout<< "optimal path cost is " << opt_path_cost << endl;
	}
}
