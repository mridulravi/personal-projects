#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<queue>
#include<string>
#include<fstream>
#include<utility>
#include<vector>
using namespace std;

// creating variables which will store the status of all the threads
int status[4];
// These will have the value 0 if ready, 1 if blocked for receive, 2 if blocked for send, -1 for complete(used for initialization as well)


pthread_t threads[4];
pthread_mutex_t ipc_mutex;
pthread_cond_t cond0, cond1, cond2, cond3, buf_size;

// all the buffers
queue< pair<int, string> > buf0, buf1, buf2, buf3;

vector<string> readInput(string base)
{
  vector<string> myvector;
  string space (" ");
  size_t found = base.find(space);
  string str2 = base.substr (0,found);   
  
  if(str2.compare("send") == 0)
  {
    myvector.push_back(str2);
    string str7 = base.substr (found+1,base.size()-1);
    found = str7.find(space);
    string str4 = str7.substr (0,found);
    myvector.push_back(str4);
    string str5 = str7.substr (found+1,str7.size()-1);
    myvector.push_back(str5);
  }
  else if(str2.compare("receive") == 0)
  {
    myvector.push_back(str2);
  }
  return myvector;

}

void deadlock_check()
{
	// here if all the threads which are not complete are either send blocked or receive blocked, then done
	int i=0;
	for(;i<4;i++)
	{
		if(status[i] == 0)			// if process is in ready state, then return from this function
		{
			return ;
		}
		if(status[i] == 1)
		{	// if we are sending to a thread and which is blocked, and this send is the last instruction in the file, then we will exit the current thread after the send instruction, the thread blocked on receive will get unblocked but its varible's value will not change, so we are considering that case here				
			switch(i)				
			{
				case 0:
				{
					if(!buf0.empty())
					{
						return;
					}
					break;
				}
				case 1:
				{
					if(!buf1.empty())
					{
						return;
					}
					break;
				}
				case 2:
				{
					if(!buf2.empty())
					{
						return;
					}
					break;
				}
				case 3:
				{
					if(!buf3.empty())
					{
						return;
					}
					break;
				}
			}
		}
		if(status[i] == 2)
		{
			// here if one thread is send blocked, and the last instruction of a file is receive which rduces the buffer by one and unblocks the bocked thread
			if( (buf0.size() + buf1.size() + buf2.size() + buf3.size() ) < 20 )
			{
				break;
			}
		}
	}
	
	// if all processes are complete, then return
	if(status[0] == -1 && status[1] == -1 && status[2] == -1 && status[3] == -1 )
	{
		return ;
	}
	
	// if all the processes blocked, either for receive or for send, then deadlock is there
	printf("\n***************************\nError, Deadlock detected\n***************************\n");
//	printf("Error, Deadlock detected\n");
//	printf("***************************\n");
	exit(1);
}
// whenever wait is called then it releases the mutex lock, and blocks the process(itself) and when the process again comes to running from blocked state, then the mutex lock is again gained

// create a function ipc
string ipc(int op, int s_id, int r_id, string msg)
{
	// op = 1 means receive, op = 0 means send
	// s_id --> sender's id, r_id--> receiver's id

	//printf("\nIn IPC, parameters\nop - %d\ns_id - %d\nr_id - %d\nmsg - %s\n\n", op, s_id, r_id, msg.c_str() );

	// if receive
	if(op == 1)
	{
		// if message already present in buffer, then read from the buffer, print the message, pop from the buffer
		bool msg_received = false;
		switch(r_id)
		{		
			case 0:
			{
				while(buf0.empty())
				{
					status[0] = 1;
					deadlock_check();
					pthread_cond_wait(&cond0, &ipc_mutex);
					status[0] = 0;
				}
				s_id = buf0.front().first;
				msg = buf0.front().second;
				buf0.pop();
				printf("Message received: %d, %d, %s\n", s_id, r_id, msg.c_str());	
				msg_received = true;
				break;
			}
			case 1:
			{
				while(buf1.empty())
				{
					status[1] = 1;
					deadlock_check();
					pthread_cond_wait(&cond1, &ipc_mutex);
					status[1] = 0;
				}
				s_id = buf1.front().first;
				msg = buf1.front().second;
				buf1.pop();
				printf("Message received: %d, %d, %s\n", s_id, r_id, msg.c_str());
				msg_received = true;
				break;
			}
			case 2:
			{
				while(buf2.empty())
				{
					status[2] = 1;
					deadlock_check();
					pthread_cond_wait(&cond2, &ipc_mutex);
					status[2] = 0;
				}
				s_id = buf2.front().first;
				msg = buf2.front().second;
				buf2.pop();
				printf("Message received: %d, %d, %s\n", s_id, r_id, msg.c_str());
				msg_received = true;
				break;
			}
			case 3:
			{
				while(buf3.empty())
				{
					status[3] = 1;
					deadlock_check();
					pthread_cond_wait(&cond3, &ipc_mutex);
					status[3] = 0;
				}
				s_id = buf3.front().first;
				msg = buf3.front().second;
				buf3.pop();
				printf("Message received: %d, %d, %s\n", s_id, r_id, msg.c_str());
				msg_received = true;
				break;
			}		
			default:
				printf("Error, wrong thread id\n");
				exit(1);
		}
		if(msg_received && (buf0.size() + buf1.size() + buf2.size() + buf3.size() )< 20)
		{
			pthread_cond_signal(&buf_size);
		}
		return msg;
	}
	else		// op == 0, i.e. send
	{	// here we will have to send to the process	
		
		while( (buf0.size() + buf1.size() + buf2.size() + buf3.size() )>= 20)
		{	
			// here the buffer size is full, we will have to wait till its size becomes less than 20
			status[s_id] = 2;
			deadlock_check();
			pthread_cond_wait(&buf_size, &ipc_mutex);
			status[s_id] = 0;
		}
		
		if((buf0.size() + buf1.size() + buf2.size() + buf3.size() )< 20)
		{
			switch(r_id)
			{
				case 0:
				{
					buf0.push(make_pair(s_id, msg) );
					pthread_cond_signal(&cond0);
					break;
				}
				case 1:
				{
					buf1.push(make_pair(s_id, msg) );
					pthread_cond_signal(&cond1);
					break;
				}
				case 2:
				{
					buf2.push(make_pair(s_id, msg) );
					pthread_cond_signal(&cond2);
					break;
				}
				case 3:
				{
					buf3.push(make_pair(s_id, msg) );
					pthread_cond_signal(&cond3);
					break;
				}
				default:
					printf("Error, wrong thread id\n");
					exit(1);
			}
			printf("Message sent: %d, %d, %s\n", s_id, r_id, msg.c_str());
		}
		return msg;
	}
}

