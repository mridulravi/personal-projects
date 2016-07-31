
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
#include<typeinfo>

using namespace std;

#include"common-classes.hh"
#include"error-display.hh"
#include"user-options.hh"
#include"local-environment.hh"
#include"icode.hh"
#include"reg-alloc.hh"
#include"symbol-table.hh"
#include"ast.hh"
#include"basic-block.hh"
#include"procedure.hh"
#include"program.hh"

Ast::Ast()
{}

Ast::~Ast()
{}

bool Ast::check_ast()
{
	stringstream msg;
	msg << "No check_ast() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Data_Type Ast::get_data_type()
{
	stringstream msg;
	msg << "No get_data_type() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Symbol_Table_Entry & Ast::get_symbol_entry()
{
	stringstream msg;
	msg << "No get_symbol_entry() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	stringstream msg;
	msg << "No print_value() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	stringstream msg;
	msg << "No get_value_of_evaluation() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	stringstream msg;
	msg << "No set_value_of_evaluation() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register)
{
	stringstream msg;
	msg << "No create_store_stmt() function for " << typeid(*this).name();
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, msg.str());
}

////////////////////////////////////////////////////////////////

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;

	ast_num_child = binary_arity;
	node_data_type = void_data_type;

	lineno = line;
}

Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

bool Assignment_Ast::check_ast()
{
	CHECK_INVARIANT((rhs != NULL), "Rhs of Assignment_Ast cannot be null");
	CHECK_INVARIANT((lhs != NULL), "Lhs of Assignment_Ast cannot be null");

	if (lhs->get_data_type() == rhs->get_data_type())
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, 
		"Assignment statement data type not compatible");
}

void Assignment_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n" << AST_SPACE << "Asgn:";

	file_buffer << "\n" << AST_NODE_SPACE << "LHS (";
	lhs->print(file_buffer);
	file_buffer << ")";

	file_buffer << "\n" << AST_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);
	file_buffer << ")";
}

Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	CHECK_INVARIANT((rhs != NULL), "Rhs of Assignment_Ast cannot be null");
	Eval_Result & result = rhs->evaluate(eval_env, file_buffer);

	CHECK_INPUT_AND_ABORT(result.is_variable_defined(), "Variable should be defined to be on rhs of Assignment_Ast", lineno);

	CHECK_INVARIANT((lhs != NULL), "Lhs of Assignment_Ast cannot be null");

	lhs->set_value_of_evaluation(eval_env, result);

	// Print the result

	print(file_buffer);

	lhs->print_value(eval_env, file_buffer);

	return result;
}

Code_For_Ast & Assignment_Ast::compile()
{
	/* 
		An assignment x = y where y is a variable is 
		compiled as a combination of load and store statements:
		(load) R <- y 
		(store) x <- R
		If y is a constant, the statement is compiled as:
		(imm_Load) R <- y 
		(store) x <- R
		where imm_Load denotes the load immediate operation.
	*/

	CHECK_INVARIANT((lhs != NULL), "Lhs cannot be null");
	CHECK_INVARIANT((rhs != NULL), "Rhs cannot be null");

	Code_For_Ast & load_stmt = rhs->compile();

	Register_Descriptor * load_register = load_stmt.get_reg();

	Code_For_Ast store_stmt = lhs->create_store_stmt(load_register);

	// Store the statement in ic_list

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;

	if (load_stmt.get_icode_list().empty() == false)
		ic_list = load_stmt.get_icode_list();

	if (store_stmt.get_icode_list().empty() == false)
		ic_list.splice(ic_list.end(), store_stmt.get_icode_list());

	Code_For_Ast * assign_stmt;
	if (ic_list.empty() == false)
		assign_stmt = new Code_For_Ast(ic_list, load_register);

	return *assign_stmt;
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	CHECK_INVARIANT((lhs != NULL), "Lhs cannot be null");
	CHECK_INVARIANT((rhs != NULL), "Rhs cannot be null");

	// error when both lra and icode are used comes due to this line
	lra.optimize_lra(mc_2m, lhs, rhs);
	
	Code_For_Ast load_stmt = rhs->compile_and_optimize_ast(lra);

	Register_Descriptor * result_register = load_stmt.get_reg();

	Code_For_Ast store_stmt = lhs->create_store_stmt(result_register);

	list<Icode_Stmt *> ic_list;

	if (load_stmt.get_icode_list().empty() == false)
		ic_list = load_stmt.get_icode_list();

	if (store_stmt.get_icode_list().empty() == false)
		ic_list.splice(ic_list.end(), store_stmt.get_icode_list());

	Code_For_Ast * assign_stmt;
	if (ic_list.empty() == false)
		assign_stmt = new Code_For_Ast(ic_list, result_register);

	return *assign_stmt;
}

