
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
#include"basic-block.hh"
#include"procedure.hh"
#include"program.hh"

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

void Ast::set_data_type(Data_Type data_type)
{
	report_internal_error("Should not reach, Ast : set_data_type");
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

void Assignment_Ast::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
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
	file_buffer << "\n"<< AST_SPACE << "Asgn:\n";
	//file_buffer<< AST_SPACE << "Asgn:\n";

	file_buffer << AST_NODE_SPACE << "LHS (";			// here i think there is an error, there should be "<<" before "LHS ("
	lhs->print_ast(file_buffer);						// calling the print_ast function on LHS
	file_buffer << ")\n";

	file_buffer << AST_NODE_SPACE << "RHS (";
	rhs->print_ast(file_buffer);						// calling the print_ast function on RHS
	//file_buffer << ")\n";
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

	if(result.get_result_enum() == void_result)
		report_error("The right hand side of assignment has type void_data_type", NOLINE);
	

	lhs->set_value_of_evaluation(eval_env, result);
	// set the calculated value as LHS's value

	//file_buffer << "\n";
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
	node_data_type = var_entry.get_data_type();
}

// destructor
Name_Ast::~Name_Ast()
{}

// return data type of the Symbol_entry object variable_symbol_entry
Data_Type Name_Ast::get_data_type()
{
	return node_data_type;
}

void Name_Ast::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
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
	{	// if type is int or float, then continue, otherwise throw an error
		if (loc_var_val->get_result_enum() == int_result)
		{
			file_buffer << std::setprecision(0)<<(int)loc_var_val->get_value() << "\n";
			//file_buffer << loc_var_val->get_value() << "\n";
			//file_buffer << loc_var_val->get_value() ;
		}
		else if(loc_var_val->get_result_enum() == float_result)
		{
			//char temp[10];
			//sprintf(temp, "%.2f\n",loc_var_val->get_value()); 			
			//sprintf(temp, "%.2f",loc_var_val->get_value());
			//string str = string(temp);
			//file_buffer << str;
/*			if(loc_var_val->get_value() == 0)
			{
				file_buffer << std::setprecision(0) << (int)loc_var_val->get_value() << "\n";
			}
			else
			{
				file_buffer << std::setprecision(2) << loc_var_val->get_value() << "\n";
			}
*/
			file_buffer << std::setprecision(2) << loc_var_val->get_value() << "\n";

		}
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
				//file_buffer << glob_var_val->get_value() << "\n";
				file_buffer << std::setprecision(0) << (int)glob_var_val->get_value() << "\n";
		}
		else if(glob_var_val->get_result_enum() == float_result)
		{
			if (glob_var_val == NULL)
				file_buffer << "0.00\n";				// check as to what is being printed here in sir's eval ****************
				//file_buffer << "0.00";				// check as to what is being printed here in sir's eval ****************
			else
			{
				//char temp[10];
				//sprintf(temp, "%.2f\n",glob_var_val->get_value()); 			
				//sprintf(temp, "%.2f",glob_var_val->get_value());
				//string str = string(temp);
				//file_buffer << str;

/*				if(glob_var_val->get_value() == 0)
				{
					file_buffer << std::setprecision(0) << (int)glob_var_val->get_value() << "\n";
				}
				else
				{
					file_buffer << std::setprecision(2) << glob_var_val->get_value() << "\n";
				}
*/
				file_buffer << std::setprecision(2) << glob_var_val->get_value() << "\n";			
			
				//file_buffer << glob_var_val->get_value() << "\n";
			}
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
	//cout<< "In get_value_of_evaluation of Name_Ast\n";
	// here check what happens in the case, if variable is present in global scope and in local scope both
	if (eval_env.does_variable_exist(variable_name))
	{
		Eval_Result * result = eval_env.get_variable_value(variable_name);
// wrong because it changes in symbol_table		
/*
		if(get_data_type() == int_data_type)
		{
			result->set_result_enum(int_result);
		}
		else if(get_data_type() == float_data_type || get_data_type() == double_data_type)
		{
			result->set_result_enum(float_result);
		}
*/		
		return *result;
	}

	Eval_Result * result = interpreter_global_table.get_variable_value(variable_name);
/*
	if(get_data_type() == int_data_type)
	{
		result->set_result_enum(int_result);
	}
	else if(get_data_type() == float_data_type || get_data_type() == double_data_type)
	{
		result->set_result_enum(float_result);
	}
*/	
	return *result;
}

