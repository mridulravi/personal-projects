#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <utility>
#include <queue>
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
	int phase_no;
	int time;
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
			proc.phase_no = 0;
			proc.time = 0;

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

int my_clock;
priority_queue<process> event_table;
void scheduler_time_sharing();


int main(){
	process_proc_file();
	//cout<<(process_list[1].phases[1]).io_time<<endl;
	process_scheduler_file();
	//cout<<my_scheduler.levels[1].time_slice<<endl;
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
	for(int i= 0;i<process_list.size();i++)
	{
		event_table.push(process_list[i]);
	}
	
	scheduler_time_sharing();

//	int i =100000;
//	cout<<i<<endl;
	return 0;
}

void scheduler_time_sharing()
{
	priority_queue< pair<int, process> > io_list;
	queue<process> scheduling_queue;

	if(event_table.empty() )
	{
		cout<<"Event table should not be empty\n";
		exit(1);
	}
	
	// add the first process in the pcb list from the event_table
	process p = event_table.top();
	event_table.pop();
	scheduling_queue.push(p);
	my_clock = p.admission;
	
	int time_slice = my_scheduler.levels[0].time_slice;
	
	while(!event_table.empty() || !scheduling_queue.empty() || !io_list.empty() )
	{
		// set all these 3 to very large values and then process on the minimum amongst them, if the min is not from io or from event, then add it to the queue and execute it till min of time_slice or its termination time
		int time = my_clock+time_slice;
		int time_next_process = -1, cpu_time = -1, io_time = -1;
		if(!event_table.empty() )
		{
			time_next_process = event_table.top().admission;
		}
		if(!scheduling_queue.empty() )
		{
			cpu_time = scheduling_queue.front().phases[scheduling_queue.front().phase_no].cpu_time;
		}
		if(!io_list.empty() )
		{
			io_time = io_list.top().first;
		}

		if(time_next_process == -1 && io_time == -1)
		{
			// execute the process in front of the queue for its time
			p = scheduling_queue.front();
			scheduling_queue.pop();
			
			// now check whether it will run for the whole time or not
			if(cpu_time <time_slice)
			{
				// it will finish in this time
				my_clock +=cpu_time;		
				p.time = my_clock;
				p.phases[p.phase_no].cpu_time = 0;	
				cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
				int new_time = p.phases[p.phase_no].io_time + my_clock;
				p.phase_no++;
				// schedule it for IO
				io_list.push(make_pair(new_time, p) );
				continue;
			}		
			else
			{
				p.time = time;
				p.phases[p.phase_no].cpu_time = cpu_time - (time - my_clock);
				my_clock = time;
				// push back in scheduling queue
				scheduling_queue.push(p);
				continue;
			}
		}
		else if(cpu_time == -1 && io_time == -1)
		{
			// pop from event_table and push in scheduling queue		
			p = event_table.top();
			event_table.pop();
			my_clock = p.admission;
			p.time = p.admission;
			scheduling_queue.push(p);
			continue;
		}
		else if(cpu_time == -1 && time_next_process == -1)
		{
			// io 
			p = io_list.top().second;
			my_clock = io_list.top().first;
			io_list.pop();
			
			cout<<"Process Id:"<<p.p_id<<" completed I/O at "<<my_clock<<endl;
			
			if(p.phase_no >=p.phases.size())
			{
				cout<<"Process Id:"<<p.p_id<<" finished at "<<my_clock<<endl;
			}
			else
			{
				p.time = my_clock;
				scheduling_queue.push(p);
			}
			continue;
		}
		else if(io_time == -1)
		{
			// here there are no IO 
			if(time_next_process < time)
			{
				if(time_next_process < cpu_time + my_clock)
				{
					// push it in queue 
					p = event_table.top();
					event_table.pop();
					scheduling_queue.push(p);
					
					if(cpu_time + my_clock <=time)
					{
						// it finishes before end of time_slice, and schedules an IO
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = 0;
						
						cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
						int new_time = p.time + p.phases[p.phase_no].io_time;
						p.phase_no++;
						my_clock +=cpu_time;
						io_list.push(make_pair(new_time, p) );
						continue;
					}
					else
					{
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = time;
						p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
						my_clock = time;
						scheduling_queue.push(p);
						continue;					
					}
					my_clock = time_next_process;
					continue;
				}
				else
				{
					// here CPU finishes first and schedules an IO 
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;
					
					cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock = p.time;
					io_list.push(make_pair(new_time, p));
					continue;
					
/*					// now pop from event_table and push in queue
					p = event_table.top();
					event_table.pop();
					scheduling_queue.push(p);
					my_clock = time_next_process;
					continue;
*/
				}
			}
			else
			{
				// here time_next_process >= time, 
				if(cpu_time <= time_slice)
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;
					
					cout<<"Process Id:"<<p.p_id<<" completed io at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock +=cpu_time;
					io_list.push(make_pair(new_time, p));
					continue;				
				
				}
				else
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
					my_clock = time;
					scheduling_queue.push(p);
					continue;
				}
			}
		}		
		else if(cpu_time == -1)
		{
			// here there are IO and event_table
			if(io_time <= time_next_process)
			{
				// here pop from io_list and push in queue
				p = io_list.top().second;
				my_clock = io_time;
				io_list.pop();
				p.time = io_time;
				
				cout<<"Process Id:"<<p.p_id<<" completed IO at time "<<io_time<<endl;
				
				if(p.phase_no >= p.phases.size() )
				{
					cout<<"Process Id:"<<p.p_id<<" finished at time "<<io_time<<endl;
				}
				else
				{
					scheduling_queue.push(p);
				}
				continue;
			}
			else
			{
				// here pop from event_table and push in scheduling queue
				p = event_table.top();
				event_table.pop();
				
				p.time = time_next_process;
				my_clock = time_next_process;
				scheduling_queue.push(p);
				continue;
			}
		}
		else if(time_next_process == -1)
		{
			if(io_time <=time)
			{
				if(io_time <= cpu_time + my_clock)
				{
					// here first schedule IO
					p = io_list.top().second;
					io_list.pop();
					cout<<"Process Id:"<<p.p_id<<" completed IO at time "<<io_time<<endl;
				
					if(p.phase_no >= p.phases.size() )
					{
						cout<<"Process Id:"<<p.p_id<<" finished at time "<<io_time<<endl;
					}
					else
					{
						scheduling_queue.push(p);
					}
					
					if(cpu_time + my_clock <= time)
					{
						// here execute in the cpu and then schedule an IO
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = 0;
					
						cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
						int new_time = p.time + p.phases[p.phase_no].io_time;
						p.phase_no++;
						my_clock = p.time;
						io_list.push(make_pair(new_time, p));
						continue;
					}
					else
					{
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = time;
						p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
						my_clock = time;
						scheduling_queue.push(p);
						continue;
					}
				}
				else
				{
					// here cpu finishes first ans schedules an IO
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;
			
					cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock = p.time;
					io_list.push(make_pair(new_time, p));
					continue;
				}
			}
			else
			{
				// no IO in this time period, only check for CPU
				if(cpu_time <= time_slice)
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;
					
					cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock +=cpu_time;
					io_list.push(make_pair(new_time, p));
					continue;				
				
				}
				else
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
					my_clock = time;
					scheduling_queue.push(p);
					continue;
				}
			
			}
		
		}
		else
		{
			// when all are non-negative
			if(cpu_time+my_clock <= time_next_process && cpu_time+my_clock <= io_time)
			{
				// here we will execute process on cpu first
				if(cpu_time <=time_slice)
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;
					
					cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock +=cpu_time;
					io_list.push(make_pair(new_time, p));
					continue;
				
				}
				else
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
					my_clock = time;
					scheduling_queue.push(p);
					continue;
				}
			}
			else if(time_next_process<=time)
			{	
				// here we will have to execute this also in this process
				if(io_time <= time_next_process)
				{
					// here first io occurs and then pop from event_table
					if(cpu_time+my_clock <= io_time)
					{
						// here execute process on CPU first, process will start an IO
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = 0;
					
						cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
						int new_time = p.time + p.phases[p.phase_no].io_time;
						p.phase_no++;
						my_clock +=cpu_time;
						io_list.push(make_pair(new_time, p));
						continue;
					}
					else
					{
						// here io occurs first and then cpu
						p = io_list.top().second;
						io_list.pop();
						p.time = io_time;						
						cout<<"Process Id:"<<p.p_id<<" completed IO at time "<<io_time<<endl;
				
						if(p.phase_no >= p.phases.size() )
						{
							cout<<"Process Id:"<<p.p_id<<" finished at time "<<io_time<<endl;
						}
						else
						{
							scheduling_queue.push(p);
						}
												
						if(time_next_process <= cpu_time + my_clock)
						{
							// now pop from event_table
							p = event_table.top();
							event_table.pop(); 
							p.time = p.admission;
							scheduling_queue.push(p);
							
							if(cpu_time<=time_slice)
							{
								p = scheduling_queue.front();
								scheduling_queue.pop();
								p.time = my_clock + cpu_time;
								p.phases[p.phase_no].cpu_time = 0;
				
								cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
								int new_time = p.time + p.phases[p.phase_no].io_time;
								p.phase_no++;
								my_clock +=cpu_time;
								io_list.push(make_pair(new_time, p));
								continue;
							}
							else
							{
								p = scheduling_queue.front();
								scheduling_queue.pop();
								p.time = my_clock + cpu_time;
								p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
								my_clock = time;
								scheduling_queue.push(p);
								continue;	
							}
						}
						else
						{
							// here cpu occurs earlier
							p = scheduling_queue.front();
							scheduling_queue.pop();
							p.time = my_clock + cpu_time;
							p.phases[p.phase_no].cpu_time = 0;
			
							cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
							int new_time = p.time + p.phases[p.phase_no].io_time;
							p.phase_no++;
							my_clock +=cpu_time;
							io_list.push(make_pair(new_time, p));
							continue;
						}
					}				
				}
				/*else if(io_time <= time)
				{
					// here first event table then
					if(cpu_time + my_clock <=io_time)
					{
					
					}
				
				}*/
				else
				{
					// here pop from event_table occurs first and then check for IO 
					if(time_next_process <= cpu_time + my_clock)
					{
						// now pop from event_table
						p = event_table.top();
						event_table.pop(); 
						p.time = p.admission;
						scheduling_queue.push(p);
						
						//now check for IO
						if(io_time <= time)
						{
							if(cpu_time + my_clock < io_time)
							{
								// here process excution ends earlier
								p = scheduling_queue.front();
								scheduling_queue.pop();
								p.time = my_clock + cpu_time;
								p.phases[p.phase_no].cpu_time = 0;
			
								cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
								int new_time = p.time + p.phases[p.phase_no].io_time;
								p.phase_no++;
								my_clock +=cpu_time;
								io_list.push(make_pair(new_time, p));
								continue;
							}
							else
							{
								// here io first, 
								p = io_list.top().second;
								io_list.pop();
								cout<<"Process Id:"<<p.p_id<<" completed IO at time "<<io_time<<endl;
				
								if(p.phase_no >= p.phases.size() )
								{
									cout<<"Process Id:"<<p.p_id<<" finished at time "<<io_time<<endl;
								}
								else
								{
									scheduling_queue.push(p);
								}
								
								if(cpu_time<=time_slice)
								{
									p = scheduling_queue.front();
									scheduling_queue.pop();
									p.time = my_clock + cpu_time;
									p.phases[p.phase_no].cpu_time = 0;
				
									cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
									int new_time = p.time + p.phases[p.phase_no].io_time;
									p.phase_no++;
									my_clock +=cpu_time;
									io_list.push(make_pair(new_time, p));
									continue;
								}
								else
								{
									p = scheduling_queue.front();
									scheduling_queue.pop();
									p.time = my_clock + cpu_time;
									p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
									my_clock = time;
									scheduling_queue.push(p);
									continue;	
								}
								
								
							}
						}
						else
						{
							// here cpu happens 
							if(cpu_time<=time_slice)
							{
								p = scheduling_queue.front();
								scheduling_queue.pop();
								p.time = my_clock + cpu_time;
								p.phases[p.phase_no].cpu_time = 0;
			
								cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
								int new_time = p.time + p.phases[p.phase_no].io_time;
								p.phase_no++;
								my_clock +=cpu_time;
								io_list.push(make_pair(new_time, p));
								continue;
							}
							else
							{
								p = scheduling_queue.front();
								scheduling_queue.pop();
								p.time = my_clock + cpu_time;
								p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
								my_clock = time;
								scheduling_queue.push(p);
								continue;	
							}
						}
					}
					else
					{
						// here cpu occurs and schedules an IO
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = 0;
	
						cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
						int new_time = p.time + p.phases[p.phase_no].io_time;
						p.phase_no++;
						my_clock +=cpu_time;
						io_list.push(make_pair(new_time, p));
						continue;
					}
				}
			}
			else if(io_time <= time)
			{
				//here the case that time_next_process is already handled earlier
				if(cpu_time+my_clock <= io_time)
				{
					p = scheduling_queue.front();
					scheduling_queue.pop();
					p.time = my_clock + cpu_time;
					p.phases[p.phase_no].cpu_time = 0;

					cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
					int new_time = p.time + p.phases[p.phase_no].io_time;
					p.phase_no++;
					my_clock +=cpu_time;
					io_list.push(make_pair(new_time, p));
					continue;
				}
				else 
				{
					p = io_list.top().second;
					io_list.pop();
					p.time = io_time;
					my_clock = io_time;
					
					cout<<"Process Id:"<<p.p_id<<" completed IO at time "<<io_time<<endl;
					
					if(p.phase_no >= p.phases.size())
					{
						cout<<"Process Id:"<<p.p_id<<" finished at time "<<io_time<<endl;
					}
					else
					{
						scheduling_queue.push(p);
					}
					
					if(cpu_time<=time_slice)
					{
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = 0;

						cout<<"Process Id:"<<p.p_id<<" completed cpu at time "<<p.time<<endl;
						int new_time = p.time + p.phases[p.phase_no].io_time;
						p.phase_no++;
						my_clock +=cpu_time;
						io_list.push(make_pair(new_time, p));
						continue;
					}
					else
					{
						p = scheduling_queue.front();
						scheduling_queue.pop();
						p.time = my_clock + cpu_time;
						p.phases[p.phase_no].cpu_time = cpu_time - time_slice;
						my_clock = time;
						scheduling_queue.push(p);
						continue;	
					}
				}
			}
		}
	}
}

//for event
bool operator < (const process & p1, const process & p2)
{
	return (p1.admission > p2.admission); 
}

bool operator < (const pair<int, process> & p1, const pair<int, process> & p2)
{
	return (p1.first > p2.first); 
}

