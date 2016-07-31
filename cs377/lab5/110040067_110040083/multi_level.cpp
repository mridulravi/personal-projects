#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;



struct process_phase{
	int iterations;
	int cpu_time;
	int io_time;
};

struct process{
	int p_id;
	int priority;
	int admission;
	int time;
	int phase_no;
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
			proc.priority = prior;
			proc.admission = adm;
			proc.time =adm;
			proc.phase_no = 0;				
				
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

int my_clock;
vector<process> scheduling_queue;
priority_queue<process> event_table;
priority_queue<pair<int, process> > io_list;
int find_time_slice(int pr);
int find_higher_priority(int curr);
int find_lower_priority(int curr);
vector<process>::iterator find_process(int pr);
int find_highest_priority_queue();
void scheduling_multi_level();

void print_event_table();
void print_process(process p1);
void print_levels();

bool func(sc_level i, sc_level j)
{
	return i.priority > j.priority;
}


int main(){
	process_proc_file();
//	cout<<(process_list[1].phases[1]).io_time<<endl;
	process_scheduler_file();
//	cout<<my_scheduler.levels[1].time_slice<<endl;
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

	// sorted in decreasing order
	sort(my_scheduler.levels.begin(), my_scheduler.levels.end(), func);
	//print_levels();

	for(int i= 0;i<process_list.size();i++)
	{
		event_table.push(process_list[i]);
	}

	scheduling_queue.reserve(event_table.size());
//	cout<<"capacity is "<<scheduling_queue.capacity()<<endl;
//	cout<<"size is "<<scheduling_queue.size()<<endl;
	// print all the vectors
	//print_event_table();
	
	scheduling_multi_level();
	
	return 0;
}

void print_levels()
{
	cout<<"Printing Levels\n";
	for(int i = 0;i<my_scheduler.levels.size();i++)
	{
		cout<<"Level no. "<<my_scheduler.levels[i].level_number<<endl;
		cout<<"Priority "<<my_scheduler.levels[i].priority<<endl;
		cout<<"Time Slice "<<my_scheduler.levels[i].time_slice<<endl;
		cout<<endl;
	}
	cout<<endl<<endl;
}

void print_event_table(){
	while(!event_table.empty())
	{
		print_process(event_table.top());	
		event_table.pop();
		cout<<endl;
	}
};

void print_process(process p1)
{
	cout<<"process id --> "<<p1.p_id<<endl;
	cout<<"process priority --> "<<p1.priority<<endl;
	cout<<"process adm -->"<<p1.admission<<endl;
	
	for(int i =0;i<p1.phases.size();i++)
	{
		cout<<"Iterations "<<p1.phases[i].iterations<<endl;
		cout<<"CPU burst "<<p1.phases[i].cpu_time<<endl;
		cout<<"IO burst "<<p1.phases[i].io_time<<endl;
	}
}

int find_highest_priority_queue()
{
	if(scheduling_queue.empty())
	{
		return 0;
	}
	// scheduling_queue is global vector of processes
	int max = scheduling_queue[0].priority;
	for(int i = 1; i<scheduling_queue.size();i++)
	{
		if (max < scheduling_queue[i].priority)
		{
			max = scheduling_queue[i].priority;
		}	
	}
	return max;
}

vector<process>::iterator find_process(int pr)
{
	vector<process>::iterator itr;
	for(itr = scheduling_queue.begin();itr!=scheduling_queue.end();itr++)
	{
		if( (*itr).priority == pr)
		{
			return itr;
		}
	}
}

// make a common list for io, it will have all the processes which are doing IO, so pick from the top and check its priority, if it is more then priority of currently executing process, then stop this process and start executing that process

void scheduling_multi_level()
{
	
	// scheduling queue will not serve processes with same priority in round-robin fashion, we have to use vector for that,
	// create a function named find_highest_priority_queue
	// create function return process with priority p	
	
	int count = 0;
	int cpu_time = -1, io_time = -1, time_next_process = -1;	
	
	process p = event_table.top();
	event_table.pop();
	my_clock = p.admission;
	scheduling_queue.push_back(p);
	count++;

	while(!event_table.empty() || !scheduling_queue.empty() || !io_list.empty() )
	{
		vector<process>::iterator itr ;
		int pr;
		int cpu_time = -1, io_time = -1, time_next_process = -1, time_slice = 0;
		if(!event_table.empty() )
		{
			//cout<<"in event\n";
			time_next_process = event_table.top().admission;
		}
		if(!scheduling_queue.empty() )
		{
			pr = find_highest_priority_queue();
			itr = find_process(pr);
			cpu_time = (*itr).phases[(*itr).phase_no].cpu_time;
			time_slice = find_time_slice(pr);
			//cout<<"Pr is "<<pr<<endl;
			//cout<<"itr is iterator to process "<<(*itr).p_id<<endl;
			//scheduling_queue.erase(itr);
			//cout<<"element deleted\n";
		}
		if(!io_list.empty() )
		{
			//cout<<"in io\n";
			io_time = io_list.top().first;
		}
	
		//cout<<event_table.size()<<"		"<<count<<"		"<<io_list.size()<<endl;
	
		if(time_next_process == -1 && io_time == -1)
		{
			// here we only have processes in scheduling queue
			if(cpu_time < time_slice)
			{
				// means it will start an I/O now, so now increase its priority and schedule an IO
				my_clock += cpu_time;
				p = *itr;
				scheduling_queue.erase(itr);
				count--;

				p.priority = find_higher_priority(p.priority);
				p.time = my_clock;
				p.phases[p.phase_no].cpu_time = 0;
				int new_time = my_clock + p.phases[p.phase_no].io_time;
				p.phase_no++;
				cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
				io_list.push(make_pair(new_time, p) );
				continue;				
			}
			else if(cpu_time == time_slice)
			{
				my_clock +=time_slice;
				p = *itr;
				scheduling_queue.erase(itr);
				count--;
				
				p.phases[p.phase_no].cpu_time = 0;
				p.priority = find_lower_priority(p.priority);
				int new_time = p.phases[p.phase_no].io_time + my_clock;
				p.phase_no++;
				cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
				io_list.push( make_pair(new_time, p));
				continue;
			}
			else
			{
				// here cpu executes for full time_slice, decrease its priority and schedule it again
				my_clock +=time_slice;
				p = *itr;
				scheduling_queue.erase(itr);
				count--;
				
				p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - time_slice;
				p.priority = find_lower_priority(p.priority);
				p.time = my_clock;
				
				scheduling_queue.push_back(p);
				count++;
			}
		}
		else if(cpu_time == -1 && io_time == -1)
		{
			// here pop from event_table and push in scheduling_queue;
			p = event_table.top();
			event_table.pop();
			
			my_clock = p.admission;
			p.time = my_clock;
			p.phase_no = 0;
			scheduling_queue.push_back(p);
			count++;
			continue;
		}
		else if(cpu_time == -1 && time_next_process == -1)
		{
			// here there are processes only in io list
			p = io_list.top().second;
			my_clock = io_list.top().first;
			io_list.pop();
			p.time = my_clock;
			
			cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<my_clock<<endl;
			if(p.phase_no >=p.phases.size())
			{
				cout<<"Process ID:"<<p.p_id<<" finished at time "<<my_clock<<endl;
			}
			else
			{
				scheduling_queue.push_back(p);
			}
			
			count++;
			continue;		
		}
		else if(io_time == -1)
		{	
			// here there are no IO operations
			// both of the other are non-null
			
			//cout<<"itr is "<<(*itr).p_id<<endl;
			
			if(cpu_time < time_slice)
			{
				// here cpu finishes earlier then time_slice
				if(time_next_process < cpu_time + my_clock)
				{
					// pop from event_table and push in scheduling queue
					p = event_table.top();
					event_table.pop();
					
					//my_clock = time_next_process;
					p.time = time_next_process;
					// extract index from itr
					
					scheduling_queue.push_back(p);
					count++;
					// reassign itr
					
					if(p.priority > pr)
					{
						//cout<<"in pr\n";
						// here execute the process upto time_next_process
						p = (*itr);
						p.time = time_next_process;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
						my_clock = time_next_process;
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here cpu will start an IO operation
						my_clock +=cpu_time;
						//cout<<"in req\n";
						//cout<<"itr points to "<<(*itr).p_id<<endl;						
						p = (*itr);
						//cout<<"p's id is "<<p.p_id<<endl;
						//cout<<"p's priority s "<<p.priority<<endl;
						p.time = time_next_process;
						//cout<<"itr points to "<<(*itr).p_id<<endl;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = 0;
						p.priority = find_higher_priority(p.priority);
						int new_time = p.phases[p.phase_no].io_time + my_clock;
						p.phase_no++;
						
						cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
						
						io_list.push(make_pair(new_time, p));
						continue;
					}
				}
				else
				{
					// here cpu will start an IO first
					my_clock += cpu_time;
					p = *itr;
					p.time = time_next_process;
					scheduling_queue.erase(itr);
					count--;
					p.phases[p.phase_no].cpu_time = 0;
					p.priority = find_higher_priority(p.priority);
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					
					io_list.push(make_pair(new_time, p));
					continue;
				}			
			}
			else if(cpu_time == time_slice)
			{
				// here also the same cases as above
				if(time_next_process < cpu_time + my_clock)
				{
					// pop from event_table and push in scheduling queue
					p = event_table.top();
					event_table.pop();
					
					//my_clock = time_next_process;
					p.time = time_next_process;
					scheduling_queue.push_back(p);
					count++;
					
					if(p.priority > pr)
					{
						// here execute the process upto time_next_process
						p = *itr;
						p.time = time_next_process;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
						my_clock = time_next_process;
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here cpu will start an IO operation with lower priority
						my_clock +=cpu_time;
						p = *itr;
						p.time = time_next_process;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = 0;
						p.priority = find_lower_priority(p.priority);
						int new_time = p.phases[p.phase_no].io_time + my_clock;
						p.phase_no++;
						cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
						io_list.push(make_pair(new_time, p));
						continue;
					}
				}
				else
				{
					// here cpu will start an IO , but with lower priority
					my_clock += cpu_time;
					p = *itr;
					p.time = my_clock;
					scheduling_queue.erase(itr);
					count--;
					p.phases[p.phase_no].cpu_time = 0;
					p.priority = find_lower_priority(p.priority);
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, p));
					continue;
				}
			}
			else
			{
				// here cpu_time > time_slice, that is cpu operation will not complete in this duration
				if(time_next_process < my_clock + time_slice)
				{
					// pop from event_table and push in scheduling queue
					p = event_table.top();
					event_table.pop();
					
					p.time = time_next_process;
					scheduling_queue.push_back(p);
					count++;
										
					if(p.priority > pr)
					{
						// here execute the process upto time_next_process
						p = *itr;
						p.time = time_next_process;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
						my_clock = time_next_process;
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here cpu will schedule it again with low priority
						my_clock +=time_slice;
						p = *itr;
						p.time = my_clock;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - time_slice;
						p.priority = find_lower_priority(p.priority);

						scheduling_queue.push_back(p);					
						count++;
						continue;
					}
				}
				else
				{
					// here cpu will schedule it again
					my_clock += time_slice;
					p = *itr;
					p.time = my_clock;
					scheduling_queue.erase(itr);
					count--;
					p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - time_slice;
					p.priority = find_lower_priority(p.priority);
					count++;
					scheduling_queue.push_back(p);										
					continue;
				}
			
			}
		}
		else if(cpu_time == -1)
		{
			// so here both other will be non negative
			
			// so only io and time_next_process, 
			if(io_time < time_next_process)
			{
				my_clock = io_time;
				p = io_list.top().second;
				io_list.pop();
				
				cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<my_clock<<endl;
				
				p.time = my_clock;
				if(p.phase_no >=p.phases.size())
				{
					cout<<"Process ID:"<<p.p_id<<" finished at time "<<my_clock<<endl;
				}
				else
				{
					scheduling_queue.push_back(p);
					count++;
				}
				continue;
			}
			else
			{
				// here next process occurs earlier
				my_clock = time_next_process;
				p = event_table.top();
				event_table.pop();
				
				p.time = my_clock;
				scheduling_queue.push_back(p);
				count++;
				continue;
			
			}
			
		}
		else if(time_next_process == -1)
		{
			// here processes are in IO and scheduling queue only
			if(cpu_time < time_slice)
			{
				if(io_time < cpu_time + my_clock)
				{
					// here io will occur first
					p = io_list.top().second;
					p.time = io_list.top().first;
					io_list.pop();
					
					cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
					
					if(p.phase_no >= p.phases.size() )
					{
						cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;					
					}
					else
					{
						scheduling_queue.push_back(p);
						count++;
					}
					
					// now check whether its priority is higher than current process or not
					
					if(p.priority > pr)
					{
						// here the process which completed execution is of higher priority and therefore it should be scheduled
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (io_time - my_clock);
						my_clock = io_time;
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here IO is started
						my_clock +=cpu_time;
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = 0;
						p.priority = find_higher_priority(p.priority);
						p.time = my_clock;
						int new_time = p.phases[p.phase_no].io_time + my_clock;
						p.phase_no++;
						cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
						
						io_list.push(make_pair(new_time, p) );
						continue;
					}
				}
				else
				{
					// here process completes cpu operation first
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					my_clock += cpu_time;
					p.time = my_clock;
					p.phases[p.phase_no].cpu_time = 0;
					p.priority = find_higher_priority(p.priority);
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, p) );
					continue;
				}
			}
			else if(cpu_time == time_slice)
			{
				if(io_time < cpu_time + my_clock)
				{
					// here io will occur first
					p = io_list.top().second;
					p.time = io_list.top().first;
					io_list.pop();
					
					cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
					
					if(p.phase_no >= p.phases.size() )
					{
						cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;					
					}
					else
					{
						scheduling_queue.push_back(p);
						count++;
					}
					
					// now check whether its priority is higher than current process or not
					
					if(p.priority > pr)
					{
						// here the process which completed execution is of higher priority and therefore it should be scheduled
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (io_time - my_clock);
						my_clock = io_time;
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here IO is started
						my_clock +=cpu_time;
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time = 0;
						p.priority = find_lower_priority(p.priority);
						p.time = my_clock;
						int new_time = p.phases[p.phase_no].io_time + my_clock;
						p.phase_no++;
						cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
						
						io_list.push(make_pair(new_time, p) );
						continue;
					}
				}
				else
				{
					// here process completes cpu operation first
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					my_clock += cpu_time;
					p.time = my_clock;
					p.phases[p.phase_no].cpu_time = 0;
					p.priority = find_lower_priority(p.priority);
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, p) );
					continue;
				}			
			}
			else
			{
				// here cpu_time > time_slice
				if(io_time < my_clock + time_slice)
				{
					// here io will occur first
					p = io_list.top().second;
					p.time = io_list.top().first;
					io_list.pop();
					
					cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
					
					if(p.phase_no >=p.phases.size() )
					{
						cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;
					}
					else
					{
						scheduling_queue.push_back(p);
						count++;
					}
					
					if(p.priority >pr)
					{
						// then execute the cpu upto IO time only
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.time = io_time;
						p.phases[p.phase_no].cpu_time -= (io_time - my_clock);
						my_clock = io_time;
					
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// here execute process for full time slice
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						my_clock += time_slice;
						p.time = my_clock;
						p.priority = find_lower_priority(p.priority);
						p.phases[p.phase_no].cpu_time -= time_slice;
						
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
				}
				else
				{
					// here run process for time_slice time and then schedule it with lower priority
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					my_clock += time_slice;
					p.priority = find_lower_priority(p.priority);
					p.phases[p.phase_no].cpu_time -= time_slice;
					p.time = my_clock;
					
					scheduling_queue.push_back(p);
					count++;
					continue;
				}
			}
		}
		else
		{
			// when all are non-negative
			if(cpu_time +my_clock <= io_time && cpu_time + my_clock <= time_next_process)
			{
				// process execution finishes first
				
				if(cpu_time < time_slice)
				{
					// execute for cpu_time and then start io
					my_clock += cpu_time;
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					p.time = my_clock;
					p.priority = find_higher_priority(p.priority);
					p.phases[p.phase_no].cpu_time = 0;
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, p) );
					continue;
				}			
				else if(cpu_time == time_slice)
				{
					// execute for time_slice, decrease priority and then start io
					my_clock +=time_slice;
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					p.time = my_clock;
					p.priority = find_lower_priority(p.priority);
					p.phases[p.phase_no].cpu_time = 0;
					int new_time = p.phases[p.phase_no].io_time + my_clock;
					p.phase_no++;
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					io_list.push(make_pair(new_time, p) );
					continue;
				}
				else
				{	// execute for time_slice, decrease priority and then schedule again
					my_clock +=time_slice;
					p = *itr;
					scheduling_queue.erase(itr);
					count--;
					p.time = my_clock;
					p.priority = find_lower_priority(p.priority);
					p.phases[p.phase_no].cpu_time -= time_slice;
					
					scheduling_queue.push_back(p);
					count++;
					continue;
				}
			}
			else if(io_time <=time_next_process && io_time <=cpu_time + my_clock)
			{
				// io completes first
				if(io_time < my_clock + time_slice)
				{
					// here pop from io list and push in scheduling_queue
					
					p= io_list.top().second;
					p.time = io_list.top().first;
					io_list.pop();
					
					cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;

					if(p.phase_no >= p.phases.size() )
					{
						cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;
					}
					else
					{
						scheduling_queue.push_back(p);
						count++;
					}
					
					if(p.priority > pr)
					{
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.phases[p.phase_no].cpu_time -= (io_time - my_clock);
						my_clock = io_time;
						p.time = my_clock;
						//p.priority = find_lower_priority(p.priority);
						
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// now i have to decide amongst time_next_process and cpu_time
						if(cpu_time < time_slice)
						{
							// here cpu finishes earlier then time_slice
							if(time_next_process < cpu_time + my_clock)
							{
								// pop from event_table and push in scheduling queue
								p = event_table.top();
								event_table.pop();
					
								//my_clock = time_next_process;
								p.time = time_next_process;
								scheduling_queue.push_back(p);
								count++;
													
								if(p.priority > pr)
								{
									// here execute the process upto time_next_process
									p = *itr;
									p.time = time_next_process;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
									my_clock = time_next_process;
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here cpu will start an IO operation
									my_clock +=cpu_time;
									p = *itr;
									p.time = time_next_process;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = 0;
									p.priority = find_higher_priority(p.priority);
									int new_time = p.phases[p.phase_no].io_time + my_clock;
									p.phase_no++;
									
									cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
									io_list.push(make_pair(new_time, p));
									continue;
								}
							}
							else
							{
								// here cpu will start an IO first
								my_clock += cpu_time;
								p = *itr;
								p.time = time_next_process;
								scheduling_queue.erase(itr);
								count--;
								p.phases[p.phase_no].cpu_time = 0;
								p.priority = find_higher_priority(p.priority);
								int new_time = p.phases[p.phase_no].io_time + my_clock;
								p.phase_no++;
								cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
								io_list.push(make_pair(new_time, p));
								continue;
							}			
						}
						else if(cpu_time == time_slice)
						{
							// here also the same cases as above
							if(time_next_process < cpu_time + my_clock)
							{
								// pop from event_table and push in scheduling queue
								p = event_table.top();
								event_table.pop();
					
								//my_clock = time_next_process;
								p.time = time_next_process;
								scheduling_queue.push_back(p);
								count++;
					
								if(p.priority > pr)
								{
									// here execute the process upto time_next_process
									p = *itr;
									p.time = time_next_process;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
									my_clock = time_next_process;
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here cpu will start an IO operation with lower priority
									my_clock +=cpu_time;
									p = *itr;
									p.time = time_next_process;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = 0;
									p.priority = find_lower_priority(p.priority);
									int new_time = p.phases[p.phase_no].io_time + my_clock;
									p.phase_no++;
									
									cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
									io_list.push(make_pair(new_time, p));
									continue;
								}
							}
							else
							{
								// here cpu will start an IO , but with lower priority
								my_clock += cpu_time;
								p = *itr;
								p.time = my_clock;
								scheduling_queue.erase(itr);
								count--;
								p.phases[p.phase_no].cpu_time = 0;
								p.priority = find_lower_priority(p.priority);
								int new_time = p.phases[p.phase_no].io_time + my_clock;
								p.phase_no++;
					
								io_list.push(make_pair(new_time, p));
								continue;
							}
						}
						else
						{
							// here cpu_time > time_slice, that is cpu operation will not complete in this duration
							if(time_next_process < my_clock + time_slice)
							{
								// pop from event_table and push in scheduling queue
								p = event_table.top();
								event_table.pop();
					
								p.time = time_next_process;
								scheduling_queue.push_back(p);
								count++;
					
								if(p.priority > pr)
								{
									// here execute the process upto time_next_process
									p = *itr;
									p.time = time_next_process;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (time_next_process - my_clock);
									my_clock = time_next_process;
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here cpu will schedule it again with low priority
									my_clock +=time_slice;
									p = *itr;
									p.time = my_clock;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - time_slice;
									p.priority = find_lower_priority(p.priority);

									scheduling_queue.push_back(p);					
									count++;
									continue;
								}
							}
							else
							{
								// here cpu will schedule it again
								my_clock += time_slice;
								p = *itr;
								p.time = my_clock;
								scheduling_queue.erase(itr);
								count--;
								p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - time_slice;
								p.priority = find_lower_priority(p.priority);
								scheduling_queue.push_back(p);						
								count++;				
								continue;
							}
						}
					}					
				}
				else
				{
					// here io_time >= my_clock +time_slice
					
					// so execute the process and schedule it again but with decrease priority 
				
					p = *itr;
					my_clock += time_slice;
					scheduling_queue.erase(itr);
					count--;
					p.time = my_clock;
					p.priority = find_lower_priority(p.priority);
					p.phases[p.phase_no].cpu_time -= time_slice;
					
					scheduling_queue.push_back(p);
					count++;
					continue;
				}
			}
			else
			{
				// here time_next_process is the minimum
				if(time_next_process < my_clock + time_slice)
				{
					// so pop from event_table and push in scheduling queue
					p = event_table.top();
					event_table.pop();
					p.time = time_next_process;
					scheduling_queue.push_back(p);
					count++;
					
					if(p.priority > pr)
					{
						p = *itr;
						scheduling_queue.erase(itr);
						count--;
						p.time = time_next_process;
						p.phases[p.phase_no].cpu_time -= (time_next_process - my_clock);
						my_clock = time_next_process;
						
						scheduling_queue.push_back(p);
						count++;
						continue;
					}
					else
					{
						// have to choose between io and running process now
						if(cpu_time < time_slice)
						{
							if(io_time < cpu_time + my_clock)
							{
								// here io will occur first
								p = io_list.top().second;
								p.time = io_list.top().first;
								io_list.pop();
				
								cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
				
								if(p.phase_no >= p.phases.size() )
								{
									cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;					
								}
								else
								{
									scheduling_queue.push_back(p);
									count++;
								}
				
								// now check whether its priority is higher than current process or not
				
								if(p.priority > pr)
								{
									// here the process which completed execution is of higher priority and therefore it should be scheduled
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (io_time - my_clock);
									my_clock = io_time;
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here IO is started
									my_clock +=cpu_time;
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = 0;
									p.priority = find_higher_priority(p.priority);
									p.time = my_clock;
									int new_time = p.phases[p.phase_no].io_time + my_clock;
									p.phase_no++;
									cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
					
									io_list.push(make_pair(new_time, p) );
									continue;
								}
							}
							else
							{
								// here process completes cpu operation first
								p = *itr;
								scheduling_queue.erase(itr);
								count--;
								my_clock += cpu_time;
								p.time = my_clock;
								p.phases[p.phase_no].cpu_time = 0;
								p.priority = find_higher_priority(p.priority);
								int new_time = p.phases[p.phase_no].io_time + my_clock;
								p.phase_no++;
				
								cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
								io_list.push(make_pair(new_time, p) );
								continue;
							}
						}
						else if(cpu_time == time_slice)
						{
							if(io_time < cpu_time + my_clock)
							{
								// here io will occur first
								p = io_list.top().second;
								p.time = io_list.top().first;
								io_list.pop();
					
								cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
					
								if(p.phase_no >= p.phases.size() )
								{
									cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;					
								}
								else
								{
									scheduling_queue.push_back(p);
									count++;
								}
					
								// now check whether its priority is higher than current process or not
					
								if(p.priority > pr)
								{
									// here the process which completed execution is of higher priority and therefore it should be scheduled
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = p.phases[p.phase_no].cpu_time - (io_time - my_clock);
									my_clock = io_time;
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here IO is started
									my_clock +=cpu_time;
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									p.phases[p.phase_no].cpu_time = 0;
									p.priority = find_lower_priority(p.priority);
									p.time = my_clock;
									int new_time = p.phases[p.phase_no].io_time + my_clock;
									p.phase_no++;
									cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
						
									io_list.push(make_pair(new_time, p) );
									continue;
								}
							}
							else
							{
								// here process completes cpu operation first
								p = *itr;
								scheduling_queue.erase(itr);
								count--;
								my_clock += cpu_time;
								p.time = my_clock;
								p.phases[p.phase_no].cpu_time = 0;
								p.priority = find_lower_priority(p.priority);
								int new_time = p.phases[p.phase_no].io_time + my_clock;
								p.phase_no++;
					
								cout<<"Process ID:"<<p.p_id<<" completed cpu at time "<<my_clock<<endl;
								io_list.push(make_pair(new_time, p) );
								continue;
							}			
						}
						else
						{
							// here cpu_time > time_slice
							if(io_time < my_clock + time_slice)
							{
								// here io will occur first
								p = io_list.top().second;
								p.time = io_list.top().first;
								io_list.pop();
					
								cout<<"Process ID:"<<p.p_id<<" completed IO at time "<<p.time<<endl;
					
								if(p.phase_no >=p.phases.size() )
								{
									cout<<"Process ID:"<<p.p_id<<" finished at time "<<p.time<<endl;
								}
								else
								{
									scheduling_queue.push_back(p);
									count++;
								}
					
								if(p.priority >pr)
								{
									// then execute the cpu upto IO time only
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									p.time = io_time;
									p.phases[p.phase_no].cpu_time -= (io_time - my_clock);
									my_clock = io_time;
					
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
								else
								{
									// here execute process for full time slice
									p = *itr;
									scheduling_queue.erase(itr);
									count--;
									my_clock += time_slice;
									p.time = my_clock;
									p.priority = find_lower_priority(p.priority);
									p.phases[p.phase_no].cpu_time -= time_slice;
						
									scheduling_queue.push_back(p);
									count++;
									continue;
								}
							}
							else
							{
								// here run process for time_slice time and then schedule it with lower priority
								p = *itr;
								scheduling_queue.erase(itr);
								count--;
								my_clock += time_slice;
								p.priority = find_lower_priority(p.priority);
								p.phases[p.phase_no].cpu_time -= time_slice;
								p.time = my_clock;
					
								scheduling_queue.push_back(p);
								count++;
								continue;
							}
						}
					}
				}
				else
				{
					// here time_next_process is min and it is itself >=cpu_time + my_clock
					
					// process will run for time_slice and then rescheduled again with low priority
					my_clock += time_slice;
					p =*itr;
					scheduling_queue.erase(itr);
					count--;
					p.time = my_clock;
					p.priority = find_lower_priority(p.priority);
					p.phases[p.phase_no].cpu_time -= time_slice;
					
					scheduling_queue.push_back(p);
					count++;
					continue;
				}
			}		
		}
	}
}