// the argumnts are result and a local environment
// if the type of the result is int, then a new variable of eval_result_value is created and assigned this value
// if the passed local environment has this variable, then this new variable i, along with the variable name is put in the passed environment
// otherwise it is put intointerpreter global table
void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	// have to change here, because i we have to decide on the basis of LHS and not rhs as to what should our value be

	Eval_Result_Value * i;
/*	if (result.get_result_enum() == int_result)
	{
		i = new Eval_Result_Value_Int();
	 	i->set_value((int)result.get_value());
	}																
	// for float we will add similar things
	else if(result.get_result_enum() == float_result)
	{
		i = new Eval_Result_Value_Float();
		i->set_value(result.get_value());
	}
*/

	if(get_data_type() == int_data_type)
	{
		i = new Eval_Result_Value_Int();
	 	i->set_value(result.get_value());
	}	
	else if(get_data_type() == float_data_type || get_data_type() == double_data_type)
	{
		i = new Eval_Result_Value_Float();
		i->set_value(result.get_value());
	}
		
	if (eval_env.does_variable_exist(variable_name))
		eval_env.put_variable_value(*i, variable_name);
	else
		interpreter_global_table.put_variable_value(*i, variable_name);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	//cout << "in evaluate of Int, Name of variable is "<< variable_name <<"\n";
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
void Number_Ast<DATA_TYPE>::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::print_ast(ostream & file_buffer)
{
	if(get_data_type() == int_data_type)
	{
		//file_buffer << "Num : " << constant;
		file_buffer << "Num : " << std::setprecision(0) << (int)constant;
	}
	else if(get_data_type() == float_data_type || get_data_type() == double_data_type)
	{
		//char temp[100];
		//sprintf(temp, "Num : %.2f",(double)constant);
		//string str = string(temp);
		//file_buffer << str;
/*		if(constant == 0)
		{
			file_buffer << "Num : " << std::setprecision(0) << constant;		
		}
		else
		{
*/
			file_buffer << "Num : " << std::setprecision(2) << constant;
//		}
	}
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if (node_data_type == int_data_type)
	{
		Eval_Result & result = *new Eval_Result_Value_Int();			// * is for dereferencing the pointer
		result.set_value(constant);

		return result;
	}
	// I think if we have to add functionality for float, then we have to add like this only 
	else if(node_data_type == float_data_type || node_data_type == double_data_type)
	{
		Eval_Result & result = * new Eval_Result_Value_Float();
		result.set_value(constant);
		
		return result;
	
	}
}

///////////////////////////////////////////////////////////////////////////////

Return_Ast::Return_Ast()
{
	return_value = NULL;
}

Return_Ast::Return_Ast(Ast * temp)
{
	return_value = temp;
}

Return_Ast::~Return_Ast()
{}

void Return_Ast::print_ast(ostream & file_buffer)
{
	if(return_value ==NULL)
	{
		file_buffer <<"\n"<< AST_SPACE << "RETURN <NOTHING>\n\n";
		//file_buffer<< AST_SPACE << "RETURN <NOTHING>\n\n";
	}
	else
	{
		file_buffer <<"\n"<< AST_SPACE << "RETURN ";
		//file_buffer <<AST_SPACE << "RETURN ";
		return_value->print_ast(file_buffer);
		file_buffer <<"\n\n";
	}
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	
	if(return_value == NULL)
	{	
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_variable_status(true);
		
		// here also modify it from void_result to something else
		result.set_result_enum(void_result);
//		result.set_result_enum(stop_execution);
		print_ast(file_buffer);
		result.set_execution_status(true);
		return result;
	}
	else
	{
		Eval_Result & result = return_value->evaluate(eval_env, file_buffer);
		print_ast(file_buffer);
		result.set_execution_status(true);
		//result.set_result_enum(void_result);
		//result.set_result_enum(stop_execution);
		return result;
	}
}

