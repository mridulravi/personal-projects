/*
This is the program for a user. First, a UDP socket is created which sends a request (store/ request) to a node.
Then, we close this socket and make a TCP socket using the same port number. It then accepts the TCP connection request
from a node and finally sends/ receives a file to/ from the node.
*/
//-------------------------------------------------------
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <openssl/md5.h>
//---------------------------------------------------

#define MYPORT 3490
#define BACKLOG 10   // how many pending connections queue will hold
#define MAXSIZE 1024 //max size of buffer used while sending/ receiving file

//---------------------------------------------------
using namespace std;
//---------------------------------------------------

//This function takes the node id and returns a vector with the details of that node.
//(by reading the NodeMesh.cfg file)
//The vector has the IP Address, Port Number and the Folder name in that order.
vector<string> getNodeDetails(int nodeNum);

//This functions takes the name of a file as input and returns the md5 sum(as 16 unsigned chars) of that file in a vector.
vector<unsigned char> md5sumHelp(string filename);

//This function takes an unsigned char as input and returns the first(most significant) character
//of the hex representation of the ascii value of this input char.
char first(unsigned char a);

//This function takes an unsigned char as input and returns the second(least significant) character
//of the hex representation of the ascii value of this input char.
char second(unsigned char a);

//This function takes the name of a file as input and returns the md5 sum (in hex form) of that file in a string.
string md5sum(string input);

//----------------------------------------------------

