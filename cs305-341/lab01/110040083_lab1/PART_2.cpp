#include <iostream>
#include <bitset>
#include <string>
#include <climits>

template<typename T>
void show_binrep(const T& a)
{
    const char* beg = reinterpret_cast<const char*>(&a);
    const char* end = beg + sizeof(a);
	std::string binstr;
    while(beg != end)
        binstr.insert(0, (std::bitset<CHAR_BIT>(*beg++)).to_string());
    std::cout << binstr << '\n';
}

template<typename T>
void show_hexrep(const T& a)
{
    const char* beg = reinterpret_cast<const char*>(&a);
    const char* end = beg + sizeof(a);
	std::string str;
    while(beg != end)
        str.insert(0, (std::bitset<CHAR_BIT>(*beg++)).to_string());
	std::string hex;
	for (int i = 0 ; i < str.size(); i=i+4)
	{
		std::string part;
		part.push_back(str[i]); 
		part.push_back(str[i+1]); 
		part.push_back(str[i+2]); 
		part.push_back(str[i+3]);
		if (part.compare("0000") == 0)
			{hex.push_back('0');}
		else if (part.compare("0001") == 0)
			{hex.push_back('1');}
		else if (part.compare("0010") == 0)
			{hex.push_back('2');}
		else if (part.compare("0011") == 0)
			{hex.push_back('3');}
		else if (part.compare("0100") == 0)
			{hex.push_back('4');}
		else if (part.compare("0101") == 0)
			{hex.push_back('5');}
		else if (part.compare("0110") == 0)
			{hex.push_back('6');}
		else if (part.compare("0111") == 0)
			{hex.push_back('7');}
		else if (part.compare("1000") == 0)
			{hex.push_back('8');}
		else if (part.compare("1001") == 0)
			{hex.push_back('9');}
		else if (part.compare("1010") == 0)
			{hex.push_back('A');}
		else if (part.compare("1011") == 0)
			{hex.push_back('B');}
		else if (part.compare("1100") == 0)
			{hex.push_back('C');}
		else if (part.compare("1101") == 0)
			{hex.push_back('D');}
		else if (part.compare("1110") == 0)
			{hex.push_back('E');}
		else if (part.compare("1111") == 0)
			{hex.push_back('F');}
	}
	std::cout << hex << '\n';
}


int main()
{
    int a;
    float b;
    double c;
	std::cout << "Enter the negative integer number:";
	std::cin >> a;
	std::cout << "Binary representation of this negative integer number:\n";
	show_binrep(a);
	std::cout << "Hex representation of this negative integer number:\n";
	show_hexrep(a);

	std::cout << "Enter the single precision floating point number:";
	std::cin >> b;
	std::cout << "Binary representation of this single precision floating point number:\n";
	show_binrep(b);
	std::cout << "Hex representation of this single precision floating point number:\n";
	show_hexrep(b);

	std::cout << "Enter the double precision floating point number:";
	std::cin >> c;
	std::cout << "Binary representation of this double precision floating point number:\n";
	show_binrep(c);
	std::cout << "Hex representation of this double precision floating point number:\n";
	show_hexrep(c);
}