template class Number_Ast<int>;
template class Number_Ast<float>;

///////////////////////////////////////////////////////////////////////////////
Relational_Ast::Relational_Ast(Ast * temp_lhs, RELATIONAL_OP temp_op, Ast * temp_rhs)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
	op = temp_op;
}

Relational_Ast::~Relational_Ast()
{
	delete lhs;
	delete rhs;
}

Data_Type Relational_Ast::get_data_type()
{
	return node_data_type;
}

void Relational_Ast::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
}

bool Relational_Ast::check_ast(int line)
{
	// this is there because in many cfg files in relational arith we have float on LHS and 0 on RHS and it is not giving error
/*	if(lhs->get_data_type() == float_data_type || lhs->get_data_type() == double_data_type)
	{
		//node_data_type = lhs->get_data_type();
		node_data_type = int_data_type;
		return true;
	}
*/
 
 	
/*	if(rhs->get_data_type() == float_data_type || rhs->get_data_type() == double_data_type)
	{
		node_data_type = rhs->get_data_type();
		return true;
	}
*/
	if(lhs->get_data_type() == rhs->get_data_type() )
	{
		//node_data_type = lhs->get_data_type();
		node_data_type = int_data_type;
		return true;
	}

	report_error("Relational statement data type not compatible", line);
}

void Relational_Ast::print_ast(ostream & file_buffer)
{
	file_buffer <<"\n"<< REL_SPACE << "Condition: ";
	switch(op)
	{
		case 0:	file_buffer << "EQ\n";
				break;
		case 1:	file_buffer << "GE\n";
				break;
		case 2:	file_buffer << "GT\n";
				break;
		case 3:	file_buffer << "LE\n";
				break;
		case 4:	file_buffer << "LT\n";
				break;
		case 5:	file_buffer << "NE\n";
				break;
	}
	
	file_buffer << REL_NODE_SPACE << "LHS (";			
	lhs->print_ast(file_buffer);						// calling the print_ast function on LHS
	file_buffer << ")\n";

	file_buffer << REL_NODE_SPACE << "RHS (";
	rhs->print_ast(file_buffer);						// calling the print_ast function on RHS
	file_buffer << ")";
}

// not sure whether the following will work correctly

Eval_Result & Relational_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// so get the evaluated result of RHS and LHS and then compare them and return the result
	Eval_Result & i = lhs->evaluate(eval_env, file_buffer);
	
	Eval_Result & j = rhs->evaluate(eval_env, file_buffer);

	if(i.is_variable_defined() == false)
	{	
		report_error("variable should be defined to be used in Relational operation", NOLINE);
	}
	else if(j.is_variable_defined() == false)
	{
		report_error("variable should be defined to be used in Relational operation", NOLINE);
	}
	
	Eval_Result * result = new Eval_Result_Value_Int();	
	
	// printing
	// so now i and j has the evaluation result of rhs and lhs
	// EQ, GE, GT, LE, LT, NE
	switch(op)
	{
		case 0:
			if(i.get_value() == j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}
			break;
		case 1:
			if(i.get_value() >= j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}		
			break;
		case 2:
			if(i.get_value() > j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}
			break;
		case 3:
			if(i.get_value() <= j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}		
			break;
		case 4:
			if(i.get_value() < j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}		
			break;
		case 5:
			if(i.get_value() != j.get_value() )
			{
				result->set_value(1);
				result->set_variable_status(true);
			}
			else
			{
				result->set_value(0);
				result->set_variable_status(true);
			}		
			break;
		default:
			report_error("Only 6 operators were allowed", NOLINE);
			break;
	}
	//print_ast(file_buffer);
	return *result;
	// result has 1 if the condition is true otherwise it has 0, this will be used by either by evaluate of assignment or evaluate of conditional
}