/////////////////////////////////////////////////////////////////

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line)
{
	variable_symbol_entry = &var_entry;

	CHECK_INVARIANT((variable_symbol_entry->get_variable_name() == name),
		"Variable's symbol entry is not matching its name");

	ast_num_child = zero_arity;
	node_data_type = variable_symbol_entry->get_data_type();
	lineno = line;
}

Name_Ast::~Name_Ast()
{}

Data_Type Name_Ast::get_data_type()
{
	return variable_symbol_entry->get_data_type();
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry()
{
	return *variable_symbol_entry;
}

void Name_Ast::print(ostream & file_buffer)
{
	file_buffer << "Name : " << variable_symbol_entry->get_variable_name();
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	string variable_name = variable_symbol_entry->get_variable_name();

	Eval_Result * loc_var_val = eval_env.get_variable_value(variable_name);
	Eval_Result * glob_var_val = interpreter_global_table.get_variable_value(variable_name);

	file_buffer << "\n" << AST_SPACE << variable_name << " : ";

	if (!eval_env.is_variable_defined(variable_name) && !interpreter_global_table.is_variable_defined(variable_name))
		file_buffer << "undefined";

	else if (eval_env.is_variable_defined(variable_name) && loc_var_val != NULL)
	{
		CHECK_INVARIANT(loc_var_val->get_result_enum() == int_result, "Result type can only be int");
		file_buffer << loc_var_val->get_int_value() << "\n";
	}

	else
	{
		CHECK_INVARIANT(glob_var_val->get_result_enum() == int_result, 
			"Result type can only be int and float");

		if (glob_var_val == NULL)
			file_buffer << "0\n";
		else
			file_buffer << glob_var_val->get_int_value() << "\n";
	}
	file_buffer << "\n";
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	string variable_name = variable_symbol_entry->get_variable_name();

	if (eval_env.does_variable_exist(variable_name))
	{
		CHECK_INPUT_AND_ABORT((eval_env.is_variable_defined(variable_name) == true), 
					"Variable should be defined before its use", lineno);

		Eval_Result * result = eval_env.get_variable_value(variable_name);
		return *result;
	}

	CHECK_INPUT_AND_ABORT((interpreter_global_table.is_variable_defined(variable_name) == true), 
				"Variable should be defined before its use", lineno);

	Eval_Result * result = interpreter_global_table.get_variable_value(variable_name);
	return *result;
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	Eval_Result * i;
	string variable_name = variable_symbol_entry->get_variable_name();

	if (variable_symbol_entry->get_data_type() == int_data_type)
		i = new Eval_Result_Value_Int();
	else
		CHECK_INPUT_AND_ABORT(CONTROL_SHOULD_NOT_REACH, "Type of a name can be int/float only", lineno);

	if (result.get_result_enum() == int_result)
	 	i->set_value(result.get_int_value());
	else
		CHECK_INPUT_AND_ABORT(CONTROL_SHOULD_NOT_REACH, "Type of a name can be int/float only", lineno);

	if (eval_env.does_variable_exist(variable_name))
		eval_env.put_variable_value(*i, variable_name);
	else
		interpreter_global_table.put_variable_value(*i, variable_name);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	return get_value_of_evaluation(eval_env);
}

Code_For_Ast & Name_Ast::compile()
{
	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);
	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	Ics_Opd * register_opd = new Register_Addr_Opd(result_register);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(load, opd, register_opd);

	list<Icode_Stmt *> ic_list;
	ic_list.push_back(load_stmt);

	Code_For_Ast & load_code = *new Code_For_Ast(ic_list, result_register);

	return load_code;
}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register)
{
	CHECK_INVARIANT((store_register != NULL), "Store register cannot be null");

	Ics_Opd * register_opd = new Register_Addr_Opd(store_register);
	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);

	Icode_Stmt * store_stmt = new Move_IC_Stmt(store, register_opd, opd);

	if (command_options.is_do_lra_selected() == false)
		variable_symbol_entry->free_register(store_register);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	ic_list.push_back(store_stmt);

	Code_For_Ast & name_code = *new Code_For_Ast(ic_list, store_register);

	return name_code;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;;

	bool load_needed = lra.is_load_needed();

	Register_Descriptor * result_register = lra.get_register();
	CHECK_INVARIANT((result_register != NULL), "Register cannot be null");
	Ics_Opd * register_opd = new Register_Addr_Opd(result_register);

	Icode_Stmt * load_stmt = NULL;
	if (load_needed)
	{
		Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);

		load_stmt = new Move_IC_Stmt(load, opd, register_opd);
			
		ic_list.push_back(load_stmt);
	}

	Code_For_Ast & load_code = *new Code_For_Ast(ic_list, result_register);

	return load_code;
}

