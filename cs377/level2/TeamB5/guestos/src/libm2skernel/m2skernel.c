/*
 *  Multi2Sim
 *  Copyright (C) 2007  Rafael Ubal Tena (raurte@gap.upv.es)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <m2skernel.h>
#include <math.h>
#define INSTRUCTION_JUMPS 20
/* Global Multi2Sim
 * Kernel Variable */
struct kernel_t *ke;

/////////////////////////////////////////////////
instruction_jump(int block, int byte){
	int track = block/num_sectors;				// calculating the track no
	if(block % num_sectors !=0)
	{
		track++;
	}
	
	// now find the head which is closest to it
	int i=0;
	int min = num_tracks;
	int min_pos=0;
	for (i=0;i<num_heads;i++){
		if (abs(head_pos[i]-track) < min) {
			min_pos = i;
			min = abs(head_pos[i]-track);
		}
	}
	
	int temp = byte/(512*num_sectors);
	min += temp;
	head_pos[min_pos] = track+temp;
	
	return min*INSTRUCTION_JUMPS + (byte*2);
		
}

///////////////////////////////////////////////
/* Initialization */

void insert_fcb(struct oft * fcb)
{
	if(tail_oft)
	{
		// if tail_oft is non-null
		tail_oft->next = fcb;
		fcb->next = NULL;
		fcb->prev = tail_oft;
		tail_oft = fcb;
	}
	else
	{
		// if tail_oft is NULL
		head_oft = tail_oft = fcb;
		fcb->next = fcb->prev = NULL;
	}
}

int calculate_fd()
{
	int max = 0, size = 0;
	int min;
	struct oft * i = head_oft;
	if(!head_oft)
	{
		return 0;	
	}
	min = head_oft->file_descriptor;
	for(;i;i = i->next)
	{
		size++;
		if(max<i->file_descriptor)
		{
			max = i->file_descriptor;
		}
	}
	
	// now i know the size
	int * fd_array = (int *) malloc(sizeof(int) * size);
	int j;
	for(j = 0;j<max;j++)
	{
		fd_array[j] = 0;	
	}

	i = head_oft;	
	for(;i;i = i->next)
	{
		fd_array[i->file_descriptor] = 1;
	}
	
	for(j = 0;j<max;j++)
	{
		if(fd_array[j] == 0)
		{
			free(fd_array);
			return j;			
		}
	}
	free(fd_array);
	return max+1;
}

void delete_fcb(int fd)
{
	struct oft * i = head_oft;
	for(;i;i = i->next)
	{
		if(i->file_descriptor == fd)
		{
			// remove this from the list
			if(i->prev)
			{
				// i is not head
				
				// if i is tail
				if(tail_oft == i)
				{	
					tail_oft == i->prev;
					tail_oft->next = NULL;
				}
				else
				{	// if i is not tail
					i->prev->next = i->next;
					i->next->prev = i->prev;
				}
				
				
			}
			else
			{
				// i is head
				
				// if i is tail
				if(tail_oft == i)
				{
					head_oft = tail_oft = NULL;
				}
				else
				{
					// if i is not tail_oft
					head_oft = head_oft->next;
					head_oft->prev = NULL;
				}
			}
		}
	}
}

struct oft * return_fcb(int fd)
{
	struct oft * i = head_oft;
	for(;i;i=i->next)
	{
		if(i->file_descriptor == fd)
		{
			return i;
		}
	}
	return NULL;
	
}

///////////////////////////////////////////////////////

void schedule_interrupt_insert(schedule_interrupt* st) {
    schedule_interrupt* temp=headio;
    if(temp!=NULL) {
        while(temp->next!=NULL) {
            if(temp->inst_num<=st->inst_num) {
                temp=temp->next;
            }
            else {
                temp=temp->prev;
                st->next=temp->next;
                temp->next=st;
                st->next->prev=st;
                st->prev=temp;
                return;
            }
        }
    }
    else {
        headio=st;
        tailio=st;
        st->next=NULL;
        st->prev=NULL;
        return;
    }
    if(temp==tailio) {
        tailio->next=st;
        st->next=NULL;
        st->prev=tailio;
        tailio=st;
    }
}


void schedule_interrupt_remove() {
    if(headio!=NULL) {
    	struct schedule_interrupt * temp = headio;
        headio=headio->next;
        free(temp);
       	if(headio!=NULL)
       	{
	        headio->prev=NULL;
        }
    }
}

schedule_interrupt* schedule_interrupt_return() {
    return headio;
}

/////////////////////////////////////////////////////////////////////

char * get_current_time()
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	
	timeinfo = localtime(&rawtime);
	char * buf = (char *)malloc(sizeof(char) * 15);
	strftime(buf, 15, "%d%m%Y%H%M%S", timeinfo);
/*	printf("In get_current_time: %s\n",buf);*/
	int i =0;
/*	for(i =0;i<15;i++)*/
/*	{*/
/*		printf("%d-%c	",i, buf[i]);*/
/*	}*/
	printf("\n");
	
/*	buf[15] = '\0';*/
	return buf; 
}

int update_dsm(int block_num, FILE* fp, int stat)
{
	int offset = 15 + block_num;
	char status[1];
	if(stat)
	{
		status[0] = '1'; // busy
	}
	else
	{
		status[0] = '0'; // free
	}	
	fseek(fp, offset, SEEK_SET);
	int bytes_written = fwrite(status, 1, 1, fp);
	if(bytes_written != 1)
		return -1;
	return 0;	
}

// This function calculates the last_part of input
// input: A/B/C returns C 
char* get_last_part_of_address(char* addr) 
{
    char c[1000];
    strcpy(c, addr);
    char* ans;
    char * tok = strtok(c, "/");
    while (tok != NULL)
    {
        ans = tok;
        tok = strtok(NULL, "/");
    }
    char *dest = (char *)malloc(sizeof(char) * 1000);
    bzero(dest, 1000);
    strcat(dest, ans);
   return dest;
}

