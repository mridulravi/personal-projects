
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
%token <string_value> NAME
%token RETURN INTEGER
%token IF
%token ELSE
%token GOTO
%token ASSIGN_OP
%token NE EQ 
%token LT LE GT GE

%type <symbol_table> declaration_statement_list
%type <symbol_entry> declaration_statement
%type <basic_block_list> basic_block_list
%type <basic_block> basic_block
%type <ast_list> executable_statement_list
%type <ast_list> assignment_statement_list
%type <ast> assignment_statement
%type <ast> variable
%type <ast> constant
%type <ast> single_term inner_comp comparison if_goto_else_goto goto_stmt

%start program

%%

program:
	declaration_statement_list procedure_name
	{
		program_object.set_global_table(*$1);
		return_statement_used_flag = false;				// No return statement in the current procedure till now
	}
	procedure_body
	{
		program_object.set_procedure_map(*current_procedure);

		if ($1)
			$1->global_list_in_proc_map_check(get_line_number());

		delete $1;
	}
|
	procedure_name
	{
		return_statement_used_flag = false;				// No return statement in the current procedure till now
	}
	procedure_body
	{
		program_object.set_procedure_map(*current_procedure);
	}
;

procedure_name:
	NAME '(' ')'
	{
		current_procedure = new Procedure(void_data_type, *$1);
	}
;

procedure_body:
	'{' declaration_statement_list
	{
		current_procedure->set_local_list(*$2);
		delete $2;
	}
	basic_block_list '}'
	{
		if (return_statement_used_flag == false)
		{
			int line = get_line_number();
			//report_error("Atleast 1 basic block should have a return statement", line);
		}

		current_procedure->set_basic_block_list(*$4);

		delete $4;
	}
|
	'{' basic_block_list '}'
	{
		if (return_statement_used_flag == false)
		{
			int line = get_line_number();
			//report_error("Atleast 1 basic block should have a return statement", line);
		}

		current_procedure->set_basic_block_list(*$2);

		delete $2;
	}
;

declaration_statement_list:
	declaration_statement
	{
		int line = get_line_number();
		program_object.variable_in_proc_map_check($1->get_variable_name(), line);

		string var_name = $1->get_variable_name();
		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}

		$$ = new Symbol_Table();
		$$->push_symbol($1);
	}
|
	declaration_statement_list declaration_statement
	{
		// if declaration is local then no need to check in global list
		// if declaration is global then this list is global list

		int line = get_line_number();
		program_object.variable_in_proc_map_check($2->get_variable_name(), line);

		string var_name = $2->get_variable_name();
		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}

		if ($1 != NULL)
		{
			if($1->variable_in_symbol_list_check(var_name))
			{
				int line = get_line_number();
				report_error("Variable is declared twice", line);
			}

			$$ = $1;
		}

		else
			$$ = new Symbol_Table();

		$$->push_symbol($2);
	}
;

declaration_statement:
	INTEGER NAME ';'
	{
		$$ = new Symbol_Table_Entry(*$2, int_data_type);

		delete $2;
	}
;

basic_block_list:
	basic_block_list basic_block
	{
		if (!$2)
		{
			int line = get_line_number();
			report_error("Basic block doesn't exist", line);
		}

		bb_strictly_increasing_order_check($$, $2->get_bb_number());

		$$ = $1;
		$$->push_back($2);
	}
|
	basic_block
	{
		if (!$1)
		{
			int line = get_line_number();
			report_error("Basic block doesn't exist", line);
		}

		$$ = new list<Basic_Block *>;
		$$->push_back($1);
	}
	
;

basic_block:
	BASICBLOCK ':' executable_statement_list
	{
		if ($3 != NULL) 
		{
			 $$ = new Basic_Block($1, *$3); // in the previous code, it should have been $6, but here $3 is right 
		}
		else 
		{ 
			list<Ast *> * ast_list = new list<Ast *>; 
			$$ = new Basic_Block($1, *ast_list); 
		}
		delete $3;
	}
;

