
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

#ifndef AST_HH
#define AST_HH

#include<string>
#include<iostream>
#include<iomanip>
#include<typeinfo>
#include<list>
#include<iomanip>

#define AST_SPACE "         "
#define AST_NODE_SPACE "            "
#define AST_SUB_NODE_SPACE "               "

#define REL_SPACE "            "			// 12 spaces
#define REL_NODE_SPACE "               "	// 15 spaces

using namespace std;

enum RELATIONAL_OP 
{
	EQ, GE, GT, LE, LT, NE
};

enum ARITHMETIC_OP
{
	PLUS, MINUS, MULT, DIV, UMINUS
};

class Ast;

class Ast
{
protected:
	typedef enum
	{
		zero_arity = 0,
		unary_arity = 1,
		binary_arity = 2
	}Ast_Arity;

	Data_Type node_data_type;
	Ast_Arity ast_num_child;

	int lineno;

public:
	Ast();
	~Ast();

	virtual Data_Type get_data_type();
	virtual bool check_ast();
	virtual Symbol_Table_Entry & get_symbol_entry();

	virtual void print(ostream & file_buffer) = 0;
	virtual void print_value(Local_Environment & eval_env, ostream & file_buffer);

	virtual Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);
	virtual void set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result);
	virtual Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer) = 0;

	virtual Code_For_Ast & compile() = 0;
	virtual Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra) = 0;
	virtual Code_For_Ast & create_store_stmt(Register_Descriptor * store_register);
	
	virtual void set_data_type(Data_Type data_type);
	
//	virtual const type_info& get_child_type();
};

class Assignment_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;

public:
	Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line);
	~Assignment_Ast();

	bool check_ast();

	void print(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
	
	Data_Type get_data_type();
	void set_data_type(Data_Type data_type);
};

class Name_Ast:public Ast
{
	Symbol_Table_Entry * variable_symbol_entry;

public:
	Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line);
	~Name_Ast();

	Data_Type get_data_type();
	Symbol_Table_Entry & get_symbol_entry();

	void print(ostream & file_buffer);

	void print_value(Local_Environment & eval_env, ostream & file_buffer);
	Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);
	void set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result);
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
	Code_For_Ast & create_store_stmt(Register_Descriptor * store_register);
	
	void set_data_type(Data_Type data_type);
};

template <class T>
class Number_Ast:public Ast
{
	T constant;

public:
	Number_Ast(T number, Data_Type constant_data_type, int line);
	~Number_Ast();

	Data_Type get_data_type();

	void print(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
	
	void set_data_type(Data_Type data_type);
};

class Return_Ast:public Ast
{

public:
	Return_Ast(int line);
	~Return_Ast();

	void print(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
};

// add classes for Relational_Ast, Conditional_Ast and GoTo_Ast
// also add compile and compile_and_optimize_ast functions for all the classes

class Relational_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	RELATIONAL_OP op;

public:
	Relational_Ast(Ast * temp_lhs, RELATIONAL_OP temp_op, Ast * temp_rhs, int line);
	~Relational_Ast();

	void print(ostream & file_buffer);
	
	Data_Type get_data_type();
	bool check_ast();
	
	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);	
	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	void set_data_type(Data_Type data_type);
};

// float variables will require a size of 8 bytes
class Arithmetic_Ast:public Ast
{
	// for Unary, give rhs as NULL 
	Ast * lhs;
	Ast * rhs;
	ARITHMETIC_OP op;
	
public:
	Arithmetic_Ast(Ast* temp_lhs, ARITHMETIC_OP temp_op, Ast* temp_rhs, int line);
	~Arithmetic_Ast();

	void print(ostream & file_buffer);

	Data_Type get_data_type();
	bool check_ast();
	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);		
	
	void set_data_type(Data_Type data_type);

};

class GoTo_Ast:public Ast
{
	Ast * child;
public:
	
	GoTo_Ast(Ast * temp_child, int line);
	~GoTo_Ast();

	void print(ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
};

class Conditional_Ast:public Ast
{
// If condition can have relational conditions only, this is because the preprocessor takes care of all other cases, i.e. cases where there is an assignment statement as condition( eg:- if(a = 0) ) or a const value as condition (eg:- if(0) )
	Ast * condition;
	Ast * trueSuccessor;
	Ast * falseSuccessor;
	
public:
	Conditional_Ast(Ast * temp_condition, Ast * a, Ast * b, int line);
	~Conditional_Ast();

	void print(ostream & file_buffer);

	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
};

class successor:public Ast
{
	int n;
public:
	
	successor(int a);
	~successor();

	void print(ostream & file_buffer);
	
	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
		
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
};

class Type_Ast:public Ast
{
	Ast *child;
	Symbol_Table_Entry * symbol_entry;
public:

	Type_Ast(Ast * temp, int line, Symbol_Table_Entry * s);
	~Type_Ast();
	
	void print(ostream & file_buffer);
	
	Code_For_Ast & compile();
	Code_For_Ast & compile_and_optimize_ast(Lra_Outcome & lra);
	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

	Data_Type get_data_type();
	void set_data_type(Data_Type data_type);	
	
	Symbol_Table_Entry & get_symbol_entry();
//	const type_info& get_child_type();
};

#endif
