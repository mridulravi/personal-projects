/*
* 	This file defines a function ipHexToString that takes as input an IP address 
*	in Hexadecimal format and returns the IP address in "dotted decimal" notation.
*  	For example: Input = ff34ab12
*  	      		 Output = 255.52.171.18 
*/

#ifndef IPHEXTOSTRING_H
#define IPHEXTOSTRING_H

#include<stdio.h>
#include<string>
#include<string.h>
#include "ipStringToHex.h"
using namespace std;

string ipHexToString(char * input){
	int firstOctet, secondOctet, thirdOctet, fourthOctet;
	
	/* 
	*  firstOctet: Stores first octet (bits:24-31) of IP address(in decimal format)
	*  secondOctet: Stores second octet (bits:16-23) of IP address(in decimal format)
	*  thirdOctet:  Stores third octet (bits:8-15) of IP address(in decimal format)
	*  fourthOctet: Stores fourth octet (bits:0-7) of IP address(in decimal format)
	*/
	
	// We use function hexCharToInt to convert a hexadecimal number to its decimal equivalent
	firstOctet = hexCharToInt(input[0]) * 16 + hexCharToInt(input[1]);
	secondOctet = hexCharToInt(input[2]) * 16 + hexCharToInt(input[3]);
	thirdOctet = hexCharToInt(input[4]) * 16 + hexCharToInt(input[5]);
	fourthOctet = hexCharToInt(input[6]) * 16 + hexCharToInt(input[7]);
	
	char ip1[3], ip2[3], ip3[3], ip4[3];
	
	//sprintf stores the integer retured by hexCharToInt as a C string in the buffer pointed by ip1,ip2,ip3 & ip4.
	sprintf(ip1, "%d", firstOctet);  
	sprintf(ip2, "%d", secondOctet);
	sprintf(ip3, "%d", thirdOctet);
	sprintf(ip4, "%d", fourthOctet);

	// finally all the strings ip1,ip2,ip3 & ip4 are concatenated(along with .) to form the final IP
	string ip;
	for(int i=0;i<strlen(ip1);i++){
		ip.push_back(ip1[i]);
	}
	ip.push_back('.');
	for(int i=0;i<strlen(ip2);i++){
		ip.push_back(ip2[i]);
	}
	ip.push_back('.');
	for(int i=0;i<strlen(ip3);i++){
		ip.push_back(ip3[i]);
	}
	ip.push_back('.');
	for(int i=0;i<strlen(ip4);i++){
		ip.push_back(ip4[i]);
	}
	return ip;
}

#endif
