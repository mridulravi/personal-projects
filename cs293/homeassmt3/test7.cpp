// std_tr1__unordered_map__unordered_multimap_equal_range.cpp 
// compile with: /EHsc 

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue> 
 
typedef std::unordered_multimap<char, int> Mymap; 
typedef std::int z;
int main() 
    { 
    Mymap c1; 
    int z=0;
    c1.insert(Mymap::value_type('a', 1)); 
    c1.insert(Mymap::value_type('b', 2)); 
    c1.insert(Mymap::value_type('c', 3)); 
 
// display contents " [c 3] [b 2] [a 1]" 
    for (Mymap::const_iterator it = c1.begin(); 
        it != c1.end(); ++it) 
        std::cout << " [" << it->first << ", " << it->second << "]"; 
    std::cout << std::endl; 
 
// display results of failed search 
    std::pair<Mymap::iterator, Mymap::iterator> pair1 = 
        c1.equal_range('x'); 
    std::cout << "equal_range('x'):"; 
    for (; pair1.first != pair1.second; ++pair1.first) 
        std::cout << " [" << pair1.first->first 
            << ", " << pair1.first->second << "]"; 
    std::cout << std::endl; 
 
// display results of successful search 
    pair1 = c1.equal_range('b'); 
    std::cout << "equal_range('b'):"; 
    for (; pair1.first != pair1.second; ++pair1.first) 
        std::cout << " [" << pair1.first->first 
	//z = pair1.first->second;
            << ", " << pair1.first->second << "]"; 
    std::cout << std::endl; 
 
    return (0); 
    } 
