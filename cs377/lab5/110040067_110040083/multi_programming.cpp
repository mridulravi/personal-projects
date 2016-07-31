#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>
#include <functional>
#include <stdlib.h>
using namespace std;



struct process_phase{
	int iterations;
	int cpu_time;
	int io_time;
};

struct process{
	int p_id;
	int start_priority;
	int admission;
	vector<process_phase> phases;
};

struct sc_level{
	int level_number;
	int priority;
	int time_slice;
};

struct scheduler{
	int no_levels;
	vector<sc_level> levels;
};

vector<process> process_list;
scheduler my_scheduler;


void process_proc_file(){
	string line, line2;
	int pid, prior;
	int adm;
	int iter;
	int cpu_t, io_t;
	ifstream infile("PROCESS_SPEC");
	while (std::getline(infile, line))
	{
		if(line=="PROCESS"){
			process proc;
			getline(infile, line2);
			std::istringstream iss(line2);
		    if (!(iss >> pid >> prior >> adm)) { break; } // error
		    // cout<<pid<<endl<<prior<<endl;
			
			proc.p_id = pid;
			proc.start_priority = prior;
			proc.admission = adm;

			getline(infile, line2);
			while(line2 != "END"){
				std::istringstream iss(line2);
				process_phase pp;
			    if (!(iss >> iter >> cpu_t >> io_t)) { break; } // error
			    // cout<<cpu_t<<endl<<io_t<<endl;
			    
			    pp.iterations = iter;
			    pp.cpu_time = cpu_t;
			    pp.io_time = io_t;
			    (proc.phases).push_back(pp);
			    getline(infile, line2);
			}
			process_list.push_back(proc);
		}
	}
	// cout<<(process_list[1].phases[1]).io_time<<endl;
	// return 0;
}

void process_scheduler_file(){
	string line, line2;
	int level_count;
	int prior;
	int s_lvl;
	int t_slice;
	ifstream infile("SCHEDULER_SPEC");
	while (std::getline(infile, line))
	{
		if(line=="SCHEDULER"){
			getline(infile, line2);
			std::istringstream iss(line2);
		    if (!(iss >> level_count)) { break; } // error
		    // cout<<pid<<endl<<prior<<endl;
			
			my_scheduler.no_levels = level_count;
			for(int i=0; i<level_count; i++){
				getline(infile, line2);
				std::istringstream iss(line2);
				if (!(iss >> s_lvl >> prior >> t_slice)) { break; } // error
				sc_level scl;
				scl.level_number = s_lvl;
				scl.priority = prior;
				scl.time_slice = t_slice;
				my_scheduler.levels.push_back(scl);
			}
		}
	}
}

class ready_process{
public:
	ready_process()
	{
		blocked = false;
	
	}
	ready_process(int id, int a, vector<process_phase> b)
	{	
		process_id = id;
		priority = a;
		phases = b;
		phase_no = 0;
		blocked = false;
		time = 0;
	}
	int process_id, priority, time;
	vector<process_phase> phases;
	int phase_no;				// will start from zero
	bool blocked;
};

int my_clock;
priority_queue<process> event_table;
void scheduler_multiprogramming();

