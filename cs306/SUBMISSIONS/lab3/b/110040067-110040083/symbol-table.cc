
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
#include<iostream>

using namespace std;

#include"local-environment.hh"
#include"user-options.hh"
#include"error-display.hh"

#include"symbol-table.hh"

#include"ast.hh"
#include"basic-block.hh"
#include"procedure.hh"
#include"program.hh"

// constructor
Symbol_Table::Symbol_Table()
{}

// destructor
Symbol_Table::~Symbol_Table()
{}

// sets the scope to the passed value
void Symbol_Table::set_table_scope(Table_Scope list_scope)
{
	scope = list_scope;
}

// returns the scope of the symbol table
Table_Scope Symbol_Table::get_table_scope()
{
	return scope;
}

// push a variable in symbol table
void Symbol_Table::push_symbol(Symbol_Table_Entry * variable)
{
	variable_table.push_back(variable);
}

// have to understand this function carefully
void Symbol_Table::global_list_in_proc_map_check(int line)
{
	list<Symbol_Table_Entry *>::iterator i;
	for (i = variable_table.begin(); i != variable_table.end(); i++)
	{
		string name = (*i)->get_variable_name();
		program_object.variable_in_proc_map_check(name, line);			// check where is it defined and what is it that it performs
	}
}

// this function checks whether the variable is present in variable table(which is a list of pointers to symbol_table_entry), if any of the symbol_table_entry object has this name, thn it returns true, otherwise false.
bool Symbol_Table::variable_in_symbol_list_check(string variable)
{
	list<Symbol_Table_Entry *>::iterator i;
	for (i = variable_table.begin(); i != variable_table.end(); i++)
	{
		if ((*i)->get_variable_name() == variable)
			return true;
	}

	return false;
}


// returns(if found) the address of the symbol table entry corressponding to the passed variable name, otherwise it prints an error
// here we are returning a reference to symbol_table_entry
Symbol_Table_Entry & Symbol_Table::get_symbol_table_entry(string variable_name)
{
	list<Symbol_Table_Entry *>::iterator i;			// we will use i to iterate over variable list
	for (i = variable_table.begin(); i != variable_table.end(); i++)
	{												// i will be an object of iterator type, such that *i will access the element in the list
		if ((*i)->get_variable_name() == variable_name)
			return **i;								// this is correct, because *i means a pointer to Symbol_table_entry, so if we have to return the Symbol_table_entry itself instead of a pointer to it, we should dereference it further
	}

	report_error("variable symbol entry doesn't exist", NOLINE);
}

void Symbol_Table::create(Local_Environment & local_global_variables_table)
{
	list<Symbol_Table_Entry *>::iterator i;

	for (i = variable_table.begin(); i != variable_table.end(); i++)
	{
		string name = (*i)->get_variable_name();
		Eval_Result_Value_Int * j = new Eval_Result_Value_Int();
		if (scope == global)
		{
			j->set_variable_status(true);
			j->set_value(0);
		}

		local_global_variables_table.put_variable_value(*j, name);
	}
}

/////////////////////////////////////////////////////////////

// constructor without any arguments
Symbol_Table_Entry::Symbol_Table_Entry()
{}

// constructor with arguments
Symbol_Table_Entry::Symbol_Table_Entry(string & name, Data_Type new_data_type)
{
	variable_name = name;
	variable_data_type = new_data_type;
}

// destructor
Symbol_Table_Entry::~Symbol_Table_Entry()
{}

// returns the data type of the variable
Data_Type Symbol_Table_Entry::get_data_type()
{
	return variable_data_type;
}

// returns the name of the variable
string Symbol_Table_Entry::get_variable_name()
{
	return variable_name;
}
