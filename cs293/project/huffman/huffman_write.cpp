#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<string>
#include<stdlib.h>
using namespace std;

struct bit{
	unsigned a:1;										// a will be of 1 bit now
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

void write(string str){
	bit obj[8];
	int i=0,j=7;
	int size=str.size();
	if(size%8==0){}								// for completing the bits  i.e. suppose the in the last byte only 000 was there then making it 00000000
	else{
		size=size+(8-size%8);
	}
	while(str.size()!=size){
		str=str+'0';
	}
	ofstream fout("compressed.bin",ios::binary);// opening this file for writing the compressed text
	while(j<size ){
		for(i=7;i>=0;i--){
			obj[i].a=0;
			obj[i].a=(obj[i].a | str[j]& 1);	// taking each 0 and 1 and storing it in "a" of structure bit which takes 1 bit
			j--;
		}										// this loop runs 8 times so that we have 1 byte of information
 		char c=(char)0;
		for(i=0;i<8;i++)
		{
			c=c | obj[i].a;						// storing the character formed above in "c"
			if(i!=7){
				c=c<<1;
			}
		}
		fout.write((&c),1);						// writing c to the file
		j+=16;												
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
	vector<int> check(256);
	for(int i=0;i<256;i++){
		check[i]=-1;
	}
	int count=-1;
	string str;
	char a;
	cout<<"enter the file name\n";
	cin>>str;
	ifstream fin(str.c_str() );									// opening the file 		
	while(1){													// reading from the file
		fin.get(a);
		if(fin.eof() ){
			break;
		}
		if(check[int(a)]==-1){									// if new character then push it into the vector
			Node * n;
			n = new Node;
			(*n).initialize(a,1);
			vec.push_back(*n);
			count++;
			check[int(a)]=count;							
			delete n;
		}
		else{													// if old character then just increase the frequency by 1
			vec[check[int(a)] ].frequency++;
		}	
	}
	fin.close();												// close the file
	
	int vec_size=vec.size();
	ofstream fout("encodedvector.bin",ios::binary);				// writing the vector in a file , will be used while decoding
	fout.write(reinterpret_cast<char *>(&vec_size),sizeof(vec_size) );
	for(int i=0;i<vec.size();i++){
		fout.write(reinterpret_cast<char *>(&vec.at(i) ),sizeof(vec) );
	}
	fout.close();
	
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
	string final;
	fin.open(str.c_str() );
	while(1){
		fin.get(a);
		if(fin.eof() ){
			break;
		}
		final+=vec_str[int(a)];								// "final" string stores the whole text in the form of 0 and 1's
	}
	fin.close();
	write(final);											// writes the "final" string in a file such that each 0 and 1 takes 1 bit only 
}		

int main(){
	createFile();
	return 0;
}