int main(){
	process_proc_file();
	//cout<<(process_list[1].phases[1]).io_time<<endl;
//	process_scheduler_file();
//	cout<<my_scheduler.levels[1].time_slice<<endl;
	
	// modify process_list
	for(int i =0;i<process_list.size();i++)
	{
		vector<process_phase>  temp;
		for(int j=0;j<process_list[i].phases.size();j++)
		{
			if(process_list[i].phases[j].iterations > 1)
			{
				while(process_list[i].phases[j].iterations != 1)
				{
					process_phase a;
					a.iterations = 1;
					a.cpu_time = process_list[i].phases[j].cpu_time;
					a.io_time = process_list[i].phases[j].io_time;
					temp.push_back(a);
					process_list[i].phases[j].iterations--;
				}
				temp.push_back(process_list[i].phases[j]);
			}
			else{
				temp.push_back(process_list[i].phases[j]);
			}
		}
		process_list[i].phases = temp;	
	}
	
# if 0	
	for(int i =0;i<process_list.size();i++)
	{
		for(int j=0;j<process_list[i].phases.size();j++)
		{	
			cout<<process_list[i].phases[j].iterations<<endl;
			cout<<process_list[i].phases[j].cpu_time<<endl;
			cout<<process_list[i].phases[j].io_time<<endl<<endl;
		}
		cout<<"#################################";
	}
# endif
	for(int i= 0;i<process_list.size();i++)
	{
		event_table.push(process_list[i]);
	}
	
	scheduler_multiprogramming();
	
	return 0;
}


// if any process starts IO, we will remove it from the PCB and add it to IO_list

// implement multiprogramming scheduler

typedef pair<int, ready_process> my_io;

