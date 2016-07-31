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
	float g_value, h_value;
	int parent, child;
	int status; // 0 : not in OL nor in CL, 1: in OL, 2: in CL
	
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
int start_node, goal_node;
int num_parent_pointer_redirections, num_iterations_for_algo;
vector<int> closed_list;
bool is_reachable;
////////////////////////////////////////////////////////

class open_list_member
{
	public:
	int node_num; // gives id of the node
	
	// overload < operator for mi heap
	bool operator<(const open_list_member & rhs) const
	{
		return ( nodes[node_num].g_value + nodes[node_num].h_value ) > ( nodes[rhs.node_num].g_value + nodes[rhs.node_num].h_value ) ;
	}
};

/////////////////////////////////////////////////////
priority_queue<open_list_member> open_list;
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
	parent = -1;
	child = -1;
	status = 0;
	g_value = 0;
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

void parent_redirection(int index)
{
	//Iterate through all nodes with its parent set to index and set the appropriate value
	Node n=nodes[index];
	int i=0,other_end;
	float w;
	for(i=0;i<n.neighb_edge_ids.size();i++)
	{
		other_end=edges[n.neighb_edge_ids[i]].find_other_end(index);
		w=edges[n.neighb_edge_ids[i]].weight;
		
		if(nodes[other_end].status==1)	//If the child is in OL, then dont do anything for that node
		{
			if((nodes[other_end].g_value)>(n.g_value+w))
			{	
				nodes[other_end].g_value=n.g_value+w;
				nodes[other_end].parent=index;
			}
		}
		else if(nodes[other_end].status==2)	//If the child is in CL then do recursively on its children
		{
			if((nodes[other_end].g_value)>(n.g_value+w))
			{
				nodes[other_end].g_value=n.g_value+w;
				num_parent_pointer_redirections++;
				nodes[other_end].parent=index;
				//Setting the values of all the children, grand children and so on.
				parent_redirection(other_end);
			}
		}
	}
	
}


// A Star Algo
//Assuming open_list_member with node_num data member
//Assuming that open_list has start node already pushed into first position in the open list and its g value is set to 0.
void a_star()
{
	//Increase the iteration number
	num_iterations_for_algo++;
	
	//Pop the top of the priority queue
	open_list_member tmp=open_list.top();
	open_list.pop();
	
	//Push all its neighbours into the open list with its g-value and parent appropriately set
	int ngbr_size=nodes[tmp.node_num].neighb_edge_ids.size();
	int i=0,id;
	float w;
	for(i=0;i<ngbr_size;i++)
	{
		//Find the id of the node on the other end of the edge and the weight of the corresponding edge
		id=edges[nodes[tmp.node_num].neighb_edge_ids[i]].find_other_end(tmp.node_num);
		w=edges[nodes[tmp.node_num].neighb_edge_ids[i]].weight;
		
		if(nodes[id].status==1)	//in OL
		{
			if((nodes[id].g_value)>(nodes[tmp.node_num].g_value+w))
			{	
				nodes[id].g_value=nodes[tmp.node_num].g_value+w;
				nodes[id].parent=tmp.node_num;
			}
		}
		else if(nodes[id].status==2)	//in CL (parent redirection)
		{
			if((nodes[id].g_value)>(nodes[tmp.node_num].g_value+w))
			{
				nodes[id].g_value=nodes[tmp.node_num].g_value+w;
				num_parent_pointer_redirections++;
				nodes[id].parent=tmp.node_num;
			
				//Setting the values of all the children, grand children and so on.
				parent_redirection(id);
			}
		}
		else			// neither in OL nor in CL
		{
			nodes[id].g_value=nodes[tmp.node_num].g_value+w;
			nodes[id].parent=tmp.node_num;
			nodes[id].status=1;
			open_list_member tmp2;
			tmp2.node_num=id;
			open_list.push(tmp2);			
		}
	}
	
	//and push the node expanded in the closed list
	nodes[tmp.node_num].status=2;
	closed_list.push_back(tmp.node_num);
	
	//Test if the top node is the destination, if yes, then terminate the algo else continue.
	if(open_list.empty())
	{
		return;
	}
	else
	{
		tmp=open_list.top();
	
		if(tmp.node_num==goal_node)
		{
			is_reachable=true;
		}
		a_star();
	}
}

//////////////////////////////////////////

int main(){
	num_parent_pointer_redirections = 0;
	num_iterations_for_algo = 0;
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
	open_list_member start;
	start.node_num = start_node;
	open_list.push(start);
	
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
		vector<int> path; // will store the path
		int n = goal_node , x;
		float opt_path_cost = 0.0, tmp_cost;
		path.push_back(n);
		while( n != start_node)
		{
			x = nodes[n].parent;
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
		
		/////////////////////////////////////////////////
		// print path ( stored in reverse order in vector
		cout<< "the optimal path is:\n";
		for(int i=path.size()-1; i >=0;i--)
		{
			cout<< path[i] << " ";
		}
		cout<<endl;
		
		// print opt_path cost
		cout<< "optimal path cost is " << opt_path_cost << endl;
	}
}
