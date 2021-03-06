
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

#ifndef PROCEDURE_HH
#define PROCEDURE_HH

#include<string>
#include<map>
#include<list>

#define PROC_SPACE "   "
#define LOC_VAR_SPACE "      "

using namespace std;

class Procedure;

// here add for no of arguments and their types
class Procedure
{
	Data_Type return_type;
	string name;
	Symbol_Table local_symbol_table;
	list<Basic_Block *> basic_block_list;

	list<Data_Type> return_list;
	// added by me
	int no_of_arguments;
//	Data_Type return_data_type;
	//map<string, Data_Type> argument_type_list;
	//////////////////////////////

public:
	Procedure(Data_Type proc_return_type, string proc_name);
	// added by me
	Procedure(Data_Type proc_return_type, string proc_name, int num_arguments, Symbol_Table sym);
	//////////////////////////////
	~Procedure();

	string get_proc_name();
	void set_basic_block_list(list<Basic_Block *> bb_list);
	void set_local_list(Symbol_Table & new_list);
	Data_Type get_return_type();
	void set_return_type(Data_Type t);
	Symbol_Table_Entry & get_symbol_table_entry(string variable_name);

	// added by me
	//void set_arguments_list(map<string, Data_Type> a);
	//map<string, Data_Type> get_arguments_list();
	void append_local_list(Symbol_Table my_list);		// append the passed symbol table to local_symbol_table
	Symbol_Table get_symbol_table();
	void set_no_of_arguments(int a);
	int get_no_of_arguments();
	void push_in_return_list(Data_Type d);
	list<Data_Type> get_return_list();
	//////////////////////////////

	void print_ast(ostream & file_buffer);

	Basic_Block * get_next_bb(Basic_Block & current_bb);
	Basic_Block & get_start_basic_block();

	Eval_Result & evaluate(ostream & file_buffer);
	Eval_Result & evaluate(Local_Environment prev_env, ostream & file_buffer, list<Ast *> l);
	bool variable_in_symbol_list_check(string variable);
};

#endif