char* convert_to_absolute_address(char* addr) {
// have to define curr_dir here
	char curr_dir[1000];
	int i =0;
	for(;i<num_processes;i++)
	{
		if(curr_dir_array[i].process_id == isa_ctx->pid)
		{
/*			curr_dir = curr_dir_array[i].pathname;*/
			strcpy(curr_dir, curr_dir_array[i].pathname);
			break;
		}
	}

	char c[1000];
	strcpy(c, addr);
	
	// Input can be absoulte
	if(c[0] == '~')
	{
		return addr;
	}
	
	// Single dot = curr_dir
	if(c[0] == '.' && strlen(c)==1)
	{
		return curr_dir;
	}
	else if(c[0] == '.' && c[1] == '/' && strlen(c)==2)
	{
		return curr_dir;
	}
	else if(c[0] == '.' && c[1] == '/')
	{
		char new[1000];
		int i;
		for(i=0;i<strlen(c)-2;i++){
			new[i]=c[i+2];
		}
						
		new[i] = 0; 
		char * new_str = new;
		return convert_to_absolute_address(new_str);
	}
	else
	{
	
		// No of ".." in relative_address is the no. of times we have to level_up 
		int level_up = 0;				
		char *tok = strtok(c, "/");
		char* dot_dot="..";
		while (tok != NULL)
		{
			if(strcmp(tok, dot_dot) == 0)
				level_up++ ;
			tok = strtok(NULL, "/");
		}

		// Calculate the depth of our curr_dir : ~/user/a  means  depth 4  
		strcpy(c, curr_dir);
		int depth = 1;
		tok = strtok(c, "/");
		while (tok != NULL)
		{
			depth++;
			tok = strtok(NULL, "/");
		}

			// NULL if invalid
			if(depth - level_up <= 1)
		{
			return NULL;
		}

		// Now we start to form the absolute_address by first going level_up upwards
		char *dest = (char *)malloc(sizeof(char)*1000);
		strcpy(dest,"");
		strcpy(c, curr_dir);
		int up = depth - level_up;
		tok = strtok(c, "/");
		while (up != 1)
		{
			strcat(dest, tok);
			strcat(dest, "/");
			up--;
			tok = strtok(NULL, "/");
		}

		// Finally we go downwards in the directory tree
		strcpy(c, addr);
		tok = strtok(c, "/");
		while (tok != NULL)
		{
			if(strcmp(tok, dot_dot) != 0) 
			{
				strcat(dest, tok);
				strcat(dest, "/");
			}
			tok = strtok(NULL, "/");
		}
		
		dest[strlen(dest)-1] = '\0'; 
		char * new_str = dest;
		return new_str;
    }
}

//traverse the path and check that user has w permissions on all but the last, return block no of metadata of second last (dir). return -1 if permissions not there, or if path not exist
// so if A/B/C given than 
int check_permissions_on_path(char* abs_path)
{
/*	printf("**************In check_permissions_on_path1.0, abs_path is %s\n", abs_path);*/
	// start from the root
	
	// check whether you have write permission
	// find the string between two forward slashes 
	// find it in the dir entry, go to that block and start from step2 again

	FILE * fp = fopen("Sim_disk","r+");
	
	if(!fp)
	{	
		perror("Error in opening Sim_disk\n");
		fclose(fp);
		return -1;
	}
	
	// use get_metadata_block_no_of_child function
	int temp_block = root_dir_block_no;
/*	printf("root_dir_block_no is %d\n", root_dir_block_no);*/
	char c[1000];
    strcpy(c, abs_path);
    
/*    printf("///////////////////%p			%p\n", c, abs_path);*/
    
/*    printf("**************In check_permissions_on_path1.1, abs_path is %s\n", abs_path);*/
    int num_levels = get_number_of_levels(abs_path);
/*    printf("**************In check_permissions_on_path1.3, abs_path is %s\n", abs_path);*/
/*    printf("num_levels is %d\n", num_levels);*/
    int count = 0;
    char* ans;
    char * tok = strtok(c, "/");
    char * buf = (char *) malloc(sizeof(char) * 132);
    while (tok != NULL)
    {
    	count++;
        ans = tok;
        tok = strtok(NULL, "/");
	
		if(count == num_levels )
		{
/*			printf("///////////Before returning from check_permissions_on_path, abs_path is %s\n", abs_path);*/
			if(num_levels == 1)
			{
				return -1;
			}
			return temp_block;
		}
	
		if(count == 1)
		{
			continue;
		}
	        
/*        printf("ans is %s\n", ans);*/
        
        int block_no = get_metadata_block_no_of_child(temp_block, ans, fp);
/*        printf("block no in check_permissions_on_path is %d\n", block_no);*/
        if(block_no == -1)
        {
        	fclose(fp);
        	return -1;
        }
        
        temp_block = block_no;

        // now check write permission in block_no      
        fseek(fp, block_no * 512, SEEK_SET);
        
        int bytes_read = fread(buf, 1, 118, fp);
        
        if(bytes_read!=118)
        {
        	perror("Error in reading from Sim_disk");
        	fclose(fp);
        	return -1;
        }
        
        // check whether this is a directory, otherwise give an error
        if(buf[15] == '1')
        {
        	perror("Given path consists of file in between ");
        	fclose(fp);
        	return -1;
        }
        
        
        char perm = buf[18 + isa_ctx->uid];
        
        if(!(perm == '2' || perm == '6') )
        {
        	perror("Insufficient permissions");
        	fclose(fp);
        	return -1;
        }
        
    }
    fclose(fp);
/*    printf("///////////Before returning from check_permissions_on_path, abs_path is %s\n", abs_path);*/
    return 0;
	
}

