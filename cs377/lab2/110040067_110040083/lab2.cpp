#include<iostream>
#include<stdio.h>
#include<signal.h>
#include<string>
#include<string.h>
#include<list>
#include<vector>
#include<sys/types.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;

char * message;
int shm_id, parent_pid;
void * shm;

void processing(char * message);

void handler(int sig_num){
	// read from the shared memory
	char * message = (char *)malloc(1000 * sizeof(char));
	sscanf((char *) shm, "%s", message);
	processing(message);
}

struct sigaction sa_child;

vector<string> emails;
int main(){
	parent_pid = getpid();
	
	shm_id = shmget(IPC_PRIVATE, 1000*sizeof(char), IPC_CREAT | 0666);
	shm = shmat(shm_id,NULL,0);
	
	// create a vector of strings
	list< pair <string, int> > list_domain;

	string str, cmd, domain, email;
	list< pair <string, int> >::iterator it;
	bool domain_found = false;
	int child_pid;

/////////////////////////////////////////////////////////
	memset(&sa_child, 0, sizeof(sa_child));
	sa_child.sa_handler = &handler;
	sigaction(SIGUSR1, &sa_child, NULL);
/////////////////////////////////////////////////////////

	cout<<"\nEnter the command 'exit' if you want to kill all the child and the parent process\n\n";
	cout<<"Enter the command(Enter 'exit' for killing all processes)\n";
	
	while(getline(cin, str)){
		domain_found = false;
		// take input from user
		
		 

		// The following portion breaks the command in respective substrings	
		///////////////////////////////////////////////////////
		int pos = str.find(" ");
		cmd = str.substr(0, pos);
		if(cmd != "delete_domain"){
			email = str.substr(pos+1, string::npos);
			pos = str.find("@");
			domain =str.substr(pos+1, string::npos);
		}
		else if(cmd == "delete_domain"){
			domain = str.substr(pos+1, string::npos);
		}
		//////////////////////////////////////////////////////	
	
		if(cmd == "add_email"){
			for(it = list_domain.begin();it!=list_domain.end();it++){			
				if((*it).first == domain){	
					domain_found = true;
					break;
				}
			}
			email.append("#add");
			
			if(domain_found){
				// the pid of child process is (*it).second
				child_pid = (*it).second;
				// put the email in the shared memory
				sprintf((char *)shm, "%s", email.c_str());
				kill(child_pid,SIGUSR1);	// sends signal to child process
				sleep(1);
				kill(getpid(),SIGUSR1);
			}
			else{
				// create a child process for this domain and then do the operations
				child_pid = fork();
				list_domain.push_back(make_pair(domain, child_pid) );
				if(child_pid == 0){
					// inside the child process
					while(true){
					// so now the child will run for infinite time and when it receives the signal from parent it will perform the required action
					}
				}
				else{
					sprintf((char *)shm, "%s", email.c_str());
					if(kill(child_pid,SIGUSR1)==0){
					}
					else{
						cout<<"Error in sending signal..... Please try again\n";
					}
					sleep(1);
					kill(getpid(),SIGUSR1);
				}
			}
		}
		else if(cmd == "search_email"){	
			for(it = list_domain.begin();it!=list_domain.end();it++){			
				if((*it).first == domain){	
					domain_found = true;
					break;
				}
			}
			email.append("#search");
			
			if(domain_found){
				// the pid of child process is (*it).second
				child_pid = (*it).second;
				// put the email in the shared memory
				sprintf((char *)shm, "%s", email.c_str());
				kill(child_pid,SIGUSR1);	// sends signal to child process
				sleep(1);
				kill(getpid(),SIGUSR1);
			}
			else{
				cout<<" Parent process - Domain does not exist\n";
			}
		}
		else if(cmd == "delete_email"){
			for(it = list_domain.begin();it!=list_domain.end();it++){			
				if((*it).first == domain){	
					domain_found = true;
					break;
				}
			}
			email.append("#delete");
			
			if(domain_found){
				// the pid of child process is (*it).second
				child_pid = (*it).second;
				// put the email in the shared memory
				sprintf((char *)shm, "%s", email.c_str());
				kill(child_pid,SIGUSR1);	// sends signal to child process
				sleep(1);
				kill(getpid(),SIGUSR1);
			}
			else{
				cout<<" Parent process - Domain does not exist\n";
			}		
		}
		else if(cmd == "delete_domain"){
			for(it = list_domain.begin();it!=list_domain.end();it++){			
				if((*it).first == domain){	
					domain_found = true;
					break;
				}
			}
			if(domain_found){
				child_pid = (*it).second;
				email = "#delete_domain";
				sprintf((char *)shm, "%s", email.c_str());
				kill(child_pid, SIGUSR1);
				list_domain.erase(it);
				sleep(1);
				cout<<"Parent process - Domain "<<domain<<" with PID - "<<child_pid<<" deleted\n";
				kill(child_pid, 9);
			}
			else{
				cout<<"Parent process - Domain does not exist\n";
			}
		}
		else if(cmd == "Quit" || cmd == "quit"){
			for(it = list_domain.begin();it!=list_domain.end();it++){
				child_pid = (*it).second;
				email = "#delete_domain";
				sprintf((char *)shm, "%s",email.c_str());
				kill(child_pid, SIGUSR1);
				sleep(1);
				kill(child_pid, 9);				
			}
		}
		else if(cmd == "exit" || cmd == "Exit"){
			for(it = list_domain.begin();it!=list_domain.end();it++){
				child_pid = (*it).second;
				kill(child_pid, 9);
			}
			exit(0);
		}
		else{
			cout<<"Invalid command, please try again\n";
		}
		cout<<"\nEnter the command(Enter 'exit' for killing all processes)\n";
	}
	
	return 0;

}

