#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main()
{  ifstream the_file("Extension-request.g");
       if ( !the_file.is_open() )
      cout<<"Could not open file\n";
else   {
   string s1; char x;
   //cout << "Enter a sentence (use <space> as the delimiter): ";
   while ( the_file.get ( x ) )
       {//cout<< x;
	if (x!='{')
	{}
	else
	{//the_file.get(x);
	 while(x!='}')
	 {the_file.get(x);	
  	  getline(the_file,s1, '\n');
   	  cout << s1 << endl;
	  the_file.get(x);	  
	 }
	}
       }
       }
}