//////////////////////////////////////////////////////////////////////////
Arithmetic_Ast::Arithmetic_Ast(Ast* temp_lhs, ARITHMETIC_OP temp_op, Ast* temp_rhs)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
	op = temp_op;
}

Arithmetic_Ast::~Arithmetic_Ast()
{
	delete lhs;	
	delete rhs;
}

void Arithmetic_Ast::print_ast(ostream & file_buffer)
{
	file_buffer <<"\n"<< REL_SPACE << "Arith: ";
	switch(op)
	{
		case 0:	file_buffer << "PLUS\n";
				break;
		case 1:	file_buffer << "MINUS\n";
				break;
		case 2:	file_buffer << "MULT\n";
				break;
		case 3:	file_buffer << "DIV\n";
				break;
		case 4:	file_buffer << "UMINUS\n";
				break;
	}
	
	file_buffer << REL_NODE_SPACE << "LHS (";			
	lhs->print_ast(file_buffer);						// calling the print_ast function on LHS
	file_buffer << ")";

	if(op != UMINUS)
	{
		file_buffer <<"\n"<< REL_NODE_SPACE << "RHS (";
		rhs->print_ast(file_buffer);						// calling the print_ast function on RHS
		file_buffer << ")";
	}
}

Data_Type Arithmetic_Ast::get_data_type()
{
	return node_data_type;
}

void Arithmetic_Ast::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
}

bool Arithmetic_Ast::check_ast(int line)
{
	if(op == ARITHMETIC_OP::UMINUS)
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

	// The following 2 if conditions are for handling the use of double and float with each other
	if(lhs->get_data_type() == float_data_type && rhs->get_data_type() == double_data_type)
	{
		node_data_type = float_data_type;
		return true;
	}

	if(rhs->get_data_type() == float_data_type && lhs->get_data_type() == double_data_type)
	{
		node_data_type = float_data_type;
		return true;
	}


	if(lhs->get_data_type() == rhs->get_data_type() )
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

	report_error("Arithmetic statement data type not compatible", line);
}

Eval_Result & Arithmetic_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & i = lhs->evaluate(eval_env, file_buffer);
//	cout<<"REaching here, op is "<<op<<endl;
	
	// this line here gives error
	//Eval_Result & j  = rhs->evaluate(eval_env, file_buffer);
//	cout<<"REaching here, op is "<<op<<endl;

	Eval_Result * j;
	if(rhs !=NULL)
	{
		j = &rhs->evaluate(eval_env, file_buffer);
	}
	
	
	if(i.is_variable_defined() == false)
	{	
		report_error("variable should be defined to be used in Arithmetic operation", NOLINE);
	}
	else if(rhs !=NULL && j->is_variable_defined() == false)
	{
		report_error("variable should be defined to be used in Arithmetic operation", NOLINE);
	}
	
	Eval_Result * result;
	
	// here initially we were printing using result_enum, but now we are printing using lhs->get_data_type
	if(lhs->get_data_type() == int_data_type)
	{
		result = new Eval_Result_Value_Int();
		switch(op)
		{
			case 0:
				result->set_value((int)((int)i.get_value() + (int)j->get_value()));
				break;
			case 1:
				result->set_value((int)((int)i.get_value() - (int)j->get_value()));
				break;
			case 2:
				result->set_value((int)((int)i.get_value() * (int)j->get_value()));
				break;
			case 3:
				if(j->get_value() == 0)
				{
					report_error("Divide by 0", NOLINE);
				}
				result->set_value((int)((int)i.get_value() / (int)j->get_value()));
				break;
			case 4:
				result->set_value( - (int)i.get_value() );
				break;
			default:
				report_error("Only 5 operators defined", NOLINE);
				break;	
		}
	}
	else if(lhs->get_data_type() == float_data_type || lhs->get_data_type() == double_data_type)
	{
		result = new Eval_Result_Value_Float();
		switch(op)
		{
			case 0:
				result->set_value((double)(i.get_value() + j->get_value() ) );
				break;
			case 1:
				result->set_value((double)(i.get_value() - j->get_value()));
				break;
			case 2:
				result->set_value((double)(i.get_value() * j->get_value()));
				break;
			case 3:
				if(j->get_value() == 0)
				{
					report_error("Divide by 0", NOLINE);
				}
				result->set_value((double)(i.get_value() / j->get_value()));
				break;
			case 4:
				result->set_value( - (double)i.get_value() );
				break;
			default:
				report_error("Only 5 operators defined", NOLINE);
				break;	
		}
	}
	
	return * result;
}

