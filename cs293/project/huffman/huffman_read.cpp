#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<string>
#include<stdlib.h>
#include<vector>
using namespace std;

struct bit{
	unsigned a:1;								// a will be of 1 bit now
};

class Node{
	public:
	char character;
	int frequency;
	Node *leftchild;
	Node *rightchild;
	Node(){										// default constructor
		frequency=0;
		leftchild=NULL;
		rightchild=NULL;
	}
	Node(char a,int m ){						// overloaded constructor
		character=a;
		frequency=m;
		leftchild=NULL;
		rightchild=NULL;
	}
	void initialize(char a,int m){				// initialize function to set the data members of the node
		character=a;
		frequency=m;
		leftchild=NULL;
		rightchild=NULL;	
	}
};

void read(Node * root){							// reads fom the compressed file
	Node *ptr=root;
	ifstream fin("compressed.bin",ios::binary);
	ofstream fout("original.txt");
	char *buffer;
	fin.seekg(0,ios::end);
	int length=fin.tellg();						// calculating the length
	fin.seekg(0,ios::beg);
	buffer=new char[length];					// making buffer point to an array of characters of size "length"
	bit obj1[8];								// creating 8 objects of structure bit
	while(length!=0){
		fin.read(buffer,1);						// read 1 byte from the compressed file
		for(int i=0;i<8;i++)
		{
			obj1[i].a=0;
			obj1[i].a=*buffer>>(7-i) & 1;		// using bitwise shifts to store the correct bit in the correct object no
			if(obj1[i].a==0){					// if the bit is 0 then go left in the tree
				ptr=ptr->leftchild;
				if(ptr->leftchild==NULL && ptr->rightchild==NULL){				// if leaf then print the character in the file
					fout<<ptr->character;	
					ptr=root;
				}
			}
			else{								// if the bit is 1 then go right in the tree
				ptr=ptr->rightchild;
				if(ptr->leftchild==NULL && ptr->rightchild==NULL){				// if leaf then print the character in the file
					fout<<ptr->character;		
					ptr=root;
				}			
			}
		}
		length--;								// decrementing length
	}
}

void coding(Node * root,string str,vector<string> & str1){		// for generating codes using the huffman tree
	if(root->leftchild!=NULL){				
		coding(root->leftchild,str+'0',str1);					// if going left then add 0 to the string
	}
	if(root->rightchild!=NULL){
		coding(root->rightchild,str+'1',str1);					// if going right then add 1 to the string
	}
	if(root->leftchild==NULL and root->rightchild==NULL){
		str1[int(root->character)]=str;							// if leaf then store the code corresponding to it in the vector at respective position
	}
}

class Comparator{												// defining comparator class for overloading in the priority queue
	public:
	bool operator () (const Node & a,const Node & b){
		return ( (a.frequency>b.frequency)?true:false );
	}
};
 
void createFile(){
	typedef priority_queue < Node,vector<Node>,Comparator > heap;				
	vector<Node> vec;
	heap q;				
	ifstream fin("encodedvector.bin",ios::binary);				// open the encodedvector.bin file for restoring the vector
	int vec_size;	
	fin.read(reinterpret_cast<char *>(& vec_size),sizeof(vec_size) );
	vec.resize(vec_size);
	int i=0;
	for(int i=0;i<vec_size;i++){
		fin.read(reinterpret_cast<char *>(&vec.at(i) ),sizeof(vec) );		// recreating the vector from the file
	}
	while(!vec.empty() ){													// inserting all the elements in the priority queue
		q.push(vec.back() );
		vec.pop_back();
	}
	while(q.size()!=1){														// create the huffman tree 
		Node * left,* right;
		left=new Node;
		*left=q.top();
		q.pop();
		right=new Node;
		*right=q.top();
		q.pop();
		Node *c;
		c=new Node;		
		c->rightchild=right;
		c->leftchild=left;
		c->character='#';
		c->frequency=left->frequency+right->frequency;
		q.push(*c);
		delete c,left,right;
	}
	Node tree;
	if(q.size()==1){
		tree=q.top();
		q.pop();
	}
	vector<string> vec_str(256);
	Node * root= &tree;										// root points to the root element of the huffman tree
	string str1;
	coding(root,str1,vec_str);	
	read(root);
}		

int main(){
	createFile();
	return 0;
}