int find_time_slice(int pr)
{
	if(my_scheduler.no_levels == 0)
	{
		return 100000;
	}

	for(int i =0;i<my_scheduler.levels.size();i++)
	{
		if(my_scheduler.levels[i].priority == pr)
		{
			return my_scheduler.levels[i].time_slice;
		}
	}
	return 0;
}

int find_higher_priority(int curr)
{
	// if the no of levels are 0, then what should be done, then these functions should return current priority
	if(my_scheduler.no_levels == 0)
	{
		return curr;
	}
	for(int i =0;i<my_scheduler.levels.size() - 1;i++)
	{
		if(my_scheduler.levels[i+1].priority == curr)	// if priority at (i+1)th level = passsed priority, then send the priority at ith level
		{
			return my_scheduler.levels[i].priority;
		}
	}
	return curr;
}

int find_lower_priority(int curr)
{
	if(my_scheduler.no_levels == 0)
	{
		return curr;
	}

	for(int i =0;i<my_scheduler.levels.size() - 1;i++)
	{
		if(my_scheduler.levels[i].priority == curr)		// if current priority = this priority, then send next lower priority
		{
			return my_scheduler.levels[i+1].priority;
		}
	}
	return curr;
}


//for event_table
bool operator < (const process & p1, const process & p2)
{
	return (p1.admission > p2.admission); 
}

bool operator < (const pair<int, process> & p1, const pair<int, process> & p2)
{
	return (p1.first > p2.first); 
}

