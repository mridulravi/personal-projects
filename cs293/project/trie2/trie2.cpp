#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>

using namespace std;

struct Node{
	char character;						// stores the character
	unordered_map <char,Node *> map;			// unordered map to store the list of its child
	int flag;						// flag to check whether a word ends here or not
};

void insert(string str,Node * ptr);
void find_string(string str,Node * ptr);
void print(Node * ptr,string str);
void suggestion(Node * ptr,string str,int i);

int main(){
	string filename;
	Node *root;
	root =new Node;
	root->character=NULL;
	cout<<"enter the filename\n";
	cin>>filename;
	ifstream fin(filename.c_str() );					// opening the input fil
	string str;
	char a='y';
	while(!fin.eof() ){									// read the word from the file and insert it into the trie
		fin>>str;
		insert(str,root);
	}
	while(a=='y'){
		cout<<"enter the string to find\n";
		cin>>str;
		for(int k=0;k<str.size();k++){
			char c=str[k];
			if(int(c)>=65 and int(c)<=90){				// for removing case sensitivity.making all the characters small
				c=c+32;
				str[k]=c;
			}
		}
		find_string(str,root);							// calling the find function to find the string
		cout<<"want to find more strings(y/n)\n";
		cin>>a;
	}
	return 0;
}

void insert(string str,Node * ptr){
	int i=0;
	unordered_map<char,Node *>::iterator itr;
	while(i<str.size() ){
		char c=str[i];
		if(int(c)>=65 and int(c)<=90){				// making all the characters small (for removing case sensitivity)
			c=c+32;
			str[i]=c;
		}
		if(i==str.size()-1){						// this one is for removing the characters following the word like ,;: etc.
			if((c>='A' and c<='Z') or (c>='a' and c<='z') ){		 
			}
			else{
				ptr->flag=1;
				break;
			}
		}		
		itr=ptr->map.find(str[i]);					// find the character int the unordered map of this vertex
		if(itr==ptr->map.end() ){					// if not found then insert
			Node * ptr1;
			ptr1=new Node;
			ptr1->character=str[i];
			ptr->map.insert(make_pair<char,Node *>(str[i],ptr1) );
			ptr=ptr1;
		}
		else{
			ptr=itr->second;						// if found then make ptr point to it
		}
		if(i==str.size()-1){
			ptr->flag=1;		
		}
		i++;
	}
}
		
void find_string(string str,Node *ptr){
	int i=0;
	unordered_map<char,Node *>::iterator itr;
	while(i<str.size() ){
		itr=ptr->map.find(str[i]);					// find the character in the unorderded map
		if(itr==ptr->map.end() ){					// if not found then string not found ,then suggest the words
			cout<<"string not found\n";
			cout<<"Did you mean\n";
			string str1;
			for(int j=0;j<i;j++){
				str1+=str[j];
			}
			suggestion(ptr,str,i);					// calling suggestion function			
			print(ptr,str1);						// calling print function to print all strings starting with the substring till which the match is found 
			return;
		}
		else{
			ptr=itr->second;						// if found then make ptr point to it
		}
        if(i==str.size()-1){
        	if(ptr->flag==1){							// if found then print all the words having this as its substring 
        		print(ptr,str);
        		return;														
        	}
        	else{
        		print(ptr,str);
        	}
        }		
		i++;
	}
}

void print(Node * ptr,string str){				// for printing all the strings starting with the given string
	unordered_map<char,Node *>::iterator itr=ptr->map.begin();
		if(ptr->flag==1){
			cout<<str<<endl;					// if this is a word(flag =1 at the character where a string ends) then print it
		}	
	while(itr!=ptr->map.end() ){				// do it till all the strings are not printed
		print(itr->second,str+itr->first);
		itr++;
	}
}

void suggestion(Node * ptr,string str,int i){
	// the first case would be if user has missed this particular letter so we would search if that letter(entered by user ) is present at next levek or not
	// if present than we would continue else not 
	// second case user has entered one wrong character,rest all characters are fine

	// now implementing for first case -- that is one letter is missed
	 unordered_map<char,Node *>::iterator itr=ptr->map.begin();
	 while(itr!=ptr->map.end() ){
	 	Node *ptr1;
	 	ptr1=itr->second;
	 	unordered_map<char,Node *>::iterator itr1=ptr1->map.find(str[i]); 		 // finding the character (at the ith position)
	 	if(itr1!=ptr1->map.end() ){												 // if found 
	 		 string str1;
			 for(int j=0;j<i;j++){
	 			str1+=str[j];													// copying the string til the ith character in another string 
			 }
	 		str1+=ptr1->character;												// adding this character in the string 
	 		cout<<str1<<endl;
	 		print(ptr1,str1);													// now calling print function with this string
	 	}
	 	itr++;
	 }	
	 
	 //	for second case--one letter is wrongly typed
	 itr=ptr->map.begin();
	 while(itr!=ptr->map.end() ){
	 	Node *ptr1;
	 	ptr1=itr->second;
	 	unordered_map<char,Node *>::iterator itr1=ptr1->map.find(str[i+1]);		// finding the i+1 th character in the map of the node 
	 	if(itr1!=ptr1->map.end() ){												// if found 
	 		 string str1;
			 for(int j=0;j<i;j++){
	 			str1+=str[j];													// copying the string til the ith character in another string
			 }
	 		str1+=ptr1->character;												// adding this character in the string
	 		cout<<str1<<endl;
	 		print(ptr1,str1);													// now calling print function with this string
	 	}
	 	itr++;
	 }
} 
