
#include <string>
#include <iostream>
#include <fstream>
using namespace std ;

using namespace std ;

int main()
{
   string s1,s2;
   char x;
   cout << "Enter a sentence (use <space> as the delimiter): ";
   getline(cin,s1, '5');
   cin.get(x);
   getline(cin,s2, '6');
   cout << "You entered: " << s1 << endl;
   cout << "You entered: " << s2 << endl;
}