int get_metadata_block_no_of_child(int b_no, char * child, FILE * fp)
{
	int offset = b_no * 512 + 132;
	
	fseek(fp, offset, SEEK_SET);
	// now start reading entries, each entry will be 21B
	// can have atmost 17 entries in this page, if it exceeds 17 then use chaining(if the chained block no is non zero)
	// chained pages can have 23 entries in them
	char * buf = (char *)malloc(sizeof(char) * 380);
	int bytes_read;
	int count = 0;

	bytes_read = fread(buf, 1, 380, fp);
	if(bytes_read != 380)
	{
		perror("Error in reading from sim_disk");
		return -1;
	}
	
	char * name = child;
	int block_no_of_required_entry;
	
	while(count<17*21)
	{
		if(buf[count] == '1')			// valid bit is 1
		{
			// extract the name and then compare it with name
			char entry_name[16];
			int i=0;
			for(i=0;i<15;i++)
			{
				if(buf[count+1+i]!='/')
				{
					entry_name[i] = buf[count+1+i];
				}
				else
				{
					entry_name[i] = '\0';
					break;
				}
			}
/*			printf("Entry_name: %s\n", entry_name);*/
			int check = strcmp(name, entry_name);
			if(!check)
			{
				// it is that entry
				char num[6];
				for(i=0;i<5;i++)
				{
					num[i] = buf[count+16+i];
				}
				num[5] = '\0';
				block_no_of_required_entry = atoi(num);
				return block_no_of_required_entry;
			}
		}
		count+=21;
	}
	
	// if not found, then use the pointers
	count = 0;
	char child_pointer[6];
	int i = 0;
	for(i=0;i<5;i++)
	{
		child_pointer[i] = buf[375+i];
	}
	child_pointer[5] = '\0';
	int pointer = atoi(child_pointer);
/*	printf("In get_metadata_block_no_of_child(), the pointer is %d\n", pointer);*/


	// else follow the chanined block			
	free(buf);
	buf = (char *)malloc(sizeof(char) * 512);
	while(1)
	{
		// if the chained block is 0, then print error message that directory not found 
		if(pointer == 0)
		{
			perror("The entry does not exist");
			return -1;
		}
	
		// go to pointer block, read it
		offset = pointer * 512;
		fseek(fp, offset, SEEK_SET);
		bytes_read = fread(buf, 1, 512, fp);
		if(bytes_read !=512)
		{
			perror("Error in reading from sim_disk\n");
			return -1;
		}
		
		count = 0;
		// read entries from the page
		while(count < 23 * 21)
		{
			if(buf[count] == '1')			// valid bit is 1
			{
				// extract the name and then compare it with name
				char entry_name[16];
				int i=0;
				for(i=0;i<15;i++)
				{
					if(buf[count+1+i]!='/')
					{
						entry_name[i] = buf[count+1+i];
					}
					else
					{
						entry_name[i] = '\0';
						break;
					}
				}
/*				printf("Entry_name: %s\n", entry_name);*/
				int check = strcmp(name, entry_name);
				if(!check)
				{
					// it is that entry
					char num[5];
					for(i=0;i<5;i++)
					{
						num[i] = buf[count+16+i];
					}
					block_no_of_required_entry = atoi(num);
					return block_no_of_required_entry;
				}
			}
			count+=21;
		}
		for(i=0;i<5;i++)
		{
			child_pointer[i] = buf[507+i];
		}
		child_pointer[5] = '\0';
		pointer = atoi(child_pointer);
	}
}

int get_free_block(int calling_block_num)
{
/*	printf("Calling block number in get_free_block is %d\n", calling_block_num);*/
	// data_section_starting_block_no
	FILE * fp;
	fp = fopen("Sim_disk", "r+");
	if(!fp)
	{
		perror("Error in opening file Sim_disk\n");
		return -1;
	}
	int offset;
	
	// num_blocks is a global var
	
	// get number of blocks
	/*int offset = 10;
	fseek(fp, offset, SEEK_SET);
	char * buf = (char *)malloc(sizeof(char) * 5);
	int bytes_read = fread(buf, 1, 5, fp);
	
	if(bytes_read != 5)
	{
		perror("Error in reading from sim_disk");
		fclose(fp);
		return -1;
	}
	
	int num_blocks = atoi(buf);*/
	
	// get disk status map
	
	//free(buf);
	char * buf = (char *)malloc(sizeof(char) * num_blocks);
	offset = 15;
	fseek(fp, offset, SEEK_SET);
	int bytes_read = fread(buf, 1, num_blocks, fp);
	if(bytes_read != num_blocks)
	{
		perror("Error in reading from sim_disk");
		fclose(fp);
		return -1;
	}
	
	///////////////////////////////////////
	
	
	if( calling_block_num >= data_section_starting_block_no)
	{
		// want free block in data portion
		int displ = 1;
		for(; ; displ++)
		{
			if((calling_block_num + displ) <= num_blocks)
			{
				if(buf[calling_block_num + displ] == '0')
				{
					// found free block
					fclose(fp);
					return 	(calling_block_num + displ);
				}
			}
			
			if((calling_block_num - displ) >= data_section_starting_block_no)
			{
				if(buf[calling_block_num - displ] == '0')
				{
					// found free block
					fclose(fp);
					return 	(calling_block_num - displ);
				}
			}
			
			if(((calling_block_num + displ) > num_blocks) &&
			((calling_block_num - displ) < data_section_starting_block_no))
				break;
		}
		
	}
	
	else
	{
		// want free block in metadata portion
		int displ = 1;
		for(; ; displ++)
		{
			if((calling_block_num + displ) <= data_section_starting_block_no)
			{
/*				printf("Block no %d has status %c\n", calling_block_num + displ, buf[calling_block_num + displ]);*/
				if(buf[calling_block_num + displ] == '0')
				{
					// found free block
					fclose(fp);
					return 	(calling_block_num + displ);
				}
			}
			
			if((calling_block_num - displ) >=0)
			{
				if(buf[calling_block_num - displ] == '0')
				{
					// found free block
					fclose(fp);
					return 	(calling_block_num - displ);
				}
			}
			
			if(((calling_block_num + displ) > data_section_starting_block_no) &&
			((calling_block_num - displ) < 0))
				break;
		}
	}
	
	
	// not got a free block
	fclose(fp);
	return -1;
	
}

