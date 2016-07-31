
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

Procedure::Procedure(Data_Type proc_return_type, string proc_name, int num_arguments, Symbol_Table sym)
{
	return_type = proc_return_type;
	name = proc_name;
	no_of_arguments = num_arguments;
	local_symbol_table = sym;
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

void Procedure::set_return_type(Data_Type t)
{
	return_type = t;
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

void Procedure::push_in_return_list(Data_Type d)
{
	return_list.push_back(d);
}

list<Data_Type> Procedure::get_return_list()
{
	return return_list;
}

////////////////////////////////// added by me
/*
void Procedure::set_arguments_list(map<string, Data_Type> a)
{
	argument_type_list = a;
}

map<string, Data_Type> Procedure::get_arguments_list()
{
	return argument_type_list;
}
*/

void Procedure::append_local_list(Symbol_Table my_list)
{
	local_symbol_table.set_table_scope(local);
	list<Symbol_Table_Entry * > temp = my_list.get_variable_table();
	list<Symbol_Table_Entry * >::iterator itr;
	for(itr = temp.begin();itr!=temp.end();itr++)
	{
		// if already present in the symbol table then give error, otherwise push in the symbol table
		if(local_symbol_table.variable_in_symbol_list_check( (*itr)->get_variable_name() ) )
		{
			report_error("Varible name cannot be the same as argument name",NOLINE);
		}
		else
		{
			local_symbol_table.push_symbol((*itr));
		}
	}
}

Symbol_Table Procedure::get_symbol_table()
{
	return local_symbol_table;
}

void Procedure::set_no_of_arguments(int a)
{
	no_of_arguments = a;
}

int Procedure::get_no_of_arguments()
{
	return no_of_arguments;
}
//////////////////////////////////

void Procedure::print_ast(ostream & file_buffer)
{
	file_buffer << PROC_SPACE << "Procedure: " <<name<< "\n";
	//file_buffer << PROC_SPACE << "Procedure: " <<name;

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

	file_buffer << PROC_SPACE << "Evaluating Procedure << " << name << " >>\n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (before evaluating):\n";
	eval_env.print(file_buffer);
	file_buffer << "\n";
	
	Basic_Block * current_bb = &(get_start_basic_block());

	while (current_bb)
	{
		result = &(current_bb->evaluate(eval_env, file_buffer));
		// start from the beginning till you get the required 
		
		if(result->get_execution_status() == true && result->get_functional() == false)
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

	if(result->get_result_enum() != void_result)
	{
		string var_name = "return";
		if(get_return_type() == int_data_type)
		{
			Eval_Result_Value_Int * i = new Eval_Result_Value_Int();
			i->set_value((int)result->get_value() );
			eval_env.put_variable_value(*i, var_name );
		}
		else
		{
			Eval_Result_Value_Float * i = new Eval_Result_Value_Float();
			i->set_value(result->get_value() );
			eval_env.put_variable_value(*i, var_name );		
		}
	}

	file_buffer << "\n\n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (after evaluating) Function: << "<< name <<" >>\n";
	eval_env.print(file_buffer);

	result->set_functional(true);
	return *result;
}

// this is a new function which i have defined
Eval_Result & Procedure::evaluate(Local_Environment prev_env, ostream & file_buffer, list<Ast *> l)
{
	// now i should take list<Ast*> as an argument and then set the values here using put_variable_value
	//cout<<"In my evaluate of "<<name<<"\n";

	Local_Environment & eval_env = *new Local_Environment();
	//local_symbol_table.create(eval_env);
	
	// write our own thing for initializing the variables and putting them in eval_env
	int count=0;
	list<Symbol_Table_Entry *> temp = local_symbol_table.get_variable_table();
	list<Symbol_Table_Entry *>::iterator itr = temp.begin();
	list<Ast*>::iterator itr1 = l.begin();
	for(;itr!=temp.end();itr++)
	{
		//cout<<"Inside for loop\n";
		//cout<<"Name of var is "<< (*itr)->get_variable_name()<<endl;
		if(count<no_of_arguments)
		{
			// here initialize them with the help of list l
			if((*itr)->get_data_type() == int_data_type)
			{
				//cout<<"Inside int\n";
				Eval_Result & res = (*itr1)->evaluate(prev_env, file_buffer);
				if(res.is_variable_defined() == false)
				{
					report_error("Variable has to defined to be passed as parameter", NOLINE);
				}
				
				Eval_Result_Value_Int * my_res = new Eval_Result_Value_Int();
				my_res->set_value(res.get_value() );
				eval_env.put_variable_value(*my_res, (*itr)->get_variable_name() );
			}
			else
			{
				//cout<<"Inside float\n";
				Eval_Result &res = (*itr1)->evaluate(prev_env, file_buffer);
				if(res.is_variable_defined() == false)
				{
					report_error("Variable has to defined to be passed as parameter", NOLINE);
				}
				//cout<<"After eval in float\n";
				Eval_Result_Value_Float * my_res = new Eval_Result_Value_Float();
				//cout<<res.get_value();		// res.get_value is giving error
				my_res->set_value(res.get_value() );
				eval_env.put_variable_value(*my_res, (*itr)->get_variable_name() );
			}
			count++;
			itr1++;
		}
		else
		{
			// put them in symbol_table
			// scope will be local only
			if((*itr)->get_data_type() == int_data_type)
			{
				Eval_Result_Value_Int * j = new Eval_Result_Value_Int();
				//j->set_variable_status(true);
				eval_env.put_variable_value(*j,(*itr)->get_variable_name() );
			}
			else
			{
				Eval_Result_Value_Float * j = new Eval_Result_Value_Float();
				//j->set_variable_status(true);
				eval_env.put_variable_value(*j,(*itr)->get_variable_name() );
			}
			
		}
	}
	
	Eval_Result * result = NULL;

	file_buffer << PROC_SPACE << "Evaluating Procedure << " << name << " >> \n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (before evaluating):\n";
	eval_env.print(file_buffer);
	file_buffer << "\n";
	
	Basic_Block * current_bb = &(get_start_basic_block());

	while (current_bb)
	{
		result = &(current_bb->evaluate(eval_env, file_buffer));
		// start from the beginning till you get the required 
		
		if(result->get_execution_status() == true && result->get_functional() == false )
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

	if(result->get_result_enum() != void_result)
	{
		string var_name = "return";
		if(get_return_type() == int_data_type)
		{
			Eval_Result_Value_Int * i = new Eval_Result_Value_Int();
			i->set_value((int)result->get_value() );
			eval_env.put_variable_value(*i, var_name );
		}
		else
		{
			Eval_Result_Value_Float * i = new Eval_Result_Value_Float();
			i->set_value(result->get_value() );
			eval_env.put_variable_value(*i, var_name );		
		}
	}

	file_buffer << "\n\n";
	file_buffer << LOC_VAR_SPACE << "Local Variables (after evaluating) Function: << "<< name << " >>\n";
	eval_env.print(file_buffer);
	result->set_functional(true);
	return *result;
}
