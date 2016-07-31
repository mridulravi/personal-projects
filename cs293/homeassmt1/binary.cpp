#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
string binary;
cout << "Enter the binary value you wish to convert into decimal: " << endl;
cin >> binary;

int counter = 0;
double decimal = 0;

while (counter < binary.size())
{
if(binary[counter] == '1')
{
decimal = (decimal + pow(2.0,counter));
}
else
decimal = (decimal +pow(0.0, counter));

counter++;
}
cout << "The decimal representation of the given binary is: " << decimal << endl;

return 0;
} 
