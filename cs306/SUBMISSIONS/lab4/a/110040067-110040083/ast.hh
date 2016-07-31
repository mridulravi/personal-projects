
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
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>

#define AST_SPACE "         "				// 9 spaces
#define AST_NODE_SPACE "            "		// 12 spaces

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
	Data_Type node_data_type;
public:
	Ast();
	~Ast();

	virtual Data_Type get_data_type();
	virtual bool check_ast(int line);

	virtual void print_ast(ostream & file_buffer) = 0;
	virtual void print_value(Local_Environment & eval_env, ostream & file_buffer);

	virtual Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);
	virtual void set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result);
	virtual Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer) = 0;
	
	virtual void set_data_type(Data_Type data_type);
};

class Assignment_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	
// Calling a virtual function with a pointer that has base class type but points to a derived class object, calls the member function of the derived class. However, calling a nonvirtual function with a pointer that has base class type calls the member function of the base class, regardless of whether or not the pointer points to a derived class object. 

public:
	Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs);
	~Assignment_Ast();

	Data_Type get_data_type();
	bool check_ast(int line);

	void print_ast(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	void set_data_type(Data_Type data_type);
};

class Name_Ast:public Ast
{
	string variable_name;
	Symbol_Table_Entry variable_symbol_entry;

public:
	Name_Ast(string & name, Symbol_Table_Entry & var_entry);
	~Name_Ast();

	Data_Type get_data_type();

	void print_ast(ostream & file_buffer);

	void print_value(Local_Environment & eval_env, ostream & file_buffer);
	Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);
	void set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result);
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	void set_data_type(Data_Type data_type);
};

template <class T>
class Number_Ast:public Ast
{
	T constant;

public:
	Number_Ast(T number, Data_Type constant_data_type);
	~Number_Ast();

	Data_Type get_data_type();
	
	void print_ast(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	void set_data_type(Data_Type data_type);
	
};

class Return_Ast:public Ast
{

public:
	Return_Ast();
	~Return_Ast();

	void print_ast(ostream & file_buffer);

	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
};

// From here we are defining our own class

class Relational_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	RELATIONAL_OP op;

public:
	Relational_Ast(Ast * temp_lhs, RELATIONAL_OP temp_op, Ast * temp_rhs);
	~Relational_Ast();

	void print_ast(ostream & file_buffer);
	
	Data_Type get_data_type();
	bool check_ast(int line);
	
	//Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	void set_data_type(Data_Type data_type);
};

class Arithmetic_Ast:public Ast
{
	// for Unary, give rhs as NULL 
	Ast * lhs;
	Ast * rhs;
	ARITHMETIC_OP op;
	
public:
	Arithmetic_Ast(Ast* temp_lhs, ARITHMETIC_OP temp_op, Ast* temp_rhs);
	~Arithmetic_Ast();

	void print_ast(ostream & file_buffer);

	Data_Type get_data_type();
	bool check_ast(int line);
	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	
	void set_data_type(Data_Type data_type);

};

class GoTo_Ast:public Ast
{
	Ast * child;
public:
	
	GoTo_Ast(Ast * temp_child);
	~GoTo_Ast();

	void print_ast(ostream & file_buffer);
	//Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);

};

class Conditional_Ast:public Ast
{
// If condition can have relational conditions only, this is because the preprocessor takes care of all other cases, i.e. cases where there is an assignment statement as condition( eg:- if(a = 0) ) or a const value as condition (eg:- if(0) )
	Ast * condition;
	Ast * trueSuccessor;
	Ast * falseSuccessor;
	//successor * trueSuccessor;
	//successor * falseSuccessor;
	
public:
	//Conditional_Ast(Ast * temp_condition, successor * a, successor * b);
	Conditional_Ast(Ast * temp_condition, Ast * a, Ast * b);
	~Conditional_Ast();

	void print_ast(ostream & file_buffer);
	//Eval_Result & get_value_of_evaluation(Local_Environment & eval_env);	
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
};

class successor:public Ast
{
	int n;
public:
	
	successor(int a);
	~successor();

//	Data_Type get_data_type();
//	bool check_ast(int line);

	void print_ast(ostream & file_buffer);
	Eval_Result & evaluate(Local_Environment & eval_env, ostream & file_buffer);
	//void set_data_type(Data_Type data_type);
	//int get_successor();
};

// what should be the type conversion strategy in case of relational
// in sir's case if we have 0 on lhs and float on rhs, then it is producing tokens but not producing AST, while if 0 is on rhs and float is on lhs, then it is producing both tokens and ast


#endif