void scheduler_multiprogramming()
{
		//priority_queue< my_io, vector<my_io>, greater<my_io> > io_list;
		priority_queue< pair<int, ready_process> > io_list;
		priority_queue< ready_process> pcb;
		
		if(event_table.empty() )
		{
			cout<<"Event table should not be empty\n";
			exit(1);
		}
		
		// add the first process in the pcb list from the event_table
		process p = event_table.top();
		event_table.pop();
		pcb.push(*new ready_process(p.p_id, p.start_priority, p.phases) );
		my_clock = p.admission;
		
		while(!event_table.empty() || !pcb.empty() || !io_list.empty() )
		{
			int time_next_process = -1, cpu_time =-1, io_time=-1;
			ready_process r;
			// select the highest priority process from the ready processes
			if(!pcb.empty() )
			{
				r = pcb.top();
				pcb.pop();
				cpu_time = r.phases[r.phase_no].cpu_time;			
			}
			if(!io_list.empty())
			{
				io_time = io_list.top().first;
			}
			if(!event_table.empty())
			{
				time_next_process = event_table.top().admission;
			}
			
			// all 3 cannot be negative simultaneously
			if(cpu_time == -1 && io_time == -1)
			{
				// here no process in pcb and in io_list

				// pop the process from event_table and push it in pcb
				p = event_table.top();
				event_table.pop();
				pcb.push(*new ready_process(p.p_id, p.start_priority, p.phases) );
				my_clock = p.admission;
				continue;
			}
			else if(io_time == -1 && time_next_process == -1)
			{
				// there are processes in pcb

				// now i have to check how much more work it has to do
				my_clock += r.phases[r.phase_no].cpu_time;
				r.time = my_clock;
				r.phases[r.phase_no].cpu_time = 0;
				r.phases[r.phase_no].iterations--;
				int new_time = my_clock + r.phases[r.phase_no].io_time;			// at this time IO will complete
				if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
				{
					r.phase_no++;
				}
				
				// now r will go in an IO operation
				io_list.push(make_pair(new_time, r) );
				
				cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					
				continue;			
			}
			else if(cpu_time == -1 && time_next_process == -1)
			{
				my_clock = io_time;
				ready_process r1 = io_list.top().second;
				//my_clock = io_list.top().first;
				io_list.pop();
					
				cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
				if(r1.phase_no >= r1.phases.size() )
				{
					cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
					// here the process is complete, need not push in pcb again
				}
				else
				{
					r1.time = my_clock;
					pcb.push(r1);
				}
				continue;
			
			}
			// absolutely correct till here
			else if(io_time == -1)
			{
				// io is empty, then we have to choose between pcb and event_table
				if(time_next_process < my_clock+cpu_time)
				{
					// execute current process upto that time and then bring the process from the event_table into pcb
					r.phases[r.phase_no].cpu_time = r.phases[r.phase_no].cpu_time - (time_next_process - my_clock);
					r.time = my_clock + cpu_time;
					my_clock = time_next_process;
					pcb.push(r);
					p = event_table.top();
					event_table.pop();
					pcb.push(* new ready_process(p.p_id, p.start_priority, p.phases) );
					continue;
				}
				else if(time_next_process == my_clock+cpu_time)
				{
					r.phases[r.phase_no].cpu_time = r.phases[r.phase_no].cpu_time - (time_next_process - my_clock);
					r.phases[r.phase_no].iterations--;
					if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
					{
						r.phase_no++;
					}
					my_clock = time_next_process;
					r.time = my_clock;
					int new_time = my_clock + r.phases[r.phase_no].io_time;			// at this time IO will complete
					// now r will go in an IO operation
					io_list.push(make_pair(new_time, r) );	
					
					cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					
					p = event_table.top();
					event_table.pop();
					pcb.push(* new ready_process(p.p_id, p.start_priority, p.phases) );
					continue;
				}
				else
				{
					// execute this instruction fully, push in IO and increment my clock
					my_clock += r.phases[r.phase_no].cpu_time;
					r.phases[r.phase_no].cpu_time = 0;
					r.time = my_clock;
					r.phases[r.phase_no].iterations--;
					int new_time = my_clock + r.phases[r.phase_no].io_time;			// at this time IO will complete
					if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
					{
						r.phase_no++;
					}

					// now r will go in an IO operation
					io_list.push(make_pair(new_time, r) );	
					
					cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					continue;			
				}
			}
			else if(cpu_time == -1)
			{
				// here there are no processes in pcb
				
				// case 1: io completes before next admission
				if(io_time < time_next_process )
				{	
					// here pop from io and push in pcb
					ready_process r1 = io_list.top().second;
					//my_clock = io_list.top().first;
					my_clock = io_time;
					io_list.pop();
					
					cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
					
					// check if it has to perform more function
					if(r1.phase_no >= r1.phases.size() )
					{
						cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
						// here the process is complete, need not push in pcb again
					}
					else
					{
						r1.time = my_clock;
						pcb.push(r1);
					}
					continue;
				}
				// case 2: io completes and next admission at same time
				else if(io_time == time_next_process)
				{
					// here pop from io and push in pcb
					ready_process r1 = io_list.top().second;
					//my_clock = io_list.top().first;
					my_clock = io_time;
					io_list.pop();
					
					cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
					
					if(r1.phase_no >= r1.phases.size() )
					{
						cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
						// here the process is complete, need not push in pcb again
					}
					else
					{
						r1.time = my_clock;
						pcb.push(r1);
					}
					
					// now pop from event_table and push in pcb
					
					p = event_table.top();
					event_table.pop();
					pcb.push(* new ready_process(p.p_id, p.start_priority, p.phases) );
					continue;
				}
				// case 3 : new admission before io completion
				else
				{
					my_clock = time_next_process;
					p = event_table.top();
					event_table.pop();
					pcb.push(* new ready_process(p.p_id, p.start_priority, p.phases) );
					continue;
				}
			}
			else if(time_next_process == -1)			
			{
				// case 1: io completes before cpu execution completion
				if(io_time < my_clock + cpu_time)
				{
					// execute upto that time and push again in pcb
					r.phases[r.phase_no].cpu_time = r.phases[r.phase_no].cpu_time - (io_time - my_clock);
					my_clock = io_time;
					r.time = io_time;
					pcb.push(r);
					
					// pop from IO and push into PCB
					ready_process r1 = io_list.top().second;
					io_list.pop();
					cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
					if(r1.phase_no >= r1.phases.size() )
					{
						cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
						// here the process is complete, need not push in pcb again
					}
					else
					{
						r1.time = my_clock;
						pcb.push(r1);
					}
					
					continue;

				}
				// case 2: io completion time =  cpu execution completion time
				else if(io_time == my_clock + cpu_time)
				{
					my_clock +=cpu_time;
				
					// pop from io and push in pcb
					ready_process r1 = io_list.top().second;
					io_list.pop();
						
					cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
					
					// whwnever we are poping from IO and pushing in pcb, check whether it has completed fully and need not be pushed
					if(r1.phase_no >= r1.phases.size() )
					{
						cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
						// here the process is complete, need not push in pcb again
					}
					else
					{
						r1.time = my_clock;
						pcb.push(r1);
					}
					
					// execute instruction and push in IO list
					r.phases[r.phase_no].cpu_time = 0;
					r.phases[r.phase_no].iterations--;
					int new_time = my_clock + r.phases[r.phase_no].io_time;		// at this time IO will complete
					if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
					{
						r.phase_no++;
					}
					r.time = my_clock;
					// now r will go in an IO operation
					cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, r) );
					continue;					
				}
				// case 3: io completes after cpu execution completion
				else
				{
					r.phases[r.phase_no].cpu_time = 0;
					r.phases[r.phase_no].iterations--;
					int new_time = my_clock + r.phases[r.phase_no].io_time;			// at this time IO will complete
					if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
					{
						r.phase_no++;
					}
					my_clock +=cpu_time;

					// now r will go in an IO operation
					r.time = my_clock;
					io_list.push(make_pair(new_time, r) );	
					cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					continue;					
				}
			}
			// correct till here
			else
			{
				// when all are non-negative
				if(time_next_process <= my_clock+cpu_time && time_next_process <= io_time)
				{
					// execute cpu upto that time and then 
					r.phases[r.phase_no].cpu_time = r.phases[r.phase_no].cpu_time - (time_next_process - my_clock);
					r.time = time_next_process;
					my_clock = time_next_process;
					pcb.push(r);
					
					// now pop from event_table and push it in pcb
					p = event_table.top();
					event_table.pop();
					pcb.push(* new ready_process(p.p_id, p.start_priority, p.phases) );
					continue;
				}
				else if(my_clock+cpu_time <= time_next_process && my_clock+cpu_time <= io_time)
				{
					// execute cpu fully and then push in io list
					my_clock +=cpu_time;
					r.phases[r.phase_no].cpu_time = 0;
					r.time = my_clock;
					int new_time = my_clock + r.phases[r.phase_no].io_time;			// at this time IO will complete
					if(r.phases[r.phase_no].iterations <= 0)		// if required no of iterations have been completed, then we will go to next phase
					{
						r.phase_no++;
					}

					// now r will go in an IO operation
					io_list.push(make_pair(new_time, r) );	
					cout<<"Process Id:"<<r.process_id<<" completed cpu at time "<<my_clock<<endl;
					continue;					
				}
				else 
				{
					// io completes first					
					r.phases[r.phase_no].cpu_time = r.phases[r.phase_no].cpu_time - (io_time - my_clock);
					my_clock = io_time;
					r.time = my_clock;
					pcb.push(r);
	
					ready_process r1 = io_list.top().second;
					io_list.pop();
					cout<<"Process Id:"<<r1.process_id<<" completed I/O at time "<<my_clock<<endl;
					if(r1.phase_no >= r1.phases.size() )
					{
						// here the process is complete, need not push in pcb again
						cout<<"Process Id:"<<r1.process_id<<" finished at time "<<my_clock<<endl;
					}
					else
					{
						r1.time = my_clock;
						pcb.push(r1);
					}
					continue;
				}
			}
		} 
}

// so operator overloading done for process
// pick the process whose admission time is least
bool operator < (const process & p1, const process & p2)
{
	return (p1.admission > p2.admission); 
}

// pick that ready process which has the highest priority
bool operator < (const ready_process & p1, const ready_process & p2)
{
	return (p1.priority < p2.priority); 
}

// pick that process whose IO is finishing earliest
bool operator < (const pair<int, ready_process> & p1, const pair<int, ready_process> & p2)
{
	return (p1.first > p2.first); 
}
