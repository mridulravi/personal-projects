
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

#include<iostream>
#include<fstream>

using namespace std;

#include"user-options.hh"
#include"error-display.hh"
#include"local-environment.hh"

#include"symbol-table.hh"
#include"ast.hh"

// = 0 after declaration of a function means it is a pure virtual function, a pure virtual function means that all the classes which will inherit this class have to override this function. If any function of a class is a pure virtual function, then that class becomes virtual class meaning that no object of this class can be created. The pure virtual functions can only be called statically

// Since Ast is a virtual class and its functions are pure virtual functions, therefore they should never be called, and if they are called then throw an error
Ast::Ast()
{}

Ast::~Ast()
{}

bool Ast::check_ast(int line)
{
	report_internal_error("Should not reach, Ast : check_ast");
}

Data_Type Ast::get_data_type()
{
	report_internal_error("Should not reach, Ast : get_data_type");
}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	report_internal_error("Should not reach, Ast : print_value");
}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	report_internal_error("Should not reach, Ast : get_value_of_evaluation");
}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	report_internal_error("Should not reach, Ast : set_value_of_evaluation");
}

////////////////////////////////////////////////////////////////

// constructor
Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
}

// destructor
Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

// return the data type of the node
Data_Type Assignment_Ast::get_data_type()
{
	return node_data_type;
}

// this function checks whether the ast is valid or not, i.e. it compares the data type of LHS and RHS and if both are equal, then it sets the data type of node to this value and returns true, otherwise throws an error
bool Assignment_Ast::check_ast(int line)
{
	if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

	report_error("Assignment statement data type not compatible", line);
}

// prints the ast in the ostream object passed as an argument
void Assignment_Ast::print_ast(ostream & file_buffer)
{
	file_buffer << AST_SPACE << "Asgn:\n";

	file_buffer << AST_NODE_SPACE"LHS (";				// here i think there is an error, there should be "<<" before "LHS ("
	lhs->print_ast(file_buffer);						// calling the print_ast function on LHS
	file_buffer << ")\n";

	file_buffer << AST_NODE_SPACE << "RHS (";
	rhs->print_ast(file_buffer);						// calling the print_ast function on RHS
	file_buffer << ")\n";
}

// evaluates the assignment and returns the value
Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);
	// evaluates the RHS of the assignment (because that is the thing to be examined in an assignment statement)
	// stores the result returned by it in "result"

	if (result.is_variable_defined() == false)
		report_error("Variable should be defined to be on rhs", NOLINE);
	// if variable of the result value returned after evaluation of RHS is false, then report an error 

	lhs->set_value_of_evaluation(eval_env, result);
	// set the calculated value as LHS's value

	// Print the result
	print_ast(file_buffer);			

	// print lhs
	lhs->print_value(eval_env, file_buffer);

	return result;
}
/////////////////////////////////////////////////////////////////

// constructor
Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry)
{
	variable_name = name;
	variable_symbol_entry = var_entry;
}

// destructor
Name_Ast::~Name_Ast()
{}

// return data type of the Symbol_entry object variable_symbol_entry
Data_Type Name_Ast::get_data_type()
{
	return variable_symbol_entry.get_data_type();
}

// print the name in ostream object passesd as an argument
void Name_Ast::print_ast(ostream & file_buffer)
{
	file_buffer << "Name : " << variable_name;
}

// print value of the variable(if exists ) in file_buffer, otherwise throws an error
void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result_Value * loc_var_val = eval_env.get_variable_value(variable_name);
	Eval_Result_Value * glob_var_val = interpreter_global_table.get_variable_value(variable_name);

	file_buffer << "\n" << AST_SPACE << variable_name << " : ";

	// if undefined in both local and global, then print undefined
	if (!eval_env.is_variable_defined(variable_name) && !interpreter_global_table.is_variable_defined(variable_name))
		file_buffer << "undefined";
	// else if defined as local 
	else if (eval_env.is_variable_defined(variable_name) && loc_var_val != NULL)
	{	// if type is int, then continue, otherwise throw an error
		if (loc_var_val->get_result_enum() == int_result)
			file_buffer << loc_var_val->get_value() << "\n";
		else
			report_internal_error("Result type can only be int and float");
	}
	// else, var is defined as global variable 
	else
	{	// if type is int, then continue, otherwise throw an error
		if (glob_var_val->get_result_enum() == int_result)
		{
			if (glob_var_val == NULL)
				file_buffer << "0\n";
			else
				file_buffer << glob_var_val->get_value() << "\n";
		}
		else
			report_internal_error("Result type can only be int and float");
	}
	file_buffer << "\n";
}

// here checks whether variable exists in passes environment, if it does then its value is extracted and returned
// otherwise, its value is found in global table and returned
Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	if (eval_env.does_variable_exist(variable_name))
	{
		Eval_Result * result = eval_env.get_variable_value(variable_name);
		return *result;
	}

	Eval_Result * result = interpreter_global_table.get_variable_value(variable_name);
	return *result;
}

// the argumnts are result and a local environment
// if the type of the result is int, then a new variable of eval_result_value is created and assigned this value
// if the passed local environment has this variable, then this new variable i, along with the variable name is put in the passed environment
// otherwise it is put intointerpreter global table
void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	Eval_Result_Value * i;
	if (result.get_result_enum() == int_result)
	{
		i = new Eval_Result_Value_Int();
	 	i->set_value(result.get_value());
	}

	if (eval_env.does_variable_exist(variable_name))
		eval_env.put_variable_value(*i, variable_name);
	else
		interpreter_global_table.put_variable_value(*i, variable_name);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	return get_value_of_evaluation(eval_env);
}

///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::Number_Ast(DATA_TYPE number, Data_Type constant_data_type)
{
	constant = number;
	node_data_type = constant_data_type;
}

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::~Number_Ast()
{}

template <class DATA_TYPE>
Data_Type Number_Ast<DATA_TYPE>::get_data_type()
{
	return node_data_type;
}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::print_ast(ostream & file_buffer)
{
	file_buffer << "Num : " << constant;
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if (node_data_type == int_data_type)
	{
		Eval_Result & result = *new Eval_Result_Value_Int();			// what does * new means
		result.set_value(constant);

		return result;
	}
	// I think if we have to add functionality for float, then we have to add like this only 
}

///////////////////////////////////////////////////////////////////////////////

Return_Ast::Return_Ast()
{}

Return_Ast::~Return_Ast()
{}

void Return_Ast::print_ast(ostream & file_buffer)
{
	file_buffer << AST_SPACE << "Return <NOTHING>\n";
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = *new Eval_Result_Value_Int();
	return result;
}

template class Number_Ast<int>;
