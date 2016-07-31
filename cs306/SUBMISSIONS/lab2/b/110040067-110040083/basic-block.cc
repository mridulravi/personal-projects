
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

using namespace std;

#include"local-environment.hh"
#include"error-display.hh"
#include"user-options.hh"

#include"symbol-table.hh"
#include"ast.hh"
#include"basic-block.hh"

// constructor
Basic_Block::Basic_Block(int basic_block_number, list<Ast *> & ast_list)
{
	id_number = basic_block_number;
	statement_list = ast_list;
}

// destructor
Basic_Block::~Basic_Block()
{
	list<Ast *>::iterator i;
	for (i = statement_list.begin(); i != statement_list.end(); i++)
		delete (*i);
}

// returns the id of the basic block
int Basic_Block::get_bb_number()
{
	return id_number;
}

// writes about the basic block in the ostream object passed as an argument
void Basic_Block::print_bb(ostream & file_buffer)
{
//	file_buffer << BB_SPACE << "Basic_Block " << id_number << "\n";
	file_buffer << "\n" << BB_SPACE << "Basic_Block " << id_number <<"\n";
	list<Ast *>::iterator i;		// iterator which will be used to iterate over the statement list
	for(i = statement_list.begin(); i != statement_list.end(); i++)
		(*i)->print_ast(file_buffer);			// calling the print function of ast to print information about it
}

// evaluates the result and returns it
Eval_Result & Basic_Block::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result * result = NULL;				

	file_buffer << "\n" << BB_SPACE << "Basic Block: " << id_number << "\n";

	list <Ast *>::iterator i;							// iterator used to iterate over statement list
	for (i = statement_list.begin(); i != statement_list.end(); i++)
	{
		if((*i) == NULL)								// if the AST pointer points to NULL, then report an error
			report_error ("Ast pointer seems to be NULL", NOLINE);

		result = &((*i)->evaluate(eval_env, file_buffer)); 				// calling the evaluate function of the ast or assignment_ast or number_ast and storing the address of it(the evaluated value will itself be of type eval_value) in result
		
		// now result has Eval_Result type, we can decide on basis of "result" what to do 
		
		// if result has defined variable false, then break from the loop
		
		if(result->is_variable_defined() == false)
		{
			break;
		}
		// 
	}
	
	// the value of the return stores which will be our next block
	return *result;					// returning the value of the result and not the pointer
	// using this we can decide which block should be evaluated next
	
}

// one doubt here, that we are returning the end result only, whereas result will be calculated for each member of the statement list, so we should return a list of the results, instead of a single result

