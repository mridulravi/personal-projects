/*
* 	This file defines a function ipStringToHex that takes as input an IP address 
*	in "dotted decimal" notation and returns the IP address in Hexadecimal format.
*  	For example: Input = 255.52.171.18 
*  	      		 Output = ff34ab12
*/


#ifndef IPSTRINGTOHEX_H
#define IPSTRINGTOHEX_H

#include<string>
#include<math.h>
#include<stdio.h>
using namespace std;


/*
This function takes as input a hexadecimal number(in char format) and 
returns its decimal equivalent(in int)
Example: a->10, 7->7, f->15
*/
int hexCharToInt(char a){
	if( ((int)a)>=48 && ((int)a)<=57){
		return ((int)a -48);
	}
	else if(((int)a)>=65 && ((int)a)<=70){
		return ((int)a -55);
	}
	else if(((int)a)>=97 && ((int)a)<=102){
		return ((int)a -87);
	}
}

int stringToInt(string input){
	int power = 0;
	int value = 0;
	for(int i=input.length()-1;i>=0;i--){
		value+=(hexCharToInt(input[i])*pow(10, power));
		power++;
	}
	return value;

}


string ipStringToHex(char * input){

	string firstOctet, secondOctet, thirdOctet, fourthOctet;
	/*
	*  firstOctet: Stores first octet (bits:24-31) of IP address(in decimal format)
	*  secondOctet: Stores second octet (bits:16-23) of IP address(in decimal format)
	*  thirdOctet:  Stores third octet (bits:8-15) of IP address(in decimal format)
	*  fourthOctet: Stores fourth octet (bits:0-7) of IP address(in decimal format)
	*/
	int i=0;
	for(;input[i]!='.';i++){
		firstOctet.push_back(input[i]);
	}
	i++;
	for(;input[i]!='.';i++){
		secondOctet.push_back(input[i]);
	}
	i++;
	for(;input[i]!='.';i++){
		thirdOctet.push_back(input[i]);
	}
	i++;
	for(;input[i]!='\0';i++){
		fourthOctet.push_back(input[i]);
	}

	//buf1,buf2,buf3 & buf4 store the hexadecimal values for firstOctet, secondOctet, thirdOctet & fourthOctet 
	char buf1[2], buf2[2], buf3[2], buf4[2];
		
		
	//sprintf stores the integer retured by stringToInt (in Hexadecimal format) in the buffer pointed by buf1,buf2,buf3 & buf4.
	sprintf(buf1, "%02x", stringToInt(firstOctet));
	sprintf(buf2, "%02x", stringToInt(secondOctet));
	sprintf(buf3, "%02x", stringToInt(thirdOctet));
	sprintf(buf4, "%02x", stringToInt(fourthOctet));
	
	// finally all the strings buf1,buf2,buf3 & buf4 are concatenated to form the final IP(in Hexadecimal format)
	string final_value;
	final_value.push_back(buf1[0]);
	final_value.push_back(buf1[1]);
	final_value.push_back(buf2[0]);
	final_value.push_back(buf2[1]);
	final_value.push_back(buf3[0]);
	final_value.push_back(buf3[1]);
	final_value.push_back(buf4[0]);
	final_value.push_back(buf4[1]);
	return final_value;	
}

#endif