int is_valid_dir_name(char* dir_name, int block_num)
{
/*	printf("In valid_function:\ndir_name : %s\nblock_num : %d\n", dir_name, block_num);*/

	FILE * fp;
	fp = fopen("Sim_disk", "r+");
	
	if(!fp)
	{
		perror("Error in opening Sim_disk");
		fclose(fp);
		return -1;
	}
	
	int b_no = get_metadata_block_no_of_child(block_num, dir_name, fp);
/*	printf("In valid_function: b_no is %d\n", b_no);*/
	if(b_no == -1)
	{
		// now check whether the name is valid or not
		// name should not contain ~, / or .
		
		int i=0;
		while(dir_name[i])
		{
			if(dir_name[i] == '~' || dir_name[i] == '/')
			{
				fclose(fp);
				return -1;
			}
			i++;
		}	
		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return -1;
	}
}

int get_number_of_levels(char * path)
{
    char c[1000];
    strcpy(c, path);
    char* ans;
    int count =0;
    char * tok = strtok(c, "/");
    while (tok != NULL)
    {
    	count++;
        ans = tok;
        tok = strtok(NULL, "/");
    }
   return count;


}

//////////////////////////////////////////////////////
// find which curr_dir has this path
// new_name is the name without slash
// name_to_be_printed is the new name, with slash
// name contains the previous name
// absolute_path is the total path(old path)

void change_path_in_curr_dir_array(char * name, char * new_name, char * absolute_path)
{
	char * new_absolute_path = (char *) malloc(sizeof(char) * (strlen(absolute_path)+strlen(new_name) ) );
	bzero(new_absolute_path, strlen(absolute_path)+strlen(new_name) );
	
	// calculate new_absolute_path
	char * t1 = strstr(absolute_path, name);
	char * prev_t1;
	while(t1)
	{
		prev_t1 = t1;
		t1+=strlen(name);
		t1 = strstr(t1, name);
	}
	
	int len1 = strlen(absolute_path) - strlen(prev_t1);
	
	strncat(new_absolute_path, absolute_path, len1);
	strncat(new_absolute_path, new_name, strlen(new_name) );
	
	printf("The new absolute path is %s\n", new_absolute_path);
	
	int i =0;
	for(i=0;i<num_processes;i++)
	{
		char * temp = strstr(curr_dir_array[i].pathname, absolute_path);	
		if(!temp)
		{
			continue;
		}
		
		// copy the remaining path of cur_dir_array[i].pathname in some other char array
		char * tt = (char *)malloc(sizeof(char) * 1000);
		bzero(tt, 1000);
		int len2 = strlen(curr_dir_array[i].pathname) - strlen(absolute_path);
		int len3 = strlen(curr_dir_array[i].pathname);
		strncat(tt, new_absolute_path, strlen(new_absolute_path) );
		strncat(tt, &curr_dir_array[i].pathname[strlen(absolute_path)], len2);
		
		bzero(curr_dir_array[i].pathname, len3 );
		strncat(curr_dir_array[i].pathname, tt, strlen(tt) );
		free(tt);
	}
}

///////////////////////////////////////////////////////

static uint64_t ke_init_time = 0;

void ke_init(void)
{
	uint32_t endian = 0x44332211;
	unsigned char *pendian = (unsigned char *) &endian;

	/* Endian check */
	if (pendian[0] != 0x11 || pendian[3] != 0x44)
		fatal("cannot run kernel on a big endian machine");
	
	isa_init();
	ke = calloc(1, sizeof(struct kernel_t));
	ke->current_pid = 1000;  /* Initial assigned pid */
	
	/* Initialize mutex for variables controlling calls to 'ke_process_events()' */
	pthread_mutex_init(&ke->process_events_mutex, NULL);

	/* Debug categories */
	isa_inst_debug_category = debug_new_category();
	isa_call_debug_category = debug_new_category();
	elf_debug_category = debug_new_category();
	ld_debug_category = debug_new_category();
	syscall_debug_category = debug_new_category();
	ctx_debug_category = debug_new_category();

	/* Initialize GPU kernel */
	gk_init();

	/* Record start time */
	ke_init_time = ke_timer();
}


/* Finalization */
void ke_done(void)
{
	struct ctx_t *ctx;

	/* Finish all contexts */
	for (ctx = ke->context_list_head; ctx; ctx = ctx->context_next)
		if (!ctx_get_status(ctx, ctx_finished))			// if ctx is not finished, then finish it
			ctx_finish(ctx, 0);

	/* Free contexts */
	while (ke->context_list_head)
		ctx_free(ke->context_list_head);
	
	/* Finalize GPU kernel */
	gk_done();

	/* End */
	free(ke);
	isa_done();
	syscall_summary();
}

/* Execute one instruction from each running context. */
void ke_run(void)
{
	struct ctx_t *ctx, *ctx_trav; 
	int flag = 0;

	/* Run an instruction from every running process */
	for (ctx = ke->running_list_head; ctx; ctx = ctx->running_next) {
		int i;
		//printf ("out - %p\n", ctx);

		for ( i = 0 ; i < ctx->instr_slice ; ++i) {
			if(ctx_get_status(ctx, ctx_finished) || ctx_get_status(ctx, ctx_suspended) )		// if context finished or suspended(blocked), then does not execute the instruction
			{
				break;
			}
			
			// printf("User ID %d, Instruction_number is %d\n", ctx->uid, instruction_number);
			// fflush(stdout);
			// here before executing the current instruction, we will check the instruction_no with what is stored in array
			schedule_interrupt * st = schedule_interrupt_return();
			if(st && st->inst_num == instruction_number)
			{
				ctx_clear_status(st->di, ctx_suspended);				// here the process will be removed from suspended list and put in running list
				ctx = ke->running_list_head;
				schedule_interrupt_remove();
				printf("\nPID: %d, Resuming at instruction no %d\n", st->di->pid, instruction_number);
				fflush(stdout);
				break;
			}
			// if same, then we should change the status of that process and start executing that process(i.e. make ctx as the head of the context list)
			// ctx_clear_status(ctx_of_that_process, ctx_suspended)
			// ctx = ke->running_list_head and start again
			// then break
			
			
			ctx_execute_inst(ctx);					// execute the instruction
			instruction_number++;

			//if (ctx!=ke->running_list_head)			// here if the ctx is not at the top of the instr, then break from this loop and run for next process
			//	break;
		}
	}
	
	/* Free finished contexts */
	while (ke->finished_list_head)
		ctx_free(ke->finished_list_head);
	
	/* Process list of suspended contexts */
	ke_process_events();

	// if here also running list is empty, then we will move the instruction count to the least one in the array
	// remove that from the array, and update the status(after updating the status, it will be at the head of the running list)
	// increase instruction_no to that value
	if(!ke->running_list_head)
	{	
		// if it is NULL
		schedule_interrupt * st = schedule_interrupt_return();
		if(st!=NULL)
		{
			instruction_number = st->inst_num;
			ctx_clear_status(st->di, ctx_suspended);
			schedule_interrupt_remove();
			printf("\nPID: %d, Resuming at instruction no %d\n", st->di->pid, instruction_number);
			fflush(stdout);
		}
	}
}