executable_statement_list:
	assignment_statement_list
	{
		$$ = $1;
	}
|
	assignment_statement_list RETURN ';'
	{
		Ast * ret = new Return_Ast();

		return_statement_used_flag = true;					// Current procedure has an occurrence of return statement

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		$$->push_back(ret);
	}
|
	assignment_statement_list if_goto_else_goto	
	{	
		// So if_goto_else_goto will be pushed in statement_list 
		
		//***********************//
		// here $$ = $1(check for NULL before this), then $1 -> push_back($2)
		// i have added this 

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		$$->push_back($2);
	}
|
	assignment_statement_list goto_stmt
	{	//***********************//
		// here $$ = $1, then $1 -> push_back($2)	
		// i have added this 

		if ($1 != NULL)
			$$ = $1;

		else
			$$ = new list<Ast *>;

		
		$$->push_back(new GoTo_Ast($2) );
		//Ast * temp = (Ast *)new Goto_Ast($2);
		//$$->push_back(temp);
	}
;

assignment_statement_list:
	{
		$$ = NULL;
	}
|
	assignment_statement_list assignment_statement
	{
		if ($1 == NULL)
			$$ = new list<Ast *>;

		else
			$$ = $1;

		$$->push_back($2);
	}
;

assignment_statement:
 	variable ASSIGN_OP comparison ';'
	{
			
		// i have added this code portion
		
		// do we have to check for multiple assignments in a statement also, if yes then we have to add a rule for variable ASSIGN_OP assignment_statement
		
		$$ = new Assignment_Ast($1, $3);

		int line = get_line_number();
		$$->check_ast(line);							// This statement is giving us errors	-- fixed
	}
;

variable:
	NAME
	{
		Symbol_Table_Entry var_table_entry;

		// if the symbol table entry of the current procedure has this variable, then extract it from there, otherwise check in symbol list of program(i.e. global list), otherwise throw an error
		
		
		if (current_procedure->variable_in_symbol_list_check(*$1))
			 var_table_entry = current_procedure->get_symbol_table_entry(*$1);

		else if (program_object.variable_in_symbol_list_check(*$1))
			var_table_entry = program_object.get_symbol_table_entry(*$1);

		else
		{
			int line = get_line_number();
			report_error("Variable has not been declared", line);
		}

		$$ = new Name_Ast(*$1, var_table_entry);

		delete $1;
	}
;

constant:
	INTEGER_NUMBER
	{
		$$ = new Number_Ast<int>($1, int_data_type);
	}
;

comparison:
	comparison NE inner_comp
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::NE, $3);		//5
		int line = get_line_number();
		$$->check_ast(line);
		
	}
|
	comparison EQ inner_comp
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::EQ, $3);						//0
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	inner_comp
	{							// if you remove this one or either the single_term, then the shift reduce conflict goes
		$$ = $1;
	}
;

inner_comp:
	inner_comp GE single_term
	{ 
		$$ = new Relational_Ast($1, RELATIONAL_OP::GE, $3);				//1
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	inner_comp GT single_term
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::GT, $3);					//2
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	inner_comp LE single_term
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::LE, $3);				//3
		int line = get_line_number();
		$$->check_ast(line);

	}
|
	inner_comp LT single_term
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::LT, $3);				//4
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	single_term
	{
		$$ = $1;
	}
;

single_term:
	variable
	{
		$$ = $1;
	}
|
	constant
	{
		$$ = $1;
	}
;

if_goto_else_goto : IF '(' comparison ')' goto_stmt ELSE goto_stmt
	{
		//$$ = new Conditional_Ast($3, ($5).getSuccessor(), (*$7).getSuccessor() ); 	
		
		$$ = new Conditional_Ast($3, $5, $7);
	}
;
                             
goto_stmt : GOTO BASICBLOCK ';'
    {
    	// have to change here(in assignment statement also), in ast.hh and ast.cc, right now the new returns Ast * which is the problem
    	//$$ = new Number_Ast<int>($2, int_data_type);
    	
    	$$ = new successor($2);
    }
;
