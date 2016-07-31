
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

%scanner ../scanner.h
%scanner-token-function d_scanner.lex()
%filenames parser
%parsefun-source parser.cc

%union 
{
	int integer_value;
	float float_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	list<Basic_Block *> * basic_block_list;
	Procedure * procedure;
};

%token <integer_value> INTEGER_NUMBER
%token <integer_value> BASICBLOCK
%token <float_value> FLOAT_NUMBER 
%token <string_value> NAME
%token RETURN INTEGER
%token FLOAT
%token DOUBLE
%token VOID
%token IF
%token ELSE
%token GOTO
%token ASSIGN_OP
%token NE EQ 
%token LT LE GT GE


%start program

%%

program: 
	declaration_statement_list functions_declaration_list functions_list
	{}
|	declaration_statement_list functions_list
	{}
|	functions_declaration_list functions_list
	{}
|	functions_list
;

declaration_statement_list: 
	declaration_statement
	{}
| 	declaration_statement_list declaration_statement
	{}
;
                         
declaration_statement:
	FLOAT NAME ';'
	{}
|	INTEGER NAME ';'
	{}
;	

functions_declaration_list: 
	function_declaration
	{}
| 	functions_declaration_list function_declaration
	{}	
;

function_declaration: 
	FLOAT NAME '(' parameters_list ')' ';'
	{}
| 	FLOAT NAME '(' ')' ';'
	{}
| 	INTEGER NAME '(' parameters_list ')' ';'
	{}
| 	INTEGER NAME '(' ')' ';'
	{}
| 	VOID NAME '(' parameters_list ')' ';'
	{}
| 	VOID NAME '(' ')' ';'
	{}
;
					  
parameters_list: 
	parameter
	{}
| 	parameters_list ',' parameter
	{}
;
			   
parameter: 	
	INTEGER NAME 
	{}
|	FLOAT NAME
	{}
;
		 

functions_list: 
	functions_list function 
	{}
|	function
	{}
;
			  
function: 
	function_name function_body
	{}
;
		
function_name: 
	NAME '(' parameters_list ')'
	{}
| 	NAME '(' ')'
	{}
;

function_body: 
	'{'
	declaration_statement_list
    basic_block_list
    '}'
	{}	
|	'{'
    basic_block_list
    '}'
	{}	
;


basic_block_list:
	basic_block_list basic_block
	{}
|
	basic_block
	{}
;

basic_block:
	BASICBLOCK ':' executable_statement_list
	{}
;

executable_statement_list:
	assignment_statement_list
	{}
|
	assignment_statement_list return_stmt ';'
	{}
|
	assignment_statement_list if_goto_else_goto	
	{}
|
	assignment_statement_list goto_stmt
	{}
;


assignment_statement_list:
	{}
|	assignment_statement_list assignment_statement
	{}	
|	assignment_statement_list function_call_stmt
	{}	
;

function_call_stmt: 
	NAME '(' ')' ';'
	{}
|	NAME '(' passed_arguments_list ')' ';' 
	{}
;

passed_arguments_list: 
	comparison
	{}
| 	passed_arguments_list ',' comparison
	{}
;

assignment_statement:
 	variable ASSIGN_OP comparison ';'
	{} 	
;

comparison:
	comparison NE inner_comp
	{}
|
	comparison EQ inner_comp
	{}
|
	inner_comp
	{}
;

inner_comp:
	inner_comp GE expression
	{}
|	inner_comp GT expression
	{}
| 	inner_comp LT expression
	{}
|	inner_comp LE expression
	{}
|	expression
	{}
;

expression:
	expression '+' sub_expr
	{}
|	expression '-' sub_expr
	{}
|	sub_expr
	{}
;

sub_expr:
	sub_expr '*' single_term
	{}
|	sub_expr '/' single_term
	{}
|	single_term
	{}
;

single_term:
	function_call
	{}
|	variable
	{}
|	'-' variable
	{}
|	constant
	{}
|	'(' data_type ')' single_term
	{}
|	'-' '(' data_type ')' single_term
	{}	
|	'(' comparison ')'
	{}
|	'-' '(' comparison ')'
	{}
;

data_type:
	INTEGER
	{}
|
	FLOAT
	{}
|
	DOUBLE
	{}
;


variable:
	NAME
	{}
;

constant:
	INTEGER_NUMBER
	{}
|	FLOAT_NUMBER
	{}
;


if_goto_else_goto : IF '(' comparison ')' goto_stmt ELSE goto_stmt
	{}
;
                             
goto_stmt : GOTO BASICBLOCK ';'
  	{}
;

function_call: 
	NAME '(' ')'
	{}
| 	NAME '(' passed_arguments_list ')' 	
	{}
;

return_stmt: 
	RETURN
  	{}
| 	RETURN comparison
  	{}
;  
