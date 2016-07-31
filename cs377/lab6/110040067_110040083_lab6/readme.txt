Abhishek Gupta		110040067
Mridul Ravi Jain	110040083
###############################################################################################################

This is our 2nd submission(late submission) for Assignment6.
We have changed 3(d) part. and 5(a) part.
We have added answer for 5(b) part
3(b) part is same as in 1st submission but we have just explained it clearly in this submission
################################################################################################################
1.
In file: guestos.c

There is call to function boot().

void boot(void) {
	install_signals();
	set_defaults();
}

Boot makes call to two other functions which read the parameters from .config file and assign the signal handlers.

void set_defaults(void) {
	char param_value[LINE_MAX+1];
	get_param("INSTR_SLICE", param_value);
	instr_slice = atoi(param_value);

	int heads, tracks, sectors;
	char command[1000];
	get_param("NUM_HEADS",param_value);
	heads=atoi(param_value);
	get_param("NUM_TRACKS",param_value);
	tracks=atoi(param_value);
	get_param("NUM_SECTORS",param_value);
	sectors=atoi(param_value);
	sprintf(command,"(dd if=/dev/zero of=Sim_disk bs=%dx%dx%db count=1) 2> /dev/zero",heads,tracks,sectors);
	system(command);
}

void install_signals(void){
	signal(SIGINT, &sim_signal_handler);
    	signal(SIGABRT, &sim_signal_handler);
    	signal(SIGFPE, &sim_signal_handler);
    	signal(SIGUSR2, &sim_signal_handler);
}


###############################################################################################################

2. 
We manually edited the file .config

		INSTR_SLICE=20
		NUM_HEADS=2
		NUM_TRACKS=80
		NUM_SECTORS=18


We changed the INSTR_SLICE to 20.


###############################################################################################################

3.
(a) The function syscall_do() is called when the opcode of decoded instruction is same as op_int_imm8. 
This function is equivalent to generic syscall handler of host OS. In this way the sycall handler is invoked.

(b) Guest OS implements 1 system call at present. It passes control to host OS for 80 system calls. The syscall whose syscode is <= 325(80 such syscalls) are passed to host OS, whereas syscalls whose syscode is >=400 are handled by Guest Os(1 such predefined syscall) 

(c) syscall_do function is defined in sycall.c file. The syscode is passed via eax register. 
If the syscode is greater than 325, then the guest OS(i.e. Pranjali) handles it, otherwise it is passed 
to the Host OS. This function further has switch call whose each case acts as syscall specific handler.

(d) System call handler uses mem_read() or mem_write() to read or write respectively in the user address space of the process. mem_read() and mem_write() in turn uses the mem_access() function.

mem_access() is responsible for accessing user pages for either reading or writing or executing. These operation mode is specified as a parameter for mem_access(). This parameter’s value may either be one of the following: mem_access_read, mem_access_write, mem_access_exec.
To read or write user space buffers mem_read(), mem_write() macros are used. These macros are ultimatley expanded to call the mem_access() function with either mem access read or mem access write parameter in it.

mem_access() is declared as:
	void mem_access(struct mem_t *mem, uint32_t addr, int size, void *buf, enum mem_access_enum access)

mem points to the memory page table of current process. addr is the address of the buffer in the user space whose contents are to be accessed. buf is the buffer in the kernel space where the accessed contents are written or read from depending on whether mem access() is called to read or write the user space contents, size specifies size of buf, access parameter specifies the mode of mem access(), whether its being used for read or write.

###############################################################################################################

4.
(a) The source code file Context.c is mainly used for creating contexts of processes. 
It contains many things about a process including its loader, signal handler list, segment bases, 
segment limits ,memory details, file descriptor table ,etc. 

We can therefore access the PCB of all process by iterating over the linked list "ke->context_list_head" 
using the context_next  pointer and finding out the details such as GPRs using: "ke->context_list_head->regs"

(b) In file guestos.c : instr_slice

(c) The scheduler of any OS decides which process to schedule at given instant of time. For
this purpose, scheduler can use its own scheduling policy.
The guest OS multiplexes operation of user processes on an n-instructions-
at-a-time basis. The guest OS executes one-by-one instruction from each user process 
i.e. in round-robin way. So instead of being timing driven, Guest OS is instruction count driven.

If it was a multiprocessor OS, cpu should also be selected for the next instruction which is done as follws 
after each instr_slice:
 Select the cpu identifier that best fits to the context with the following priority:
  1) If the cpu where the context was allocated before is free, select it.
  2) If there is any cpu that has not been used yet, select it.
  3) If there is any free cpu, select it.

###############################################################################################################

Note: Compile the c files with -m32 and -static flag, also use gcc-4.4.3 for compiling

5.
(a) We added a system call set_instruction_slice whose syscall code is 401. It accepts one parameter which is an integer which will be the new instruction slice for the process. Basicaly we modify the instr_slice variable of the context of that process.
We also modified the ke->run() function in m2skernel.c. We commeneted out some portion of it and added some new portion. Basically we added a check which will check the status of each process before executing the instruction. If the status is "finished", then we will not try to execute the instruction.
The code portion added is 
	if(ctx_get_status(ctx, ctx_finished) )		// if context finished, then does not execute the instruction
	{
		break;
	}

Testing:-
	We have made 4 c files - test1.c, test2.c, test3.c, test4.c
	All these are doing the same computation and differ only in the value passed to set_instruction_slice syscall.
	test1.c passes 10, test2.c passes 233, tets3.c passes 613, test4.c passes 1000 as parameter to set_instruction_slice syscall
	
	Hence test4 finishes first followed by test3, then test2 and finally test1 (independent of the order in which you enter them for scheduling)


5.
(b) We added 2 system calls. 
read_virtual_disk systrem call has syscode 402 and accepts as parameters:-
	no_of_bytes_to_be_read, address_of_memory_in_process_address_space, disk_block_no, offset_in_disk_block	

write_virtual_disk systrem call has syscode 403 and accepts as parameters:-
	no_of_bytes_to_be_written, address_of_memory_in_process_address_space, disk_block_no, offset_in_disk_block	

We have also added the syscalls in syscall.dat file

We have also added the protection check, which ensures that no process can read or write at same blocks which have been written by some other user.


Testing:-
	protection1.c and protection2.c, both of these include temp.h. Both these write in same block in file
	
	If you run them with the same user id, then the operations will proceed normally, but if you run them with different user_id, then an error will be thrown stating that 1 user cannot access blocks modified by some other user
