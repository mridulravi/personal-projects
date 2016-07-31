/*
	This is the FileMeshNode program
		-takes nodeId as argument
		-reads info about all the nodes from configuration file
		-receives UDP packet, and stores the md5sum
		-if the portion in the UDP packet which is intended for user's IP contains non-zero values then change the IP address and port no. 
		field in their_addr structure(structure which stores information about user), using the data received in the packet
		-if md5sum%N equals nodeNo, then create a new process which will create a TCP connection with the user and serve the user request
		-if md5sum%N not equals nodeNo, then we will change the IP address and Port no.(in hex digits) in the data received to that of the 
		user and forward the data to the correct(intended) node
		
*/

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
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<math.h>

#include "ipHexToString.h"
#include "ipStringToHex.h"
using namespace std;

# define MAXLENGTH 1024
# define BACKLOG 10

int md5hash(char inputmd5sum[], int N);				// function used for calculating md5sum%N
vector<string> getNodeDetails(int nodeNum);			// function which reads the details of the specific Node from the configuration file
void sigchld_handler(int s);

int main(int argc, char ** argv)
{
	int nodeNo,N;									// nodeNo stores the current node's no and N stores the total no. of nodes

	if(argc!=2){									// if wrong usage, then exit
		printf("Wrong Usage\n");
		printf("%s nodeNo\n",argv[0]);
		exit(0);
	}

	nodeNo = atoi(argv[1]);							

	char buffer[MAXLENGTH+1];			// creating a char array which will be used to store data to be sent and also data to be received
    int sockfd, newSockfd; 				// these will store the socket descriptors returned by the socket function

	// Reading the no of lines from the configuration file to determine the value of N(i.e. total no of nodes)
	ifstream myfile("FileMesh.cfg");
	string line;
	N=0;
	if(myfile.is_open()){
		while(getline(myfile,line)){
			N++;
		}
	}
	else{
		printf("Error in opening Configuration file\nExiting\n");
	}

    struct sockaddr_in nodeAddr[N]; 	// to store the details about all the nodes
    struct sockaddr_in theirAddr; 		// to store the details about the sender in case of UDP datagrams
    int sinSize;
    struct sigaction sa;
    int yes=1;
	string folderName;					// stores the name of the folder in which the files should be stored and retrieved from
	struct stat st = {0};
	
	// reading the information for all the nodes from the configuration file and storing them in the corresponding nodeAddr structures
	for(int i=0;i<N;i++){
		vector<string> details = getNodeDetails(i);
		nodeAddr[i].sin_family = AF_INET;
		nodeAddr[i].sin_port = htons( atoi(details[1].c_str()) );
		nodeAddr[i].sin_addr.s_addr =inet_addr(details[0].c_str() );
		bzero(&(nodeAddr[i].sin_zero), 8);
		if(i == nodeNo){
			folderName = details[2];		// if this is the current node, then store the folder name in folderName variable
		}
	}
	
	// If folder does not exist then creating it
	if(stat(folderName.c_str(), &st) == -1){
		mkdir(folderName.c_str(),0700);
		printf("folder %s created\n",folderName.c_str());
	}

	// creating a socket, In case of failure, printing the error and returning with exit status 1
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

	// For reusing the port even if it is still not completely freed by the kernel
	// In case of failure, printing the error and exiting the program with exit status 1
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

	// Associating the socket with the corresponding port
	// In case of failure exiting the program with exit status 1
    if (bind(sockfd, (struct sockaddr *)&nodeAddr[nodeNo], sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    while(1){				// This is the main loop, all sending, receiving will happen in this loop
    
		bool errorInReceivingUDP = false;
		
		// totalBytesReceived stores the total no of bytes received whereas bytesReceivedInThisIteration stores the amount of data 
		// received from a single packet, i.e. in a single iteration
		int totalBytesReceived=0, bytesReceivedInThisIteration;		
		int theirSize = sizeof(struct sockaddr);					

		// keep receiving till 45 bytes of Total data is not received
		while(totalBytesReceived!=45){
			
			// since receiving on UDP connection, therefore using the recvfrom function
			// In case of error in receiving, print the error and stop receiving the current data(break from this loop) and go to the 
			// starting mode, that is discard the data received in this iteration and again start waiting for a packet
			if( (bytesReceivedInThisIteration = recvfrom(sockfd, buffer+totalBytesReceived, MAXLENGTH, 0, (struct sockaddr*)&theirAddr, (socklen_t *)&theirSize ) ) == -1)			{
				perror("error in receiving md5");
				errorInReceivingUDP = true;
				break;
			}
			totalBytesReceived += bytesReceivedInThisIteration;		
	
			// If 45 bytes received then whole packet received, so stop waiting further for any UDP packet and break out from this loop 
		 	if(totalBytesReceived==45){			
		 		buffer[totalBytesReceived]='\0';
		 		printf("User request received\n");
		 		break;
		 	}
	 	}
	 	
	 	// If there was any error in receiving UDP packet, then this flag will be set to true
	 	// If set to true, then again start waiting for a UDP packet, i.e. discard the data received this time
		if(errorInReceivingUDP){
			continue;
		}

		bool userIpAddrIsAllZeroFlag = true;		// Set to false if user Ip Address Field is not filled with 0's in UDP packet
		char userIpAddr[8];							// To store the user's IP address(send in form of 8 hex digits) from the UDP packet
		char userPortNo[4];							// To store the user's Port Number(send in form of 4 hex digits) from the UDP packet
		char md5sumArray[32];						// To store the md5sum sent by the user(16 bytes, i.e. 32 hex digits)
		for(int i=0;i<32;i++){
			md5sumArray[i] = buffer[i];				// storing the md5sum in md5sumArray
		}
		char requestType = buffer[32];				// requestType stores the type of request
													// 'r' for retrieval and 's' for store
		for(int i=33;i<41;i++){
			userIpAddr[i-33] = buffer[i];			// storing the user's IP address (received as 8 hex digits)
			if(buffer[i]!='0'){						// If all the hex digits are not zero, then set the zero flag to false
				userIpAddrIsAllZeroFlag = false;
			}
		}
		for(int i=41;i<45;i++){
			userPortNo[i-41] = buffer[i];			// storing the user's port number(received as 4 hex digits)
		}
		
		// If all the hex digits for user's IP address was not zero, then this flag is set to false
		// If false, then it means that this request has been forwarded by a Node and has not come directly from User. Hence we need to 
		// modify the theirAddr structure, since we want to store user's IP address and user's port no in theirAddr structure
		if(!userIpAddrIsAllZeroFlag){				
			// storing the user's IP address in IP address field of theirAddr structure
			theirAddr.sin_addr.s_addr = inet_addr(ipHexToString(userIpAddr).c_str());
			// storing the user's Port No. in port no. field of theirAddr structure
			theirAddr.sin_port = htons(hexCharToInt(userPortNo[0])*4096 + hexCharToInt(userPortNo[1])*256 + hexCharToInt(userPortNo[2])*16 + hexCharToInt(userPortNo[3]) );
		}
				
		// fork() creates a new process and the value returned is zero for child process and non zero for parent process. Hence the child 
		// process will enter inside the if statement block, while for parent process the condition will evaluate to false and hence it 
		// will not enter inside the if statement block
		if(!fork()){			
			cout<<"The value of md5sum%N is "<<md5hash(md5sumArray, N)<<endl;
			// If md5sum%N equals nodeNo, then enter inside, i.e. checking if the request is inteneded for this node or not
			if(md5hash(md5sumArray, N)==nodeNo){		
				
				// creating a new socket, the socket is created for TCP connections(since SOCK_STREAM is used)
				// In case of failure, print the error message and exit with exit status 1
				// Notice that it will exit from the child process, the parent process will continue to run
				if ((newSockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
					perror("socket");
					exit(1);
				}
				
				// reusing the port no, if it was not completely freed by the kernel
				if (setsockopt(newSockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
					perror("setsockopt");
					exit(1);
				}
				
				// binding(associating) the socket with the corresponding port, i.e. the port assigned for this node 
				if (bind(newSockfd, (struct sockaddr *)&nodeAddr[nodeNo], sizeof(struct sockaddr)) == -1) {
					perror("bind");
					exit(1);
				}
				
				// sending connect request to user
				// In case of error, print the error message, close the socket and exit from the current process(i.e. the child 
				// process)				
				if(connect(newSockfd,(struct sockaddr*)&theirAddr, sizeof(struct sockaddr)) == -1){
					perror("Error in connect\n");
					close(sockfd);
					exit(1);
				}
				
				string fileName;			// stores the fileName, will store name in the format folderName/md5sum
				for(int i=0;i<folderName.length();i++){
					fileName.push_back(folderName[i]);		// pushing folder name
				}
				fileName.push_back('/');					// pushing a slash
				for(int j=0;j<32;j++){
					fileName.push_back(buffer[j]);			// pushing the md5sum
				}
				
				if(requestType == 's'){						// Enter if store request
					cout<<"Store request"<<endl;
					FILE *fp;								// creating a file pointer, will be used for file operations
					fp = fopen(fileName.c_str(), "w");		// opening the file in write mode			
					// if error in opening file, then print the error message and then exit with exit status 1
					if(fp == NULL){							
						printf("File Error");
						exit(1);
					}
					
					// receive packets from the user and write the data received in the file
					while(1){
						// receive the packet from the user, in case of error, print the error, close the socket and exit from the process
						if((bytesReceivedInThisIteration = recv(newSockfd, buffer, MAXLENGTH, 0)) == -1 ){
							perror("Error in receiving\n");
							fclose(fp);
							close(newSockfd);
							exit(1);
						}
						
						// this means that the collection has been closed by the user, so stop waiting for packets anymore. Close the file
						// and the socket
						if(bytesReceivedInThisIteration == 0){
							cout<<"File received successfully\n";
							fclose(fp);
							close(newSockfd);
							break;
						}
						else{			// writing to the file
							fwrite(buffer, sizeof(char), bytesReceivedInThisIteration, fp);
						}
					}
				}
				else if(requestType == 'r'){			// enter if retrieval request
					cout<<"Retrieve request\n";
					FILE *fp;							// creating a file pointer, will be used for file operations
					fp = fopen(fileName.c_str(),"r");	// opening file in read mode
					if(fp == NULL){						// if error in opening file, then print the error message and exit 
						printf("File Error");
						exit(1);
					}
					
					int bytesToBeSent;					// stores the amount of bytes to send 
					while(!feof(fp)){
						bytesToBeSent = fread(buffer, sizeof(char),MAXLENGTH, fp);		// reading data ftom the file in buffer array	
						int totalBytesSent=0, bytesSentInThisIteration;
						while(totalBytesSent!=bytesToBeSent){	// keep sending till all the bytes read from the file are not sent 
							if( (bytesSentInThisIteration = send(newSockfd, buffer, bytesToBeSent-totalBytesSent, 0) ) ==-1){
								perror("send\n");				// in case of error, print the error message and exit with status 1
								exit(1);
							}
							totalBytesSent+=bytesSentInThisIteration;
						}
					}
					cout<<"File sent successfully\n";
					fclose(fp);								// closing the file pointer
					close(newSockfd);						// closing the socket
				}
				else{
					printf("Unknown request type\nExiting\n");
					exit(0);
				}
			}
			else{
				int totalBytesSent=0, bytesYetToBeSent=45, bytesSentInThisIteration;
				
				// User's IP address is retrieved from theirAddr.sin_addr
				string userIpAddrInString = ipStringToHex(inet_ntoa(theirAddr.sin_addr));
				
				// User's Port No is retrieved from theirAddr.sin_port
				char userPort[4];
				sprintf(userPort, "%04x", ntohs(theirAddr.sin_port));
				
				// We have to change the buffer array, so that user's IP address and Port No is stored in it
				for(int i=33;i<41;i++){
					buffer[i] = userIpAddrInString[i-33];
				}
				for(int i=41;i<45;i++){
					buffer[i] = userPort[i-41];
				}

				// creating a new socket, the socket is created for UDP connections(since SOCK_DGRAM is used)
				// In case of failure, print the error message and exit with exit status 1
				// Notice that it will exit from the child process, the parent process will continue to run				
				if( (newSockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
					perror("socket");
					exit(1);
				}
				
				// reusing the port no, if it was not completely freed by the kernel
			    if (setsockopt(newSockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
					perror("setsockopt");
					exit(1);
				}
			
				// binding(associating) the socket with the corresponding port, i.e. the port assigned for this node 
				if(bind(newSockfd, (struct sockaddr*)&nodeAddr[nodeNo], sizeof(struct sockaddr)) == -1) {
					perror("bind");
					exit(1);
				}
				
				// if everything is fine, forward the request to the intended node
				while(1){								//Continue untill the whole request is sent
					// Send request packet to the correct node whose id is md5hash(md5sumArray, N)
					// Flag an error if unsuccessful and exit the process
					if( (bytesSentInThisIteration = sendto(newSockfd, buffer+totalBytesSent, bytesYetToBeSent, 0, (struct sockaddr *)&nodeAddr[md5hash(md5sumArray, N)], sizeof(struct sockaddr))) ==-1){
						perror("error in sendto\n");
						close(newSockfd);
						exit(1);
					}
					
					totalBytesSent += bytesSentInThisIteration;
					bytesYetToBeSent -= bytesSentInThisIteration;
					if(bytesYetToBeSent == 0){
						break;					// break from the loop when whole packet has been send
					}
				}
				
				//Close newSockfd once whole request is sent
				cout<<"Request forwarded to Node "<<md5hash(md5sumArray,N)<<endl;
				close(newSockfd);
			}
			close(sockfd);				// closing the socket
			// exiting from the process(note that this will exit from the child process, the parent process will still keep running)
			exit(0);					
		}
	}
    return 0;
}


/*
*	Takes as input the md5sum of the file (as a char array) and no. of nodes in mesh
* 	and returns m(f) % N - the node no. at which file is to be stored
*/
int md5hash(char inputmd5sum[], int N)
{
	int sum = 0;
	
	/* We are taking most significant 12 characters from the md5sum
	 * and calculating the sum of their ASCII values.
	 * Finally we return sum%N
	 */
	 
	for (int i=0; i< 32-20; i++)
	{
		sum += inputmd5sum[i];
	}
	return sum%N;
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
    }
}

void sigchld_handler(int s)
{
    while(wait(NULL) > 0);
}
