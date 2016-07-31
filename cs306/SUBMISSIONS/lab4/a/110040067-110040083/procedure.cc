
/*********************************************************************************************

                                cfglp : A CFG Language Processor
                                --------------------------------

           About:

           Implemented   by  Tanu  Kanvar (tanu@cse.iitb.ac.in) and Uday
           Khedker    (http://www.cse.iitb.ac.in/~uday)  for the courses
           cs302+cs306: Language  Processors  (theory and  lab)  at  IIT
           Bombay.

           Release  date  Jan  15, 2013.  Copyrights  reserved  by  Uday
           Khedker. This  implemenation  has been made  available purely
           for academic purposes without any warranty of any kind.

           Documentation (functionality, manual, and design) and related
           tools are  available at http://www.cse.iitb.ac.in/~uday/cfglp


***********************************************************************************************/

#include<string>
#include<fstream>
#include<iostream>

using namespace std;

#include"error-display.hh"
#include"local-environment.hh"

#include"symbol-table.hh"
#include"ast.hh"
#include"basic-block.hh"
#include"procedure.hh"
#include"program.hh"

// constructor for Procedure class
Procedure::Procedure(Data_Type proc_return_type, string proc_name)
{
	return_type = proc_return_type;
	name = proc_name;
}

// destructor for procedure class
Procedure::~Procedure()
{
	list<Basic_Block *>::iterator i;
	for (i = basic_block_list.begin(); i != basic_block_list.end(); i++)
		delete (*i);
}

// returns name of the procedure
string Procedure::get_proc_name()
{
	return name;
}

// set the basic block list 
void Procedure::set_basic_block_list(list<Basic_Block *> bb_list)
{
	basic_block_list = bb_list;
}

// set the local symbol table 
void Procedure::set_local_list(Symbol_Table & new_list)
{
	local_symbol_table = new_list;
	local_symbol_table.set_table_scope(local);
}

// returns the data type of the procedure
Data_Type Procedure::get_return_type()
{
	return return_type;
}

// returns true if variable is in the symbol table, otherwise returns false
bool Procedure::variable_in_symbol_list_check(string variable)
{
	return local_symbol_table.variable_in_symbol_list_check(variable);
}

// returns the entry corressponding to the variable from the symbol table
Symbol_Table_Entry & Procedure::get_symbol_table_entry(string variable_name)
{
	return local_symbol_table.get_symbol_table_entry(variable_name);
}

void Procedure::print_ast(ostream & file_buffer)
{
	file_buffer << PROC_SPACE << "Procedure: main" << "\n";

	list<Basic_Block *>::iterator i;
	for(i = basic_block_list.begin(); i != basic_block_list.end(); i++)
		(*i)->print_bb(file_buffer);
}

// returns the starting basic block of the procedure	
Basic_Block & Procedure::get_start_basic_block()
{
	list<Basic_Block *>::iterator i;
	i = basic_block_list.begin();
	return **i;
}

// returns the next basic block
Basic_Block * Procedure::get_next_bb(Basic_Block & current_bb)
{
	bool flag = false;

	list<Basic_Block *>::iterator i;
	for(i = basic_block_list.begin(); i != basic_block_list.end(); i++)
	{
		if((*i)->get_bb_number() == current_bb.get_bb_number())
		{
			flag = true;
			continue;
		}
		if (flag)
			return (*i);
	}
	
	return NULL;
}

Eval_Result & Procedure::evaluate(ostream & file_buffer)
{
	Local_Environment & eval_env = *new Local_Environment();
	local_symbol_table.create(eval_env);
	
	Eval_Result * result = NULL;

	file_buffer << PROC_SPACE << "Evaluating Procedure " << name << "\n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (before evaluating):\n";
	eval_env.print(file_buffer);
	file_buffer << "\n";
	
	Basic_Block * current_bb = &(get_start_basic_block());

	while (current_bb)
	{
		result = &(current_bb->evaluate(eval_env, file_buffer));
		// start from the beginning till you get the required 
		
		if(result->get_result_enum() == void_result)
		{
			break;
		}
		
		if(result->get_conditional() == true)
		{
			list<Basic_Block *>::iterator i;
			for(i = basic_block_list.begin(); i != basic_block_list.end(); i++)
			{
				if((*i)->get_bb_number() == result->get_value())
				{
					break;
				}
			}
			if(i == basic_block_list.end())
			{
				char msg[20];
				sprintf(msg, "bb %d doesn't exist", (int)result->get_value());
				string str = string(msg);
				report_error(str,NOLINE);
				exit(0);
			}
			current_bb = &(**i);
			continue;	
		}	
		current_bb = get_next_bb(*current_bb);		
	}

	file_buffer << "\n\n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (after evaluating):\n";
	eval_env.print(file_buffer);

	return *result;
}