void ke_dump(FILE *f)
{
	struct ctx_t *ctx;
	int n = 0;
	ctx = ke->context_list_head;
	fprintf(f, "List of kernel contexts (arbitrary order):\n");
	while (ctx) {
		fprintf(f, "kernel context #%d:\n", n);
		ctx_dump(ctx, f);
		ctx = ctx->context_next;
		n++;
	}
}


#define LIST_INSERT_HEAD(name, ctx) { \
	assert(!ctx->name##_next && !ctx->name##_prev); \
	ctx->name##_next = ke->name##_list_head; \
	if (ctx->name##_next) ctx->name##_next->name##_prev = ctx; \
	ke->name##_list_head = ctx; \
	if (!ke->name##_list_tail) ke->name##_list_tail = ctx; \
	ke->name##_count++; \
	ke->name##_max = MAX(ke->name##_max, ke->name##_count); }

#define LIST_INSERT_TAIL(name, ctx) { \
	assert(!ctx->name##_next && !ctx->name##_prev); \
	ctx->name##_prev = ke->name##_list_tail; \
	if (ctx->name##_prev) ctx->name##_prev->name##_next = ctx; \
	ke->name##_list_tail = ctx; \
	if (!ke->name##_list_head) ke->name##_list_head = ctx; \
	ke->name##_count++; }

#define LIST_REMOVE(name, ctx) { \
	if (ctx == ke->name##_list_head) ke->name##_list_head = ke->name##_list_head->name##_next; \
	if (ctx == ke->name##_list_tail) ke->name##_list_tail = ke->name##_list_tail->name##_prev; \
	if (ctx->name##_prev) ctx->name##_prev->name##_next = ctx->name##_next; \
	if (ctx->name##_next) ctx->name##_next->name##_prev = ctx->name##_prev; \
	ctx->name##_prev = ctx->name##_next = NULL; \
	ke->name##_count--; }

#define LIST_MEMBER(name, ctx) \
	(ke->name##_list_head == ctx || ctx->name##_prev || ctx->name##_next)


void ke_list_insert_head(enum ke_list_enum list, struct ctx_t *ctx)
{
	assert(!ke_list_member(list, ctx));
	switch (list) {
	case ke_list_context: LIST_INSERT_HEAD(context, ctx); break;
	case ke_list_running: LIST_INSERT_HEAD(running, ctx); break;
	case ke_list_finished: LIST_INSERT_HEAD(finished, ctx); break;
	case ke_list_zombie: LIST_INSERT_HEAD(zombie, ctx); break;
	case ke_list_suspended: LIST_INSERT_HEAD(suspended, ctx); break;
	case ke_list_alloc: LIST_INSERT_HEAD(alloc, ctx); break;
	}
}


void ke_list_insert_tail(enum ke_list_enum list, struct ctx_t *ctx)
{
	assert(!ke_list_member(list, ctx));
	switch (list) {
	case ke_list_context: LIST_INSERT_TAIL(context, ctx); break;
	case ke_list_running: LIST_INSERT_TAIL(running, ctx); break;
	case ke_list_finished: LIST_INSERT_TAIL(finished, ctx); break;
	case ke_list_zombie: LIST_INSERT_TAIL(zombie, ctx); break;
	case ke_list_suspended: LIST_INSERT_TAIL(suspended, ctx); break;
	case ke_list_alloc: LIST_INSERT_TAIL(alloc, ctx); break;
	}
}


void ke_list_remove(enum ke_list_enum list, struct ctx_t *ctx)
{
	assert(ke_list_member(list, ctx));
	switch (list) {
	case ke_list_context: LIST_REMOVE(context, ctx); break;
	case ke_list_running: LIST_REMOVE(running, ctx); break;
	case ke_list_finished: LIST_REMOVE(finished, ctx); break;
	case ke_list_zombie: LIST_REMOVE(zombie, ctx); break;
	case ke_list_suspended: LIST_REMOVE(suspended, ctx); break;
	case ke_list_alloc: LIST_REMOVE(alloc, ctx); break;
	}
}


int ke_list_member(enum ke_list_enum list, struct ctx_t *ctx)
{
	switch (list) {
	case ke_list_context: return LIST_MEMBER(context, ctx);
	case ke_list_running: return LIST_MEMBER(running, ctx);
	case ke_list_finished: return LIST_MEMBER(finished, ctx);
	case ke_list_zombie: return LIST_MEMBER(zombie, ctx);
	case ke_list_suspended: return LIST_MEMBER(suspended, ctx);
	case ke_list_alloc: return LIST_MEMBER(alloc, ctx);
	}
	return 0;
}


#undef LIST_INSERT
#undef LIST_REMOVE
#undef LIST_MEMBER


/* Return a counter of microseconds. */
uint64_t ke_timer()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t) tv.tv_sec * 1000000 + tv.tv_usec - ke_init_time;
}


/* Schedule a call to 'ke_process_events' */
void ke_process_events_schedule()
{
	pthread_mutex_lock(&ke->process_events_mutex);
	ke->process_events_force = 1;
	pthread_mutex_unlock(&ke->process_events_mutex);
}


/* Function that suspends the host thread waiting for an event to occur.
 * When the event finally occurs (i.e., before the function finishes, a
 * call to 'ke_process_events' is scheduled.
 * The argument 'arg' is the associated guest context. */
void *ke_host_thread_suspend(void *arg)
{
	struct ctx_t *ctx = (struct ctx_t *) arg;
	uint64_t now = ke_timer();

	/* Detach this thread - we don't want the parent to have to join it to release
	 * its resources. The thread termination can be observed by atomically checking
	 * the 'ctx->host_thread_suspend_active' flag. */
	pthread_detach(pthread_self());

	/* Context suspended in 'poll' system call */
	if (ctx_get_status(ctx, ctx_nanosleep)) {
		
		uint64_t timeout;
		
		/* Calculate remaining sleep time in microseconds */
		timeout = ctx->wakeup_time > now ? ctx->wakeup_time - now : 0;
		usleep(timeout);
	
	} else if (ctx_get_status(ctx, ctx_poll)) {

		struct fd_t *fd;
		struct pollfd host_fds;
		int err, timeout;
		
		/* Get file descriptor */
		fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
		if (!fd)
			fatal("syscall 'poll': invalid 'wakeup_fd'");

		/* Calculate timeout for host call in milliseconds from now */
		if (!ctx->wakeup_time)
			timeout = -1;
		else if (ctx->wakeup_time < now)
			timeout = 0;
		else
			timeout = (ctx->wakeup_time - now) / 1000;

		/* Perform blocking host 'poll' */
		host_fds.fd = fd->host_fd;
		host_fds.events = ((ctx->wakeup_events & 4) ? POLLOUT : 0) | ((ctx->wakeup_events & 1) ? POLLIN : 0);
		err = poll(&host_fds, 1, timeout);
		if (err < 0)
			fatal("syscall 'poll': unexpected error in host 'poll'");
	
	} else if (ctx_get_status(ctx, ctx_read)) {
		
		struct fd_t *fd;
		struct pollfd host_fds;
		int err;

		/* Get file descriptor */
		fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
		if (!fd)
			fatal("syscall 'read': invalid 'wakeup_fd'");

		/* Perform blocking host 'poll' */
		host_fds.fd = fd->host_fd;
		host_fds.events = POLLIN;
		err = poll(&host_fds, 1, -1);
		if (err < 0)
			fatal("syscall 'read': unexpected error in host 'poll'");
	
	} else if (ctx_get_status(ctx, ctx_write)) {
		
		struct fd_t *fd;
		struct pollfd host_fds;
		int err;

		/* Get file descriptor */
		fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
		if (!fd)
			fatal("syscall 'write': invalid 'wakeup_fd'");

		/* Perform blocking host 'poll' */
		host_fds.fd = fd->host_fd;
		host_fds.events = POLLOUT;
		err = poll(&host_fds, 1, -1);
		if (err < 0)
			fatal("syscall 'write': unexpected error in host 'write'");

	}

	/* Event occurred - thread finishes */
	pthread_mutex_lock(&ke->process_events_mutex);
	ke->process_events_force = 1;
	ctx->host_thread_suspend_active = 0;
	pthread_mutex_unlock(&ke->process_events_mutex);
	return NULL;
}


/* Function that suspends the host thread waiting for a timer to expire,
 * and then schedules a call to 'ke_process_events'. */
void *ke_host_thread_timer(void *arg)
{
	struct ctx_t *ctx = (struct ctx_t *) arg;
	uint64_t now = ke_timer();
	struct timespec ts;
	uint64_t sleep_time;  /* In usec */

	/* Detach this thread - we don't want the parent to have to join it to release
	 * its resources. The thread termination can be observed by thread-safely checking
	 * the 'ctx->host_thread_timer_active' flag. */
	pthread_detach(pthread_self());

	/* Calculate sleep time, and sleep only if it is greater than 0 */
	if (ctx->host_thread_timer_wakeup > now) {
		sleep_time = ctx->host_thread_timer_wakeup - now;
		ts.tv_sec = sleep_time / 1000000;
		ts.tv_nsec = (sleep_time % 1000000) * 1000;  /* nsec */
		nanosleep(&ts, NULL);
	}

	/* Timer expired, schedule call to 'ke_process_events' */
	pthread_mutex_lock(&ke->process_events_mutex);
	ke->process_events_force = 1;
	ctx->host_thread_timer_active = 0;
	pthread_mutex_unlock(&ke->process_events_mutex);
	return NULL;
}


/* Check for events detected in spawned host threads, like waking up contexts or
 * sending signals.
 * The list is only processed if flag 'ke->process_events_force' is set. */
void ke_process_events()
{
	struct ctx_t *ctx, *next;
	uint64_t now = ke_timer();
	
	/* Check if events need actually be checked. */
	pthread_mutex_lock(&ke->process_events_mutex);
	if (!ke->process_events_force) {
		pthread_mutex_unlock(&ke->process_events_mutex);
		return;
	}
	
	/* By default, no subsequent call to 'ke_process_events' is assumed */
	ke->process_events_force = 0;

	/*
	 * LOOP 1
	 * Look at the list of suspended contexts and try to find
	 * one that needs to be woken up.
	 */
	for (ctx = ke->suspended_list_head; ctx; ctx = next) {

		/* Save next */
		next = ctx->suspended_next;

		/* Context is suspended in 'nanosleep' system call. */
		if (ctx_get_status(ctx, ctx_nanosleep))
		{
			uint32_t rmtp = ctx->regs->ecx;
			uint64_t zero = 0;
			uint32_t sec, usec;
			uint64_t diff;

			/* If 'ke_host_thread_suspend' is still running for this context, do nothing. */
			if (ctx->host_thread_suspend_active)
				continue;

			/* Timeout expired */
			if (ctx->wakeup_time <= now) {
				if (rmtp)
					mem_write(ctx->mem, rmtp, 8, &zero);
				syscall_debug("syscall 'nanosleep' - continue (pid %d)\n", ctx->pid);
				syscall_debug("  return=0x%x\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_nanosleep);
				continue;
			}

			/* Context received a signal */
			if (ctx->signal_masks->pending & ~ctx->signal_masks->blocked) {
				if (rmtp) {
					diff = ctx->wakeup_time - now;
					sec = diff / 1000000;
					usec = diff % 1000000;
					mem_write(ctx->mem, rmtp, 4, &sec);
					mem_write(ctx->mem, rmtp + 4, 4, &usec);
				}
				ctx->regs->eax = -EINTR;
				syscall_debug("syscall 'nanosleep' - interrupted by signal (pid %d)\n", ctx->pid);
				ctx_clear_status(ctx, ctx_suspended | ctx_nanosleep);
				continue;
			}

			/* No event available, launch 'ke_host_thread_suspend' again */
			ctx->host_thread_suspend_active = 1;
			if (pthread_create(&ctx->host_thread_suspend, NULL, ke_host_thread_suspend, ctx))
				fatal("syscall 'poll': could not create child thread");
			continue;
		}

		/* Context suspended in 'rt_sigsuspend' system call */
		if (ctx_get_status(ctx, ctx_sigsuspend))
		{
			/* Context received a signal */
			if (ctx->signal_masks->pending & ~ctx->signal_masks->blocked) {
				signal_handler_check_intr(ctx);
				ctx->signal_masks->blocked = ctx->signal_masks->backup;
				syscall_debug("syscall 'rt_sigsuspend' - interrupted by signal (pid %d)\n", ctx->pid);
				ctx_clear_status(ctx, ctx_suspended | ctx_sigsuspend);
				continue;
			}

			/* No event available. The context will never awake on its own, so no
			 * 'ke_host_thread_suspend' is necessary. */
			continue;
		}

		/* Context suspended in 'poll' system call */
		if (ctx_get_status(ctx, ctx_poll))
		{
			uint32_t prevents = ctx->regs->ebx + 6;
			uint16_t revents = 0;
			struct fd_t *fd;
			struct pollfd host_fds;
			int err;

			/* If 'ke_host_thread_suspend' is still running for this context, do nothing. */
			if (ctx->host_thread_suspend_active)
				continue;

			/* Get file descriptor */
			fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
			if (!fd)
				fatal("syscall 'poll': invalid 'wakeup_fd'");

			/* Context received a signal */
			if (ctx->signal_masks->pending & ~ctx->signal_masks->blocked) {
				signal_handler_check_intr(ctx);
				syscall_debug("syscall 'poll' - interrupted by signal (pid %d)\n", ctx->pid);
				ctx_clear_status(ctx, ctx_suspended | ctx_poll);
				continue;
			}

			/* Perform host 'poll' call */
			host_fds.fd = fd->host_fd;
			host_fds.events = ((ctx->wakeup_events & 4) ? POLLOUT : 0) | ((ctx->wakeup_events & 1) ? POLLIN : 0);
			err = poll(&host_fds, 1, 0);
			if (err < 0)
				fatal("syscall 'poll': unexpected error in host 'poll'");

			/* POLLOUT event available */
			if (ctx->wakeup_events & host_fds.revents & POLLOUT) {
				revents = POLLOUT;
				mem_write(ctx->mem, prevents, 2, &revents);
				ctx->regs->eax = 1;
				syscall_debug("syscall poll - continue (pid %d) - POLLOUT occurred in file\n", ctx->pid);
				syscall_debug("  retval=%d\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_poll);
				continue;
			}

			/* POLLIN event available */
			if (ctx->wakeup_events & host_fds.revents & POLLIN) {
				revents = POLLIN;
				mem_write(ctx->mem, prevents, 2, &revents);
				ctx->regs->eax = 1;
				syscall_debug("syscall poll - continue (pid %d) - POLLIN occurred in file\n", ctx->pid);
				syscall_debug("  retval=%d\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_poll);
				continue;
			}

			/* Timeout expired */
			if (ctx->wakeup_time && ctx->wakeup_time < now) {
				revents = 0;
				mem_write(ctx->mem, prevents, 2, &revents);
				syscall_debug("syscall poll - continue (pid %d) - time out\n", ctx->pid);
				syscall_debug("  return=0x%x\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_poll);
				continue;
			}

			/* No event available, launch 'ke_host_thread_suspend' again */
			ctx->host_thread_suspend_active = 1;
			if (pthread_create(&ctx->host_thread_suspend, NULL, ke_host_thread_suspend, ctx))
				fatal("syscall 'poll': could not create child thread");
			continue;
		}


		/* Context suspended in a 'write' system call  */
		if (ctx_get_status(ctx, ctx_write))
		{
			struct fd_t *fd;
			int count, err;
			uint32_t pbuf;
			void *buf;
			struct pollfd host_fds;

			/* If 'ke_host_thread_suspend' is still running for this context, do nothing. */
			if (ctx->host_thread_suspend_active)
				continue;

			/* Context received a signal */
			if (ctx->signal_masks->pending & ~ctx->signal_masks->blocked) {
				signal_handler_check_intr(ctx);
				syscall_debug("syscall 'write' - interrupted by signal (pid %d)\n", ctx->pid);
				ctx_clear_status(ctx, ctx_suspended | ctx_write);
				continue;
			}

			/* Get file descriptor */
			fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
			if (!fd)
				fatal("syscall 'write': invalid 'wakeup_fd'");

			/* Check if data is ready in file by polling it */
			host_fds.fd = fd->host_fd;
			host_fds.events = POLLOUT;
			err = poll(&host_fds, 1, 0);
			if (err < 0)
				fatal("syscall 'write': unexpected error in host 'poll'");

			/* If data is ready in the file, wake up context */
			if (host_fds.revents) {
				pbuf = ctx->regs->ecx;
				count = ctx->regs->edx;
				buf = malloc(count);
				mem_read(ctx->mem, pbuf, count, buf);

				count = write(fd->host_fd, buf, count);
				if (count < 0)
					fatal("syscall 'write': unexpected error in host 'write'");

				ctx->regs->eax = count;
				free(buf);

				syscall_debug("syscall write - continue (pid %d)\n", ctx->pid);
				syscall_debug("  return=0x%x\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_write);
				continue;
			}

			/* Data is not ready to be written - launch 'ke_host_thread_suspend' again */
			ctx->host_thread_suspend_active = 1;
			if (pthread_create(&ctx->host_thread_suspend, NULL, ke_host_thread_suspend, ctx))
				fatal("syscall 'write': could not create child thread");
			continue;
		}

		/* Context suspended in 'read' system call */
		if (ctx_get_status(ctx, ctx_read))
		{
			struct fd_t *fd;
			uint32_t pbuf;
			int count, err;
			void *buf;
			struct pollfd host_fds;

			/* If 'ke_host_thread_suspend' is still running for this context, do nothing. */
			if (ctx->host_thread_suspend_active)
				continue;

			/* Context received a signal */
			if (ctx->signal_masks->pending & ~ctx->signal_masks->blocked) {
				signal_handler_check_intr(ctx);
				syscall_debug("syscall 'read' - interrupted by signal (pid %d)\n", ctx->pid);
				ctx_clear_status(ctx, ctx_suspended | ctx_read);
				continue;
			}

			/* Get file descriptor */
			fd = fdt_entry_get(ctx->fdt, ctx->wakeup_fd);
			if (!fd)
				fatal("syscall 'read': invalid 'wakeup_fd'");

			/* Check if data is ready in file by polling it */
			host_fds.fd = fd->host_fd;
			host_fds.events = POLLIN;
			err = poll(&host_fds, 1, 0);
			if (err < 0)
				fatal("syscall 'read': unexpected error in host 'poll'");

			/* If data is ready, perform host 'read' call and wake up */
			if (host_fds.revents) {
				pbuf = ctx->regs->ecx;
				count = ctx->regs->edx;
				buf = malloc(count);
				
				count = read(fd->host_fd, buf, count);
				if (count < 0)
					fatal("syscall 'read': unexpected error in host 'read'");

				ctx->regs->eax = count;
				mem_write(ctx->mem, pbuf, count, buf);
				free(buf);

				syscall_debug("syscall 'read' - continue (pid %d)\n", ctx->pid);
				syscall_debug("  return=0x%x\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_read);
				continue;
			}

			/* Data is not ready. Launch 'ke_host_thread_suspend' again */
			ctx->host_thread_suspend_active = 1;
			if (pthread_create(&ctx->host_thread_suspend, NULL, ke_host_thread_suspend, ctx))
				fatal("syscall 'read': could not create child thread");
			continue;
		}

		/* Context suspended in a 'waitpid' system call */
		if (ctx_get_status(ctx, ctx_waitpid))
		{
			struct ctx_t *child;
			uint32_t pstatus;

			/* A zombie child is available to 'waitpid' it */
			child = ctx_get_zombie(ctx, ctx->wakeup_pid);
			if (child) {

				/* Continue with 'waitpid' system call */
				pstatus = ctx->regs->ecx;
				ctx->regs->eax = child->pid;
				if (pstatus)
					mem_write(ctx->mem, pstatus, 4, &child->exit_code);
				ctx_set_status(child, ctx_finished);

				syscall_debug("syscall waitpid - continue (pid %d)\n", ctx->pid);
				syscall_debug("  return=0x%x\n", ctx->regs->eax);
				ctx_clear_status(ctx, ctx_suspended | ctx_waitpid);
				continue;
			}

			/* No event available. Since this context won't awake on its own, no
			 * 'ke_host_thread_suspend' is needed. */
			continue;
		}
	}


	/*
	 * LOOP 2
	 * Check list of all contexts for expired timers.
	 */
	for (ctx = ke->context_list_head; ctx; ctx = ctx->context_next)
	{
		int sig[3] = { 14, 26, 27 };  /* SIGALRM, SIGVTALRM, SIGPROF */
		int i;

		/* If there is already a 'ke_host_thread_timer' running, do nothing. */
		if (ctx->host_thread_timer_active)
			continue;

		/* Check for any expired 'itimer': itimer_value < now
		 * In this case, send corresponding signal to process.
		 * Then calculate next 'itimer' occurrence: itimer_value = now + itimer_interval */
		for (i = 0; i < 3; i++ ) {
			
			/* Timer inactive or not expired yet */
			if (!ctx->itimer_value[i] || ctx->itimer_value[i] > now)
				continue;

			/* Timer expired - send a signal.
			 * The target process might be suspended, so the host thread is canceled, and a new
			 * call to 'ke_process_events' is scheduled. Since 'ke_process_events_mutex' is
			 * already locked, the thread-unsafe version of 'ctx_host_thread_suspend_cancel' is used. */
			__ctx_host_thread_suspend_cancel(ctx);
			ke->process_events_force = 1;
			sim_sigset_add(&ctx->signal_masks->pending, sig[i]);

			/* Calculate next occurrence */
			ctx->itimer_value[i] = 0;
			if (ctx->itimer_interval[i])
				ctx->itimer_value[i] = now + ctx->itimer_interval[i];
		}

		/* Calculate the time when next wakeup occurs. */
		ctx->host_thread_timer_wakeup = 0;
		for (i = 0; i < 3; i++) {
			if (!ctx->itimer_value[i])
				continue;
			assert(ctx->itimer_value[i] >= now);
			if (!ctx->host_thread_timer_wakeup || ctx->itimer_value[i] < ctx->host_thread_timer_wakeup)
				ctx->host_thread_timer_wakeup = ctx->itimer_value[i];
		}

		/* If a new timer was set, launch 'ke_host_thread_timer' again */
		if (ctx->host_thread_timer_wakeup) {
			ctx->host_thread_timer_active = 1;
			if (pthread_create(&ctx->host_thread_timer, NULL, ke_host_thread_timer, ctx))
				fatal("%s: could not create child thread", __FUNCTION__);
		}
	}


	/*
	 * LOOP 3
	 * Process pending signals in running contexts to launch signal handlers
	 */
	for (ctx = ke->running_list_head; ctx; ctx = ctx->running_next)
	{
		signal_handler_check(ctx);
	}

	
	/* Unlock */
	pthread_mutex_unlock(&ke->process_events_mutex);
}