///////////////////////////////////////////////////////////////////////////////

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::Number_Ast(DATA_TYPE number, Data_Type constant_data_type, int line)
{
	constant = number;
	node_data_type = constant_data_type;

	ast_num_child = zero_arity;

	lineno = line;
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
void Number_Ast<DATA_TYPE>::print(ostream & file_buffer)
{
	file_buffer << std::fixed;
	file_buffer << std::setprecision(2);

	file_buffer << "Num : " << constant;
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if (node_data_type == int_data_type)
	{
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_value(constant);

		return result;
	}
}

template <class DATA_TYPE>
Code_For_Ast & Number_Ast<DATA_TYPE>::compile()
{
	Register_Descriptor * result_register = machine_dscr_object.get_new_register();
	CHECK_INVARIANT((result_register != NULL), "Result register cannot be null");
	Ics_Opd * load_register = new Register_Addr_Opd(result_register);
	Ics_Opd * opd = new Const_Opd<int>(constant);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(imm_load, opd, load_register);

	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	ic_list.push_back(load_stmt);

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, result_register);

	return num_code;
}

template <class DATA_TYPE>
Code_For_Ast & Number_Ast<DATA_TYPE>::compile_and_optimize_ast(Lra_Outcome & lra)
{
	CHECK_INVARIANT((lra.get_register() != NULL), "Register assigned through optimize_lra cannot be null");
	Ics_Opd * load_register = new Register_Addr_Opd(lra.get_register());
	Ics_Opd * opd = new Const_Opd<int>(constant);

	Icode_Stmt * load_stmt = new Move_IC_Stmt(imm_load, opd, load_register);

	list<Icode_Stmt *> ic_list;
	ic_list.push_back(load_stmt);

	Code_For_Ast & num_code = *new Code_For_Ast(ic_list, lra.get_register());

	return num_code;
}

///////////////////////////////////////////////////////////////////////////////

Return_Ast::Return_Ast(int line)
{
	lineno = line;
	node_data_type = void_data_type;
	ast_num_child = zero_arity;
}

Return_Ast::~Return_Ast()
{}

void Return_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n" << AST_SPACE << "Return <NOTHING>\n";
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = *new Eval_Result_Value_Int();
	return result;
}

Code_For_Ast & Return_Ast::compile()
{
	Code_For_Ast & ret_code = *new Code_For_Ast();
	return ret_code;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	Code_For_Ast & ret_code = *new Code_For_Ast();
	return ret_code;
}

template class Number_Ast<int>;

// have to add lineno in the default constructor

////////////////////////////////////////////////////////////////////////////////////////////

Relational_Ast::Relational_Ast(Ast * temp_lhs, RELATIONAL_OP temp_op, Ast * temp_rhs, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
	op = temp_op;
	
	lineno = line;
	ast_num_child = binary_arity;
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

bool Relational_Ast::check_ast()
{
	if(lhs->get_data_type() == rhs->get_data_type() )
	{
		node_data_type = lhs->get_data_type();
		return true;
	}

//	report_error("Relational statement data type not compatible", line);
	CHECK_INPUT_AND_ABORT(false, "Relational statement data type not compatible", lineno);
}


void Relational_Ast::print(ostream & file_buffer)
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
	lhs->print(file_buffer);						// calling the print_ast function on LHS
	file_buffer << ")\n";

	file_buffer << REL_NODE_SPACE << "RHS (";
	rhs->print(file_buffer);						// calling the print_ast function on RHS
	file_buffer << ")";
}


