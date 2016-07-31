#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  ofstream fileout;
  string text = "Writing first line to a file.\n";
  text.append("Writing second line to file.\n");

  fileout.open ("example.txt");
  fileout << text;
  fileout.close();

  ifstream filein;
  string line;
  text.clear();
  filein.open("example.txt");
  if(filein.is_open())
  {
	  while(filein.good())
	  {
		  getline(filein,line);
		  text.append(line);
		  text.append("\n");
	  }
	filein.close();
	cout << "Read from File::" << endl;
	cout << text;
  }

  else
	  cout << "Unable to open file!";

  return 0;
}
//more help : http://www.cplusplus.com/doc/tutorial/files/
