/*********************************************************************************

	            Abstract Syntax Trees for cs306 2013-14
                    Implemented by 
                         - Tanu Kanvar (tanu@cse.iitb.ac.in), and
                         - Uday Khedker (uday@cse.iitb.ac.in) 

*********************************************************************************/

#ifndef AST_HH
#define AST_HH

#include<string>

using namespace std;

class Ast;
typedef Ast * ast_Ptr;
typedef list <ast_Ptr> * ast_List_Ptr;
void print_Ast_List (ast_List_Ptr alist);

enum compare 
	{ 
	LE, 
	LT, 
	GE, 
	GT, 
	};
	
enum boolean 
	{ 
	AND, 
	OR,
	NOT 
	};

class Ast
{
public:
	Ast() {}
	~Ast() {}

	virtual void print(ostream &) = 0;

};

class Assignment_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;

public:
	Assignment_Ast(Ast * arg_lhs, Ast * arg_rhs);
	~Assignment_Ast();

	void print(ostream &);

};

class Name_Ast: public Ast
{
	string variable_name;

public:
	Name_Ast(string & name);
	~Name_Ast();

	void print(ostream &);

};

class Number_Ast:public Ast
{
	int constant;

public:
	Number_Ast(int number);
	~Number_Ast();

	void print(ostream &);

};

class Relational_Expr_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	compare oper;

public:
	Relational_Expr_Ast(Ast * arg_lhs, compare C, Ast * arg_rhs);
	~Relational_Expr_Ast();

	void print(ostream &);

};



class Boolean_Expr_Ast:public Ast
{
	Ast * lhs;
	Ast * rhs;
	boolean boolOper;

public:
	Boolean_Expr_Ast(Ast * arg_lhs, boolean C, Ast * arg_rhs);
	~Boolean_Expr_Ast();

	void print(ostream &);

};


#endif