Eval_Result & Relational_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// so get the evaluated result of RHS and LHS and then compare them and return the result
	Eval_Result & i = lhs->evaluate(eval_env, file_buffer);
	Eval_Result & j = rhs->evaluate(eval_env, file_buffer);

	if(i.is_variable_defined() == false)
	{	
//		report_error("variable should be defined to be used in Relational operation", NOLINE);
		CHECK_INPUT_AND_ABORT(false, "variable should be defined to be used in Relational operation",lineno);
	}
	else if(j.is_variable_defined() == false)
	{
//		report_error("variable should be defined to be used in Relational operation", NOLINE);
		CHECK_INPUT_AND_ABORT(false, "variable should be defined to be used in Relational operation", lineno);
	}
	
	Eval_Result * result = new Eval_Result_Value_Int();	
	
	// so now i and j has the evaluation result of rhs and lhs
	// EQ, GE, GT, LE, LT, NE
	switch(op)
	{
		case 0:
			if(i.get_int_value() == j.get_int_value() )
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
			if(i.get_int_value() >= j.get_int_value() )
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
			if(i.get_int_value() > j.get_int_value() )
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
			if(i.get_int_value() <= j.get_int_value() )
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
			if(i.get_int_value() < j.get_int_value() )
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
			if(i.get_int_value() != j.get_int_value() )
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
			//report_error("Only 6 operators were allowed", NOLINE);
			CHECK_INPUT_AND_ABORT(false, "Only 6 operators are allowed",lineno);
			break;
	}
	return *result;
	// result has 1 if the condition is true otherwise it has 0, this will be used by either by evaluate of assignment or evaluate of conditional
}

Code_For_Ast & Relational_Ast::compile()
{
	/* 
		now i have to think about, how will i compile a relational condition
		i should compile the lhs and rhs individually, and then use the new IC instruction, Relational_IC_Stmt (like move), for it
	*/

	// here the result of both should be in different registers, how to ensure that
	Code_For_Ast & stmt1 = lhs->compile();
	
	Register_Descriptor * o1 = stmt1.get_reg();
	o1->update_symbol_information(* new Symbol_Table_Entry() );
	
	Ics_Opd * op1 = new Register_Addr_Opd(o1);
	
	Code_For_Ast & stmt2 = rhs->compile();

	Register_Descriptor * o2 = stmt2.get_reg();
	o2->update_symbol_information(* new Symbol_Table_Entry() );
	
	Ics_Opd * op2 = new Register_Addr_Opd(o2);

	list<Icode_Stmt *> ic_list = * new list<Icode_Stmt *>;
	
	if(stmt1.get_icode_list().empty() == false)
	{
		ic_list = stmt1.get_icode_list();
	}

	if(stmt2.get_icode_list().empty() == false)
	{
		ic_list.splice(ic_list.end(), stmt2.get_icode_list() );
	}

	Ics_Opd * res = new Register_Addr_Opd(machine_dscr_object.get_new_register() );

	Icode_Stmt * stmt;

	// The operands in Relational_IC_Stmt constructor are Ics_Opd and not register_descriptors 

	switch(op)
	{
		case RELATIONAL_OP::EQ:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(seq, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::GE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sge, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::GT:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sgt, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::LE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sle, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::LT:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(slt, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::NE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sne, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		default:
			{
				CHECK_INPUT_AND_ABORT(false, "Only 6 operators are allowed", lineno);
				break;
			}

	}
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list, machine_dscr_object.get_new_register() );
	}

	// just check one thing that whether we have to free that registers o1 and o2 or not
	o1->clear_lra_symbol_list();
	o2->clear_lra_symbol_list();

	return * code;
}

Code_For_Ast & Relational_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	Code_For_Ast & stmt1 = lhs->compile_and_optimize_ast(lra);
	
	Register_Descriptor * o1 = stmt1.get_reg();
//	o1->update_symbol_information(* new Symbol_Table_Entry() );
	
	Ics_Opd * op1 = new Register_Addr_Opd(o1);
	
	Code_For_Ast & stmt2 = rhs->compile_and_optimize_ast(lra);

	Register_Descriptor * o2 = stmt2.get_reg();
