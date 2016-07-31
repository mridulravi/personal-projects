#include "trie.h"
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

int main()
{
	/* A stack is used to keep track of search operation i.e. everytime we cross 
	a node while searching, a pointer to that node is pushed into the stack */
	stack<TreeNode* > mystack;
	trie T;							// TRIE object
	char x,s;
	string str,filename;
	string dispStr;
	TreeNode *CurrPtr, *NextPtr, *CurrSearchPtr, *NextSearchPtr, *PrevSearchPtr;
	CurrPtr = &T.root();					// CurrPtr initially points to the root
	ifstream myfile;
	getline(cin, filename);					// to get the file name
	myfile.open(filename.c_str() );
	while ( myfile.get ( x ) )
	{
		int intX = x;			
		if ((intX <= 90 && intX >= 65)||(intX <= 122 && intX >= 97))	
		//only charaters in the range a-z,A-Z are inserted into the TRIE
		{
			NextPtr=T.insert(CurrPtr,x);
			if(NextPtr->flag != true)		// if a word "wash"  was entered earlier and then "washed"	
				NextPtr->flag = false;		// was entered 'h' flag should remain 1
			CurrPtr=NextPtr;
		}
		// when any special character is encountered, it is considered the end of a word
		else 
		{	
			CurrPtr->flag = true;			// thus flag is set to true
			CurrPtr=&T.root();			// and our CurrPtr again goes to the root
		}

	}
	myfile.close();						

		/*****************************************
			INSERION DONE !

				SEARCH STARTS NOW
		******************************************/

	CurrSearchPtr = &T.root();				// CurrSearchPtr initially points to root
	cout<<"Enter the word to search for (0 to terminate): ";
	cin>>s;
	
	cout<<endl;
	while (s != '0')					// Take input untill 0 is pressed
	{	
	   if(s != '<')						// backspace is done through <
		{NextSearchPtr = T.searchFor(CurrSearchPtr,s);
		PrevSearchPtr=CurrSearchPtr;
		mystack.push(PrevSearchPtr);			// as we cross a node, push pointer to it into a stack
		CurrSearchPtr = NextSearchPtr;
		if (NextSearchPtr == NULL)			// if s not found after str
		{
			dispStr.append(1,s);
			cout << "Sorry '" << dispStr<< "' not found!" <<endl;
			cout << "Did you mean : "<<endl;	// give suggestions by popping out of a stack
			str.erase(dispStr.size()-2,2);		// suggestions would be all words
			dispStr.erase(dispStr.size()-2,2);	// having prefix str
			T.preorder(str,mystack.top());
			cout << endl;
			return 0;				// and terminate
		}
		else 						// if s found after str
		{
			T.preorder(str,CurrSearchPtr);		// print all words starting with str appended eith s
			if (islower(CurrSearchPtr->element))    // taking care of case sensitivity
			{
				str.append(1,tolower(s));
				dispStr.append(1,s);
			}
			else 
			{
				str.append(1,toupper(s));
				dispStr.append(1,s);
			}
		}
		cout<<endl;
		cout<<"Enter the word to search for (0 to terminate): ";
		cout << dispStr;
		cin>>s;
		cout<<endl;
		}
	   else							// if backspace(<) is pressed
		{
			str.erase(dispStr.size()-1,1);
			dispStr.erase(dispStr.size()-1,1);
			cout << endl;
			T.preorder(str,CurrSearchPtr);			
			cout<<"Enter the word to search for (0 to terminate): ";
			cout <<dispStr;
			cin>>s;
			CurrSearchPtr = mystack.top();		// pop from stack and repeat
			mystack.pop();
			cout<<endl;
		}
	}	
	return 0;
}