int main(){
    int nodeNumber; // node which the user has to contact
    char requestType; // store or retrieve  file ( store : s, retrieve : r)
    string md5sumValue; // will store md5sum (in hex form)

    // path of the file to be stored by the node (in case of store) or to be retrieved from node (in case of retrieve)
    string filename;

    //take inputs from the user
    cout << "Please enter the id of the node you want to contact" <<endl;
    cin >> nodeNumber;
    cout << "Please enter the request type (r for retrieve and s for store)" <<endl;
    cin >> requestType;


    if(requestType == 'r'){
        cout<<"Please enter the md5 sum of the file:" <<endl;
        cin>>md5sumValue;
        cout<< "Please enter the file name in which you want to store the retrieved data" <<endl;
	    cin >> filename;
    }
    else if(requestType == 's'){
        //calculate the md5 sum
        cout<< "Please enter the file name which you want to send" <<endl;
	    cin >> filename;
        md5sumValue = md5sum(filename);
    }
    else{
    	cout<<"Unknown request type\nExiting\n";
    	exit(0);
    }
    // get IP address and port number of the node we want to send request to
    vector<string> node = getNodeDetails(nodeNumber);

    //------------------------------------------------

    //Create a datagram socket which will be bound to the port number MYPORT and will use the machine's IP address
    int udpSock; // socket descriptor for the datagram socket
    struct sockaddr_in my_addr; // my address information
    struct sockaddr_in their_addr; // address information of the node

    //filling all details for my_addr
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);   // use the port number defined in MYPORT
    my_addr.sin_addr.s_addr = INADDR_ANY;  // use the IP address of the machine the program is running on
    memset(&(my_addr.sin_zero), '\0', 8);  // zero the rest of the struct

    // filling all details for their_addr
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons( atoi( node[1].c_str())); // use port number of the node we want to send request to
    their_addr.sin_addr.s_addr = inet_addr( node[0].c_str()); // use IP addr of the node we want to send request to
    memset(&(their_addr.sin_zero), '\0', 8); // zero the rest of the struct

    // create socket
    if ((udpSock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    //allow program to reuse the port
    int yes = 1;
    if (setsockopt(udpSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    //bind the socket using my_addr struct
    if (bind(udpSock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    //------------------------------------------------


    // Prepare the char array (requestBuffer) to be sent in the UDP packet.
    // It has 32 bytes for md5 sum, 33rd byte is 'r' or 's' depending on the op and
    // then there are 12 bytes all of which are '0'. Thus, in all, 45 bytes will sent as part of request.

    char requestBuffer[60];

    //md5 sum
    for(int i=0; i<32; i++){
        requestBuffer[i]= md5sumValue[i];
    }

    //request type
    if(requestType == 'r') requestBuffer[32] = 'r';
    else requestBuffer[32] = 's';

    //next 12 bytes are all '0'
    for(int i=33;i<33+12;i++){
    	requestBuffer[i]='0';
    }

    //add a \0 at end so that we can print the buffer
	requestBuffer[45]='\0';

	printf("Request buffer array(md5sum+s/r+12 0's) is --- %s\n",requestBuffer);


    // send the udp packet
    int bytesSentInThisIteration, bytesYetToBeSent = 45, totalBytesSent = 0;
    while(1){
        if((bytesSentInThisIteration = sendto(udpSock, requestBuffer + totalBytesSent, bytesYetToBeSent,
            0, (struct sockaddr *)&their_addr , sizeof(struct sockaddr) )) == -1){
            perror("send");
            exit(1);
        }
        totalBytesSent += bytesSentInThisIteration;
        bytesYetToBeSent -= bytesSentInThisIteration;
        if(bytesYetToBeSent == 0){
            break;
        }
    }
	cout<<"UDP packet sent\n";
    close(udpSock); // close the udp socket

    //------------------------------------------------
    //------------------------------------------------

    // create a stream socket which listens on port number MYPORT

    int tcpSock;  // socket descriptor for the stream socket
    //create socket
    if ((tcpSock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    // allow program to reuse port number
    if (setsockopt(tcpSock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    // bind socket using my_addr struct
    if (bind(tcpSock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }
    // listen for connect() requests
    if (listen(tcpSock, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    int new_fd; // new socket descriptor returned by accept

    // accept connection
    int sin_size;
    if ((new_fd = accept(tcpSock, (struct sockaddr *)&their_addr,(socklen_t *)&sin_size)) == -1) {
        perror("accept");
        exit(1);
    }
    // allow program to reuse port number
    if (setsockopt(new_fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
    }
	cout<<"TCP connection accepted\n";

	// close tcpSock socket since we will now use new_fd
	close(tcpSock);

    if(requestType == 'r'){
        //we will receive data from the node

        // create and open the file (in write mode) in which we will store the received data
        FILE *fp;
        fp = fopen(filename.c_str(), "w");
        if(fp == NULL){
            printf("File not opened successfully\n");
            exit(1);
        }
        int numBytesReceived;   // keeps track of number of bytes received when recv() returns
        char buffer[MAXSIZE+1]; // buffer for receiving data

        // we will receive data till recv() returns 0 and in each iteration, we write the received data into the file.
        while(1){
            numBytesReceived = recv(new_fd, buffer, MAXSIZE, 0 );
            if(numBytesReceived == -1){
                perror("receive");
                exit(1);
            }
            if(numBytesReceived == 0){
                // it means the sender has closed the connection, so we should also close the connection
                fclose(fp); // close the file
                close(new_fd); // close the socket
                break;
            }
            // write into file
            fwrite(buffer, sizeof(char), numBytesReceived, fp);
        }
        fp = fopen(filename.c_str(),"r");
        if(fgetc(fp) == EOF){
        	printf("Error in retrieving file\nPlease check whether the md5sum is valid or not\n");
        	fclose(fp);
        	remove(filename.c_str());
        }
        else{
	        cout<<"File retrieved and saved successfully\n";
        }
    }

    if(requestType == 's'){
       // send data to the node
       char buffer[MAXSIZE+1]; // buffer for sending data

       //create and open the file (in read mode) which has to be sent
        FILE *fp;
        fp = fopen(filename.c_str(), "r");
        if(fp == NULL){
            printf("Error in File Opening\n");
            exit(1);
        }

        // stores the number of bytes that have been read from the file into the buffer on calling fread().
        // These bytes have to be sent in this iteration of the outer while loop.
        int bytesToBeSent;
        while(!feof(fp)){
            bytesToBeSent = fread(buffer,sizeof(char), MAXSIZE, fp);
            int totalBytesSent =0;  // stores the total bytes sent till now (in this iteration of the outer while loop)
            int bytesSentInThisIteration;   // stores the number of bytes sent by 1 call of send().
            while(totalBytesSent != bytesToBeSent){
                if((bytesSentInThisIteration = send(new_fd, buffer, bytesToBeSent - totalBytesSent, 0)) == -1){
                    perror("send");
                    exit(1);
                }
                cout<<"Bytes sent in this iteration is "<<bytesSentInThisIteration<<endl;
                totalBytesSent += bytesSentInThisIteration;
            }
        }
        cout<<"Complete file has been sent\n";
        fclose(fp); // close the file
        close(new_fd); // close the socket
    }

    exit(0);
}

//----------------------------------------------------
//This function takes the node id and returns a vector with the details of that node.
//(by reading the NodeMesh.cfg file)
//The vector has the IP Address, Port Number and the Folder name in that order.
vector<string> getNodeDetails(int nodeNum){
    vector<string> details; // stores the details
    details.resize(3);

    // open the file FileMesh.cfg which has the node details
    ifstream myfile ("FileMesh.cfg");

    string line;  // stores one line of the file
    int lineNum = 0;    // stores line number

    if(myfile.is_open()){
        while( getline(myfile,line)){
            if(lineNum == nodeNum){ // the current line read is the one whose details are needed.

                // split this line in 3 parts:
                // 1) ip (this is part which is before the colon
                // 2) port (this is after the colon and till the space
                // 3) folder (this is the part after the space till the end of the line

                string ip, port, folder;
                int colonIndex, spaceIndex,i;
                colonIndex = spaceIndex = i =0;
                for(;i<line.length(); i++){
                    if(line[i] == ':')
                        colonIndex = i;
                    if (line[i] == ' ')
                        spaceIndex = i;
                }
                ip = line.substr(0,colonIndex);
                port = line.substr(colonIndex + 1, spaceIndex - colonIndex - 1 );
                folder = line.substr(spaceIndex +1 , line.length() - spaceIndex -1);

                // store these parts into the details vector and return the vector.
                details[0]= ip;
                details[1] = port;
                details[2] = folder;
                return details;
            }
            else{ // the line read was not regarding the node we want, go to next line.
                lineNum ++ ;
                continue;
            }
        }
    }
    else{
    	printf("Error in opening Configuration file\nExiting\n");
    	exit(1);
    }
}

//----------------------------------------------------
//This functions takes the name of a file as input and returns the md5 sum(as 16 unsigned chars) of that file in a vector.
// taken from internet
vector<unsigned char> md5sumHelp(string filename)
{
    unsigned char c[MD5_DIGEST_LENGTH];
    vector<unsigned char> myvector;
    int i;
    FILE *inFile = fopen (filename.c_str(), "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL) {
        printf ("%s can't be opened.\n", filename.c_str());
        exit(1);
    }

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
    	myvector.push_back(c[i]);
    }
    fclose (inFile);
    return myvector;
}

//----------------------------------------------------
//This function takes an unsigned char as input and returns the first(most significant) character
//of the hex representation of the ascii value of this input char.
char first(unsigned char a)
{
	char b;
	if ((a/16) <= 9)    // first hex char is between 0 and 9
		b = (a/16)+48;
	else                // first hex char is between a and f
		b = (a/16)+87;
	return b;
}

//----------------------------------------------------
//This function takes an unsigned char as input and returns the second(least significant) character
//of the hex representation of the ascii value of this input char.
char second(unsigned char a)
{
	char b;
	if ((a%16) <= 9)    // second hex char is between 0 and 9
		b = (a%16)+48;
	else                // second hex char is between 0 and 9
		b = (a%16)+87;
	return b;
}

//----------------------------------------------------
//This function takes the name of a file as input and returns the md5 sum (in hex form) of that file in a string.
string md5sum(string input)
{
    // call md5sumHelp() to get the md5 sum in form of unsigned chars.
    // The for each char, call first() and second() to get the corrresponding hex characters
    // and push them into the output string.
    string outString;
    vector<unsigned char> outputVector;
    outputVector = md5sumHelp(input);
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
    	outString.push_back(first(outputVector[i]));
    	outString.push_back(second(outputVector[i]));
    }
    return outString;
}