//	o2->update_symbol_information(* new Symbol_Table_Entry() );
	
	Ics_Opd * op2 = new Register_Addr_Opd(o2);

	list<Icode_Stmt *> ic_list = * new list<Icode_Stmt *>;
	
	if(stmt1.get_icode_list().empty() == false)
	{
		ic_list = stmt1.get_icode_list();
	}

	if(stmt2.get_icode_list().empty() == false)
	{
		ic_list.splice(ic_list.end(), stmt2.get_icode_list() );
	}

	Ics_Opd * res = new Register_Addr_Opd(lra.get_register() );

	Icode_Stmt * stmt;

	// The operands in Relational_IC_Stmt constructor are Ics_Opd and not register_descriptors 

	switch(op)
	{
		case RELATIONAL_OP::EQ:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(seq, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::GE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sge, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::GT:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sgt, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::LE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sle, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::LT:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(slt, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		case RELATIONAL_OP::NE:
			{
				// suppose the reg r1 and r2 contains the result of lhs and rhs, then pass them as operands
				stmt = new Relational_IC_Stmt(sne, op1, op2, res );
				ic_list.push_back(stmt);
				break;
			}
		default:
			{
				CHECK_INPUT_AND_ABORT(false, "Only 6 operators are allowed", lineno);
				break;
			}

	}
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list, lra.get_register() );
	}

	// just check one thing that whether we have to free that registers o1 and o2 or not
//	o1->clear_lra_symbol_list();
//	o2->clear_lra_symbol_list();

	return * code;
}

//////////////////////////////////////////////////////////////////////////
GoTo_Ast::GoTo_Ast(Ast * a, int line)
{
	child = a;
	
	lineno = line;
	ast_num_child = unary_arity;
}

GoTo_Ast::~GoTo_Ast()
{
	delete child;
}


void GoTo_Ast::print(ostream & file_buffer)
{
	file_buffer <<"\n"<< AST_SPACE<<"Goto statement:\n"<< AST_NODE_SPACE;
	//file_buffer << AST_NODE_SPACE << "Successor: "<<successor<<endl;
	child->print(file_buffer);
}

Eval_Result & GoTo_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result & result = child->evaluate(eval_env, file_buffer);
	file_buffer<<endl;
	print(file_buffer);
	file_buffer << "\n" << AST_SPACE<<"GOTO (BB "<< result.get_int_value()<<")\n";
	return result;
}

Code_For_Ast & GoTo_Ast::compile()
{
	// child is the successor
	// we will get the next block where we should go by using evaluate on child
	ostream *file_buffer;
	Eval_Result & res = child->evaluate(*new Local_Environment(), *file_buffer);
	int label = res.get_int_value();
	
	Icode_Stmt * stmt = new Control_Flow_IC_Stmt(jump, label);
	
	list<Icode_Stmt *> ic_list = * new list<Icode_Stmt *>;
	ic_list.push_back(stmt);
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list, machine_dscr_object.get_new_register() );
	}

	return * code;	
	
}

Code_For_Ast & GoTo_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	ostream *file_buffer;
	Eval_Result & res = child->evaluate(*new Local_Environment(), *file_buffer);
	int label = res.get_int_value();
	
	Icode_Stmt * stmt = new Control_Flow_IC_Stmt(jump, label);
	
	list<Icode_Stmt *> ic_list = * new list<Icode_Stmt *>;
	ic_list.push_back(stmt);
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list, lra.get_register() );
	}

	return * code;	
}

//////////////////////////////////////////////////////////////////////////
Conditional_Ast::Conditional_Ast(Ast * temp_condition, Ast * a, Ast * b, int line)
{
	condition = temp_condition;
	trueSuccessor = a;
	falseSuccessor = b;
	
	lineno = line;
	// here i have to be careful with arity, its arity will be 1 only(condition)		-- may be wrong
	ast_num_child = unary_arity;
}

Conditional_Ast::~Conditional_Ast()
{
	delete condition;
	delete trueSuccessor;
	delete falseSuccessor;
}


void Conditional_Ast::print(ostream & file_buffer)
{
	file_buffer <<"\n"<< AST_SPACE << "If_Else statement:";
	condition->print(file_buffer);
	file_buffer << "\n" << AST_NODE_SPACE << "True ";
	trueSuccessor->print(file_buffer);
	file_buffer << "\n" << AST_NODE_SPACE << "False ";
	falseSuccessor->print(file_buffer);
}

