#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

typedef std::unordered_multimap<std::string,std::string> stringmap;
stringmap myumm;
queue<char> myqueue;
void recursive(string myString);

int main ( int argc, char *argv[] )
{
  int i,j;
  string variable,terminal,sentence,mystring,C[1000],z;
  char response,w;
  
  srand ( time(NULL) );						// seeding srand function with time
  ofstream fileout;
  fileout.open("traceoutput",ios::trunc);			// a file "traceoutput" is created to handle variable-production mappings
  
  if ( argc != 2 ) 						// argc should be 2 for correct execution
    cout<<"usage: "<< argv[0] <<" <filename>\n";		// We print argv[0] assuming it is the program name
    
  else 
   { 
    ifstream the_file ( argv[1] );				// We assume argv[1] is a filename to open
    								// Always check to see if file opening succeeded
    if ( !the_file.is_open() )
       cout<<"Could not open file\n";
    else {
       char x;
       while ( the_file.get ( x ) )				// the_file.get ( x ) returns false if the end of the file
       {							//  is reached or an error occurs
	if (x!='{')
	{}
	else if (x == '{')					// Outside of the braces, there can be any kind of text;   
	{							// for comments, diagrams, etc. We have to ignore it
	 do
	 {
	  while (x!='<')					// scanning for the variable
		{the_file.get(x);
		}
	  i=0;variable.clear();
	  do
	  {variable.push_back(x);				// variable found	   
           the_file.get(x);
	  }while(x!='>');
	  variable.push_back(x);
	  while(x!='}')
	  {	the_file.get(x);
		while(x==' '||x=='\n'||x=='\t')
		{the_file.get(x);
		}
		j=0;
		loop: do
		{terminal.push_back(x);		 
		 the_file.get(x);
		}while(x!=';');
		
                myumm.insert ( {{variable,terminal}} );   	 // initializer list insertion

		terminal.clear();
		the_file.get(x);
		while(x==' '||x=='\n'||x=='\t')			 // skip over any extra whitespace
		{the_file.get(x);
		}if(x!='}'){goto loop;}
	  }		  
	 }while (x!='}');
	}
       }
   }								 // the_file is closed implicitly here
    

  for ( auto& x: myumm )					 // x is the iterator which goes through the multi_map 
  std::string a;
  std::streambuf *coutbuf = std::cout.rdbuf(); 					// save old buf
  std::cout.rdbuf(fileout.rdbuf()); 						// redirect std::cout to traceoutput

  auto range = myumm.equal_range("<start>");
  for_each (
    range.first,
    range.second,
    [](stringmap::value_type& x){std::cout <<x.second;});
  std::cout.rdbuf(coutbuf);							// reset to standard output again
  fileout.close();
  ifstream myfile ("traceoutput");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,z);     
    }
    myfile.close();
  }
  for (i=0;i<z.length();)
  {if(z[i]!='<')
	{myqueue.push(z[i]);							// production rules without <> are pushed into the queue 
	 i++;
	}
    else
	{mystring.clear();
	 while(z[i]!='>')
	 {mystring.push_back(z[i]);
	 i++;
	 }
	 mystring.push_back(z[i]);
	 recursive(mystring);
	 i++;
	}
   }
  }
   
   while(!myqueue.empty())							// printing of random sentance occur here
	{									// buffer used to store it is a queue
	 cout<<myqueue.front();	 
	 myqueue.pop();
	 if ((myqueue.front()==' '&&w==' ')||(myqueue.front()=='\t'&&w=='\t'))	// neglecting extra white space
         {w=myqueue.front();myqueue.pop();}
	 
	}
   cout<<endl;
}



void recursive(string myString)						// this the recursive function to produce the random sentence 
{									// takes as argument variables in <start>
  int h=0,g=0,f=0; string C[1000],mystring2;				// the different production rules are stored in an array C
  ofstream fileout;							// of strings
  fileout.open("traceoutput",ios::trunc);
  
  std::streambuf *coutbuf = std::cout.rdbuf(); 				//save old buf
  std::cout.rdbuf(fileout.rdbuf()); 					//redirect std::cout to traceoutput!
  auto range = myumm.equal_range(myString);				//Get range of elements with specific key-here myString
  for_each (
    range.first,
    range.second,
    [](stringmap::value_type& x){std::cout <<x.second<<"_";});
  std::cout.rdbuf(coutbuf); 						//reset to standard output again
  fileout.close();									
  ifstream myfile ("traceoutput");
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,C[h],'_');      
      h++;
    }
    myfile.close();
  }

  g = (rand()%h)-1;							// generation of random value
  if(g<0) 
	g=0;

  for (f=0;f<C[g].length();)
  {
	if (C[g][f]!='<')
	{myqueue.push(C[g][f]);
	 f++;}
        else
	{mystring2.clear();
	 while (C[g][f]!='>')
	 {mystring2.push_back(C[g][f]);
	  f++;
	 }
	 mystring2.push_back(C[g][f]);
	 
	 recursive(mystring2);
	 f++;
	}	
  }
}

