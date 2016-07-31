#include <iostream>
#include <bitset>
#include <string>
#include <climits>
#include <math.h> 

template<typename T>
int show_binrep(const T& a)
{
    const char* beg = reinterpret_cast<const char*>(&a);
    const char* end = beg + sizeof(a);
	int temp;
	std::string binstr;
    while(beg != end)
        binstr.insert(0, (std::bitset<CHAR_BIT>(*beg++)).to_string());
    for (int i = 0; i< binstr.size(); i++)
	{	
		char c = binstr[i];
		int a = c;
		temp = temp + a*pow(2,i);
		if (temp < 0.0)
			break;
		std::cout<<temp<<'\n';
	}
	return temp;
}


int main()
{
    float i = 10.0;
	float d;
	
	for (i = 10.0; i <pow (100000000000000.0, 1000000.0); i=i*10.0)
	{
		d = show_binrep(i);
	}
	
	std::cout<<"The required integer is"<< -d <<'\n';
}