// starting routines for all the threads
void * fun( void * id)
{
	long tid = (long) id;
	string filename;
	string msg;
	if(tid == 0)
	{
		//cout<<"Enter filename for thread "<<tid<<endl;
		//cin>>filename;
		filename = "file0";
	}
	else if(tid == 1)
	{
		//cout<<"Enter filename for thread "<<tid<<endl;
		//cin>>filename;
		filename = "file1";
	}
	else if(tid == 2)
	{
		//cout<<"Enter filename for thread "<<tid<<endl;
		//cin>>filename;
		filename = "file2";
	}
	else
	{
		//cout<<"Enter filename for thread "<<tid<<endl;
		//cin>>filename;
		filename = "file3";
	}

	// read from the file
	ifstream fp(filename.c_str());
	if(!fp)
	{
		printf("Error in opening file\n");
		exit(1);
	}
	//printf("File opened in thread %ld \n", tid);
	string str;
	
	while(getline(fp, str))
	{
		// reading one line	
		// break it into words
		//printf("Thread %ld, Input:%s\n", tid, str.c_str() );
		vector<string> myVec = readInput(str);
		//printf("Hellllllo\n");
		
		if(myVec.size() == 1)			// receive
		{
			string str111 = "iii"; 
			// here i will call ipc function
			pthread_mutex_lock(&ipc_mutex);
			msg = ipc(1, -1, tid, str111);			// here send the parameters according to receiving
			//printf("In thread %ld, msg is %s\n", tid, msg.c_str() ); 
			pthread_mutex_unlock(&ipc_mutex);
		}
		else			// send	
		{
			//printf("Size of myVec is %d\n", myVec.size());
			pthread_mutex_lock(&ipc_mutex);
			ipc(0, tid, atoi(myVec[1].c_str() ), myVec[2]);			// here send the parameters according to send	
			pthread_mutex_unlock(&ipc_mutex);
		}	
	}
	
	// changing the variables value which denotes its status
	switch(tid)
	{	
		case 0:
		{
			status[0] = -1;
			break;
		}
		case 1:
		{
			status[1] = -1;
			break;
		}
		case 2:
		{
			status[2] = -1;
			break;
		}
		case 3:
		{
			status[3] = -1;
			break;
		}
		default:
			printf("Error, wrong thread id\n");
			exit(1);
	}
	deadlock_check();
	pthread_exit(NULL);
}

int main()
{
	pthread_mutex_init(&ipc_mutex, NULL);
	pthread_cond_init(&buf_size, NULL);
	pthread_cond_init(&cond0, NULL);
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_cond_init(&cond3, NULL);
	
	status[0] = status[1] = status[2] = status[3] = 0;
/*	
	cout<<"Size of pthread_t is "<<sizeof(pthread_t)<<endl;
	cout<<"Size of int is "<<sizeof(int)<<endl;
	cout<<"Size of double is "<<sizeof(double)<<endl;
	cout<<"Size of long int is "<<sizeof(long int)<<endl<<endl;
*/

	long int rc, i;
	void * status;

	for(i=0;i<4;i++)
	{
		rc = pthread_create(&threads[i],NULL, fun, (void*) i);
		if(rc)
		{
			printf("Error in pthread_create, error no: %ld\n", rc);
			exit(1);
		}		
	}
	// all threads created
	//cout<<"All threads created\n";

// after calling pthread_create, pthread_t variable with which the pthread_create function was called will contain the id of the thread


	for(i=0;i<4;i++)
	{
		rc = pthread_join(threads[i], &status);
		if(rc)
		{
			printf("Error in pthread_join\n");
			exit(1);
		}
	}
	//pthread_exit(NULL);				// better to use join
	pthread_cond_destroy(&cond0);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_cond_destroy(&cond3);
	pthread_cond_destroy(&buf_size);
	pthread_mutex_destroy(&ipc_mutex);
	
/*
//	These are actually printing the ids of the thread
	printf("%lu\n",threads[0]);
	printf("%lu\n",threads[1]);
	printf("%lu\n",threads[2]);
	printf("%lu\n",threads[3]);	
*/	
	
	return 0;
}