Eval_Result & Conditional_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// condition->evaluate() will return an eval which has value 1 or 0, now if value is 0, then condition is false otherwise true
	
	// Eval_result & temp = condition->evaluate(eval_env, file_buffer)
	// now based on the value, (accessible using get_int_value() ), I will decide which will be the successor of this block
	// Either trueSuccessor or falseSuccessor Ast will be used. Using that calculate the block no. of the next block
	// Now we can set the "value" of the eval_result to be that basic block number, and then in the basic block procedure we will use that result

	// If the "defined" variable is set to false, then assume that value stores the block number of the next block
	Eval_Result & temp = condition->evaluate(eval_env, file_buffer);
	//Eval_Result * result = new Eval_Result_Value_Int();
	Eval_Result * result ;
	file_buffer<<endl;
	print(file_buffer);
	if(temp.get_int_value() == 1)
	{
		result = &(trueSuccessor->evaluate(eval_env, file_buffer) );
		file_buffer << "\n" << AST_SPACE << "Condition True : Goto (BB "<<result->get_int_value()<<")\n";
	}
	else
	{
		result = &(falseSuccessor->evaluate(eval_env, file_buffer) );
		file_buffer << "\n" << AST_SPACE << "Condition False : Goto (BB "<<result->get_int_value()<<")\n";
	}
	// "defined" is false if we have to go to some block, whereas after asignment or regular statement it will be true to indicate that we have to follow the normal flow
	return *result;
}

Code_For_Ast & Conditional_Ast::compile()
{
	Code_For_Ast & stmt1 = condition->compile();
	Register_Descriptor * reg = stmt1.get_reg();
	
	ostream * file;
	
	Eval_Result & res1 = trueSuccessor->evaluate(* new Local_Environment(), *file);
	Eval_Result & res2 = falseSuccessor->evaluate(* new Local_Environment(), *file);
	
	int label1 = res1.get_int_value();
	int label2 = res2.get_int_value();
	
	list<Icode_Stmt * > ic_list = *new list<Icode_Stmt *>;
	
	ic_list = stmt1.get_icode_list();
	
	Ics_Opd * temp = new Register_Addr_Opd(reg);
	
	Icode_Stmt * stmt = new Control_Flow_IC_Stmt(bne, temp, label1, label2);

	ic_list.push_back(stmt);
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list, machine_dscr_object.get_new_register() );
	}

	return * code;
}

Code_For_Ast & Conditional_Ast::compile_and_optimize_ast(Lra_Outcome & lra)
{
	Code_For_Ast & stmt1 = condition->compile();
	Register_Descriptor * reg = stmt1.get_reg();
	
	ostream * file;
	
	Eval_Result & res1 = trueSuccessor->evaluate(* new Local_Environment(), *file);
	Eval_Result & res2 = falseSuccessor->evaluate(* new Local_Environment(), *file);
	
	int label1 = res1.get_int_value();
	int label2 = res2.get_int_value();
	
	list<Icode_Stmt * > ic_list = *new list<Icode_Stmt *>;
	
	ic_list = stmt1.get_icode_list();
	
	Ics_Opd * temp = new Register_Addr_Opd(reg);
	
	Icode_Stmt * stmt = new Control_Flow_IC_Stmt(bne, temp, label1, label2);
	ic_list.push_back(stmt);
	
	Code_For_Ast * code;
	if(ic_list.empty() == false)
	{
		code = new Code_For_Ast(ic_list,lra.get_register() );
	}

	return * code;
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


void successor::print(ostream & file_buffer)
{
	//file_buffer << AST_NODE_SPACE << "Successor: "<<n;
	file_buffer  << "Successor: "<<n;
}

Eval_Result & successor::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{

	// completely wrong, but let it be for the moment
	Eval_Result & result = *new Eval_Result_Value_Int();
	result.set_value(n);
	result.set_variable_status(false);
	return result;
}

Code_For_Ast & successor::compile()
{
	Code_For_Ast & temp = *new Code_For_Ast();
	return temp;
}

Code_For_Ast & successor::compile_and_optimize_ast(Lra_Outcome & lra)
{
	Code_For_Ast & temp = *new Code_For_Ast();
	return temp;
}