void processing(char * message){
	// can be called by any of the child or parent process
	string inp = string(message);
	// now we have to check which process we are in
	// parent process or child process, we can do this by simply checking the current process id by a variable which stores the pid of the parent process

	if(parent_pid == getpid()){
		int pos1 = inp.find("#");
		string str2 = inp.substr(pos1+1, string::npos);
		string passed_email = inp.substr(0, pos1);	
		// in parent process
		if(str2 == "print"){
			replace(passed_email.begin(),passed_email.end(),'&',' ');
			cout<<passed_email<<endl;		
		}

	}
	else{
		// in child process
		int pos1 = inp.find("#");
		string str2 = inp.substr(pos1+1, string::npos);
		string passed_email = inp.substr(0, pos1);
		int pos2 =  inp.find("@");
		string passed_domain;
		if(pos2 != string::npos){
			passed_domain = inp.substr(pos2+1, pos1-pos2-1);
		}
		
		if(str2 == "add"){
			// add to the list
			bool found = false; 
			for(int i=0;i<emails.size();i++){
				if(emails[i] == passed_email){
					found = true;
					sprintf((char *)shm, "Child&process&%s&-&Email&address&already&exists#print", passed_domain.c_str());
					break;
				}
			}
			if(!found){
				emails.push_back(passed_email);
				sprintf((char *)shm, "Child&process&%s&-&Email&address&%s&added&successfully#print",passed_domain.c_str(), passed_email.c_str());
			
			}
		}
		else if(str2 == "search"){
			bool found = false; 
			for(int i=0;i<emails.size();i++){
				if(emails[i] == passed_email){
					found = true;
					sprintf((char *)shm, "Parent&process&-&found&the&email&address&%s&at&%d#print", passed_email.c_str(),i);
					break;
				}
			}
			if(!found){
				sprintf((char *)shm, "Parent&process&-&could&not&find&the&email&address&%s#print", passed_email.c_str());
			}					
		
		}
		else if(str2 =="delete"){
			bool found = false; 
			int i;
			for(i=0;i<emails.size();i++){
				if(emails[i] == passed_email){
					found = true;
					sprintf((char *)shm, "Child&process&-child&%s&deleted&%s&from&position&%d#print", passed_domain.c_str(), passed_email.c_str(),i);
					break;
				}
			}
			if(found){
			emails.erase(emails.begin()+i);
			}
			if(!found){
				sprintf((char *)shm, "Parent&process&-&child&%s&could&not&find&the&email&address&%s#print",passed_domain.c_str(),  passed_email.c_str());
			}		
		}
		else if(str2 == "delete_domain"){
			for(int i=0;i<emails.size();i++){
				cout<<emails[i]<<endl;
			}
		}
	}
}
