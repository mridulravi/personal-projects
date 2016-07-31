#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<map>
using namespace std;

int main()
{
	// read from the 3 files and make the input vector
	map<string, int> input;
	int index=0;
//	vector<string> input;
	string str;
	fstream fp;
	fp.open("my_positive");
	if(fp.is_open() )
	{
		while(getline(fp, str) )
		{
			//input.push_back(str);
			input[str] = index++;
		}
	}
	fp.close();
	
	fp.open("my_negative");
	if(fp.is_open() )
	{
		while(getline(fp, str) )
		{
			//input.push_back(str);
			if(input[str] == 0)
				input[str] = index;
			else
				cout<<str<<": already present\n";
		}
	}
	fp.close();

	fp.open("my_objective");
	if(fp.is_open() )
	{
		while(getline(fp, str) )
		{
			//input.push_back(str);
			if(input[str] == 0)
				input[str] = index++;
			else
				cout<<str<<": already present\n";
		}
	}
	fp.close();
	
	cout<<"Size of input vector is "<<input.size()<<endl;
	cout<<index<<endl;
	
	return 0;
}	
