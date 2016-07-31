#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	map <string, int> mymap;
	fstream fp;
	fp.open("out");
	string str;
	
	if(fp.is_open() )
	{
		while(getline(fp, str) )
		{
			if(mymap[str] >= 1)
			{	
				mymap[str]++;
			}
			else
			{
				mymap[str] = 1;
			}
		}
	}
	
	map<string, int> :: iterator itr;
	
	for(itr = mymap.begin();itr!=mymap.end();itr++)
	{
		if( (*itr).second >1)
		{
			cout << (*itr).first <<endl;	
		}
	}
	
	return 0;
}