//////////////////////////////////////////////////////////////////////////
GoTo_Ast::GoTo_Ast(Ast * a)
{
	child = a;
}

GoTo_Ast::~GoTo_Ast()
{
	delete child;
}

void GoTo_Ast::print_ast(ostream & file_buffer)
{
	file_buffer <<"\n"<< AST_SPACE<<"Goto statement:\n"<< AST_NODE_SPACE;
	child->print_ast(file_buffer);
}

Eval_Result & GoTo_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = child->evaluate(eval_env, file_buffer);
	file_buffer<<endl;
	print_ast(file_buffer);
	//file_buffer << "\n" << AST_SPACE<<"GOTO (BB "<< result.get_value()<<")\n";
	file_buffer << "\n" << AST_SPACE<<"GOTO (BB "<< std::setprecision(0) << (int)result.get_value()<<")\n";
	return result;
}


//////////////////////////////////////////////////////////////////////////
Conditional_Ast::Conditional_Ast(Ast * temp_condition, Ast * a, Ast * b)
{
	condition = temp_condition;
	trueSuccessor = a;
	falseSuccessor = b;
}

Conditional_Ast::~Conditional_Ast()
{
	delete condition;
	delete trueSuccessor;
	delete falseSuccessor;
}

void Conditional_Ast::print_ast(ostream & file_buffer)
{
	file_buffer <<"\n"<< AST_SPACE << "If_Else statement:";
	condition->print_ast(file_buffer);
	file_buffer << "\n" << AST_NODE_SPACE << "True ";
	trueSuccessor->print_ast(file_buffer);
	file_buffer << "\n" << AST_NODE_SPACE << "False ";
	falseSuccessor->print_ast(file_buffer);
}

