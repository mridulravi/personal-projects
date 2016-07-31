/*********************************************************************************

	            Abstract Syntax Trees for cs306 2013-14
                    Implemented by 
                         - Tanu Kanvar (tanu@cse.iitb.ac.in), and
                         - Uday Khedker (uday@cse.iitb.ac.in) 

*********************************************************************************/

#include<iostream>
#include<fstream>
#include <cstdlib>
#include <stdlib.h>
#include<list>

using namespace std;

#include"ast.hh"

Assignment_Ast::Assignment_Ast(Ast * arg_lhs, Ast * arg_rhs)
{
	lhs = arg_lhs;
	rhs = arg_rhs;
}

Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

void Assignment_Ast::print(ostream & NAME)
{
	(*lhs).print(NAME);
	NAME<<" = ";
	(*rhs).print(NAME);
}

/////////////////////////////////////////////////////////////////////////////

Name_Ast::Name_Ast(string & name)
{
	variable_name = name;
}

Name_Ast::~Name_Ast()
{}

void Name_Ast::print(ostream & NAME)
{
	NAME << variable_name;
}
///////////////////////////////////////////////////////////////////////////////

Number_Ast::Number_Ast(int number)
{
	constant = number;
}

Number_Ast::~Number_Ast()
{}

void Number_Ast::print(ostream & NUM)
{
	NUM << constant;
}


///////////////////////////////////////////////////////////////////////////////
void print_Ast_List(ast_List_Ptr alist)
{
	list<ast_Ptr>::iterator i;

	int line=1;

	for (i=alist->begin(); i != alist->end(); i++)
        {
		cout << line++ << ": ";
        	(*i)->print(cout);
		cout << "\n";
        }

	cout << "\n";
}



///////////////////////////////////////////////////////////////////////////////

Relational_Expr_Ast::Relational_Expr_Ast(Ast * arg_lhs, compare C, Ast * arg_rhs)
{
	lhs = arg_lhs;
	oper = C;
	rhs = arg_rhs;
}

Relational_Expr_Ast::~Relational_Expr_Ast()
{}

void Relational_Expr_Ast::print(ostream & NAME)
{
	NAME<<"(";
	(*lhs).print(NAME);
	if (oper == 0)
		NAME<<" <= ";
	else if (oper == 1)
		NAME<<" < ";
	else if (oper == 2)
		NAME<<" >= ";
	else if (oper == 3)
		NAME<<" > ";
	(*rhs).print(NAME);
	NAME<<")";
}


///////////////////////////////////////////////////////////////////////////////

Boolean_Expr_Ast::Boolean_Expr_Ast(Ast * arg_lhs, boolean C, Ast * arg_rhs)
{
	lhs = arg_lhs;
	boolOper = C;
	rhs = arg_rhs;
}

Boolean_Expr_Ast::~Boolean_Expr_Ast()
{}

void Boolean_Expr_Ast::print(ostream & NAME)
{
	NAME<<"(";
	
	if (boolOper == 0) {
		(*lhs).print(NAME);
		NAME<<"&&";
		(*rhs).print(NAME);
		}
	else if (boolOper == 1){
		(*lhs).print(NAME);
		NAME<<"||";
		(*rhs).print(NAME);
		}
	else if (boolOper == 2){
		if (lhs == NULL) {
		NAME<<"!";
		(*rhs).print(NAME);
		}
		if (rhs == NULL) {
		NAME<<"!";
		(*lhs).print(NAME);
		}
		}
		
	NAME<<")";
}

///////////////////////////////////////////////////////////////////////////////