Eval_Result & Conditional_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// condition->evaluate() will return an eval which has value 1 or 0, now if value is 0, then condition is false otherwise true
	// now based on the value, (accessible using get_value() ), I will decide which will be the successor of this block
	// Either trueSuccessor or falseSuccessor Ast will be used. Using that calculate the block no. of the next block
	// Now we can set the "value" of the eval_result to be that basic block number, and then in the basic block procedure we will use that result
	// conditional statement is a statement in the statement list of the block
	// If the "is_conditional" variable is set to true, then assume that "value" stores the block number of the next block
	//print_ast(file_buffer);
	file_buffer <<"\n"<< AST_SPACE << "If_Else statement:";
	condition->print_ast(file_buffer);

	Eval_Result & temp = condition->evaluate(eval_env, file_buffer);

	file_buffer << "\n" << AST_NODE_SPACE << "True ";
	trueSuccessor->print_ast(file_buffer);
	file_buffer << "\n" << AST_NODE_SPACE << "False ";
	falseSuccessor->print_ast(file_buffer);
	
	//Eval_Result * result = new Eval_Result_Value_Int();
	Eval_Result * result ;
	file_buffer<<endl;
	// in relational , we set the value of the condition as 1 if the condition was true, else 0
	if(temp.get_value() == 1)
	{
		result = &(trueSuccessor->evaluate(eval_env, file_buffer) );
		//file_buffer << "\n" << AST_SPACE << "Condition True : Goto (BB "<<result->get_value()<<")\n";
		file_buffer << "\n" << AST_SPACE << "Condition True : Goto (BB "<<std::setprecision(0) << (int)result->get_value()<<")\n";
	}
	else
	{
		result = &(falseSuccessor->evaluate(eval_env, file_buffer) );
		//file_buffer << "\n" << AST_SPACE << "Condition False : Goto (BB "<<result->get_value()<<")\n";
		file_buffer << "\n" << AST_SPACE << "Condition False : Goto (BB "<<std::setprecision(0) << (int)result->get_value()<<")\n";
	}
	// "defined" is false if we have to go to some block, whereas after asignment or regular statement it will be true to indicate that we have to follow the normal flow
	return *result;
	//return condition->evaluate(eval_env, file_buffer);
}

///////////////////////////////////////////////////////////
Function_call_Ast::Function_call_Ast(string name, Data_Type data_type)
{
	func_name = name;
	node_data_type = data_type;
}

Function_call_Ast::Function_call_Ast(string name, list <Ast *> t, Data_Type data_type)
{
	func_name = name;
	par = t;
	node_data_type = data_type;
}

Function_call_Ast::~Function_call_Ast()
{}

void Function_call_Ast::set_data_type(Data_Type data_type)
{
	node_data_type = data_type;
}

Data_Type Function_call_Ast::get_data_type()
{
	return node_data_type;
}

void Function_call_Ast::print_ast(ostream & file_buffer)
{
	//file_buffer << AST_SPACE << "FN CALL: "<<func_name <<"(";
	file_buffer <<"\n" << AST_SPACE << "FN CALL: "<<func_name <<"(";
	list<Ast *>::iterator itr;
	if(!par.empty() )
	{
		for(itr = par.begin();itr!=par.end();itr++)
		{
			file_buffer << "\n" << AST_NODE_SPACE;
			(*itr)->print_ast(file_buffer);
		}
	}
	file_buffer <<")";
}

Eval_Result & Function_call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// dummy code
	//cout<<"in function's evaluate\n";
	
	Procedure * proc = program_object.get_procedure(func_name);	
	return proc->evaluate(eval_env, file_buffer, par);
	// have to write the code for eval here
	// what eval should do is, it should execute the called function's evaluate with the given parameter's value set in the evaluation environment(put the value of the passed argument in the environment using interpreter_global_table.put_value() function)

	// when this function is called, the global variables will already have been assigned value & so only
	// so we will just have to put the value for the passed arguments in the eval_env by using put_variable_value function, then do what was done in the evaluate function of the procedure

	// put arguments in eval_environment
	// so if a variable is passed, then we have to store its value, now how should we get value for a variable
	// so basically call evaluate on all the passed arguments and then call the evaluate of the procedure

	

}

//////////////////////////////////////////////////////////////////////////
successor::successor(int a)
{
	n = a;
}

successor::~successor()
{}

/*
int successor::get_successor()
{
	return n;
}
*/

void successor::print_ast(ostream & file_buffer)
{
	//file_buffer << AST_NODE_SPACE << "Successor: "<<n;
	file_buffer  << "Successor: "<<n;
}

Eval_Result & successor::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// here we are setting the variable status to false, and then setting the next block no. as the value attribute of the result
	// in procedure.cc's evaluate we check the status of the variable_defined_status of the variable and then check on its basis
	Eval_Result & result = *new Eval_Result_Value_Int();
	result.set_value(n);
	//result.set_variable_status(false);
	result.set_conditional(true);
	return result;
}
