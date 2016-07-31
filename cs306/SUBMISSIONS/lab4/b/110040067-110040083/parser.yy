
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

%type <symbol_table> declaration_statement_list parameters_list
%type <symbol_entry> declaration_statement parameter
%type <basic_block_list> basic_block_list
%type <basic_block> basic_block
%type <ast_list> executable_statement_list
%type <ast_list> assignment_statement_list
%type <ast> assignment_statement function_call_stmt function_call
%type <ast> variable return_stmt
%type <ast> constant
%type <ast> single_term inner_comp comparison if_goto_else_goto goto_stmt expression sub_expr
%type <integer_value> data_type
%type <ast_list> passed_arguments_list

%start program

%%

program: 
	declaration_statement_list functions_declaration_list 
	{
		// global_symbol_table in program.cc should be set to declaration_statement_list
		program_object.set_global_table(*$1);
		delete $1;
		// where should the declared functions go, so functions_declaration_list will be a list of Procedures, using this we will fill the entries in procedure_map
		// we don't need to do anything with functions_declaration_list, the function have already been put into the procedure_map in the function_name actions
		
		// program_object is an object of class Program, add the functions in procedure_map, it is of type map<string, Procedure*>, before adding check whether that function is there already there in procedure_map, if not then give an error, otherwise match the arguments no and types and the return types of the functions and 
		
		// here check that all the functions except main are declared(i.e. already present in the procedure_map)
		
		
	}
	functions_list
	{
		// here check whether all the called functions are defined or not
		map<string, int> temp = program_object.get_called_procedure_list();
		map<string, int>::iterator itr;
		for(itr = temp.begin();itr!=temp.end();itr++)
		{
			if(!program_object.get_procedure_defined( (*itr).first ) )
			{
				report_error("Called Function is declared but not defined", NOLINE);
			}
		}
	}
|	declaration_statement_list
	{
		// here if we have only "main" in functions list, then ok otherwise throw an error
		program_object.set_global_table(*$1);
		delete $1;
	}
	functions_list
	{
		// here check whether all the called functions are defined or not
		map<string, int> temp = program_object.get_called_procedure_list();
		map<string, int>::iterator itr;
		for(itr = temp.begin();itr!=temp.end();itr++)
		{
			if(!program_object.get_procedure_defined( (*itr).first ) )
			{
				report_error("Called Function is declared but not defined", NOLINE);
			}
		}
	}
|	functions_declaration_list functions_list
	{
		// here check whether all the functions in functions_list are declared already or not (exception is main), main will not be in functions_declaration_list but will be in functions_list
		
		// don't need to do anything here(alreay done in actions of some other rules)
		
		// here check whether all the called functions are defined or not
		map<string, int> temp = program_object.get_called_procedure_list();
		map<string, int>::iterator itr;
		for(itr = temp.begin();itr!=temp.end();itr++)
		{
			if(!program_object.get_procedure_defined( (*itr).first ) )
			{
				report_error("Called Function is declared but not defined", NOLINE);
			}
		}
	}
|	functions_list
	{
		// don't need to do anything
		// here check whether all the called functions are defined or not
		map<string, int> temp = program_object.get_called_procedure_list();
		map<string, int>::iterator itr;
		for(itr = temp.begin();itr!=temp.end();itr++)
		{
			if(!program_object.get_procedure_defined( (*itr).first ) )
			{
				report_error("Called Function is declared but not defined", NOLINE);
			}
		}
	}
;

declaration_statement_list:
	declaration_statement
	{
		int line = get_line_number();
		program_object.variable_in_proc_map_check($1->get_variable_name(), line);

		string var_name = $1->get_variable_name();

		// so whenever you go in function_name, set the current procedure as for that function
		
		// this check is not required, because current procedure will already be in the procedure_map
/*		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}
*/
		$$ = new Symbol_Table();
		$$->push_symbol($1);
	}
|
	declaration_statement_list declaration_statement
	{

		// if declaration is local then no need to check in global list
		// if declaration is global then this list is global list

		int line = get_line_number();
		program_object.variable_in_proc_map_check($2->get_variable_name(), line);		// this ensures that variable name cannot be same as procedure name

		string var_name = $2->get_variable_name();
		
/*		if (current_procedure && current_procedure->get_proc_name() == var_name)
		{
			int line = get_line_number();
			report_error("Variable name cannot be same as procedure name", line);
		}
*/
		
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
		// have to add for float as well *****
	}
|	FLOAT NAME ';'
	{
		$$ = new Symbol_Table_Entry(*$2, float_data_type);

		delete $2;
	}
;

functions_declaration_list: 
	function_declaration
	{
		// so here we don't need to do anything, as we have already put them in the procedure_map in actions of function_declaration
	}
| 	functions_declaration_list function_declaration
	{
		// so here we don't need to do anything, as we have already put them in the procedure_map in actions of function_declaration	
	}	
;

function_declaration: 
	FLOAT NAME '(' parameters_list ')' ';'
	{
		// here i must add them in the procedure map, i.e. add in procedure_map of program_object;
		
		// here adding a check for the case where function name is same as a global variable
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
		
		// i should also put the parameters in the symbol table, so instead of parameters being list
		Procedure * temp = new Procedure(float_data_type, *$2, $4->get_symbol_table_size(), *$4);
		// how to get the 3rd parameter, i.e. size of the symbol table
		program_object.set_procedure_map(*temp);
		delete $4;
		delete $2;
	}
| 	FLOAT NAME '(' ')' ';'
	{
	
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
	
		// same as in the above case
		Procedure * temp = new Procedure(float_data_type, *$2,0, *new Symbol_Table);
		program_object.set_procedure_map(*temp);
		delete $2;
	}
| 	INTEGER NAME '(' parameters_list ')' ';'
	{
	
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
	
		Procedure * temp = new Procedure(int_data_type, *$2, $4->get_symbol_table_size(), *$4);
		program_object.set_procedure_map(*temp);
		delete $4;
		delete $2;
	}
| 	INTEGER NAME '(' ')' ';'
	{
	
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
		
		Procedure * temp = new Procedure(int_data_type, *$2,0, *new Symbol_Table);
		program_object.set_procedure_map(*temp);
		delete $2;
	}
| 	VOID NAME '(' parameters_list ')' ';'
	{
	
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
	
		Procedure * temp = new Procedure(void_data_type, *$2, $4->get_symbol_table_size(), *$4);
		program_object.set_procedure_map(*temp);
		delete $4;
		delete $2;
	}
| 	VOID NAME '(' ')' ';'
	{
		
		if(program_object.variable_in_symbol_list_check(*$2) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
	
		Procedure * temp = new Procedure(void_data_type, *$2,0, *new Symbol_Table);
		program_object.set_procedure_map(*temp);
		delete $2;	
	}
;
					  
parameters_list: 
	parameter
	{
		// parameters_list will be a Symbol_Table
		int line = get_line_number();
		program_object.variable_in_proc_map_check($1->get_variable_name(), line);

		string var_name = $1->get_variable_name();		
		$$ = new Symbol_Table();
		$$->push_symbol($1);		
		
	}
| 	parameters_list ',' parameter
	{
		int line = get_line_number();
		program_object.variable_in_proc_map_check($3->get_variable_name(), line);

		string var_name = $3->get_variable_name();
		
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

		$$->push_symbol($3);
	}
;
			   
parameter: 	
	INTEGER NAME 
	{
		// I will return a symbol_table_entry here
	
		// parameter will be of type map<string, Data_Type>
		// The names should also be stored in the procedure
		//$$ = make_pair(*$2, int_data_type);
		$$ = new Symbol_Table_Entry(*$2, int_data_type);

	}
|	FLOAT NAME
	{
		//$$ = float_data_type;
		//$$ = make_pair(*$2, float_data_type);
		$$ = new Symbol_Table_Entry(*$2, float_data_type);
	}
;
		 

functions_list: 
	functions_list function 
	{
		// don't need to do anything here
	}
|	function
	{
		// function will be of type Procedure *
		// don't need to do anything here
	}
;
			  
function: 
	function_name function_body
	{
		// since the current_procedure is a pointer to an already pushed procedure, we do not need to push it again
		// because current_procedure was a pointer and we can therefore add or delete things in it, and we don't have to push again
		// the change will get reflected
		
		// don't need to do anything
		
	}
;
		
function_name: 
	NAME '(' parameters_list ')'
	{
		// check whether the function name is main, if so then enter it in procedure_map of program_object
		if(program_object.variable_in_symbol_list_check(*$1) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}

//		if( (*$1) =="main" )
//		{
//			Procedure * temp = new Procedure(void_data_type, *$1, $3->get_symbol_table_size(), *$3 );
//			program_object.set_procedure_map(*temp);
//			current_procedure = temp;	
//			delete $3;
//			delete $1;	
//		}
//		else
//		{
			// otherwise check whether the given function has been declared above, if not then throw an error
			// if defined, then check whether the arguments are correct(name, type and order all)
		
			current_procedure = program_object.get_procedure(*$1);
			if(current_procedure == NULL)
			{
				// this function has not been declared above
				report_error("Function not declared above", NOLINE);
			}
			
			// setting that this function is defined as well
			program_object.set_procedure_defined(*$1);
			
			// now, match the arguments
			// parameters will be in the symbol table of the function
			
			Symbol_Table temp = current_procedure->get_symbol_table();	// this function is declared in procedure.hh
			// at this point temp.get_symbol_table_size() will be the same as no_of_argument
			
			list<Symbol_Table_Entry *> l1, l2;
			l1 = $3->get_variable_table();
			l2 = temp.get_variable_table();
			
			if( $3->get_symbol_table_size() != temp.get_symbol_table_size() )
			{
				report_error("The no. of arguments in declaration and definition does not match", NOLINE);
			}
		
			// parameters_list is a symbol_table
			list<Symbol_Table_Entry *>::iterator itr1, itr2;
			itr1 = l1.begin();
			itr2 = l2.begin();
			
			// checking whether all the arguments are correct according to the definition
			for(;itr1 !=l1.end();itr2++, itr1++)
			{
				if( ((*itr1)->get_variable_name() != (*itr2)->get_variable_name()) || ((*itr1)->get_data_type() != (*itr2)->get_data_type() ) )
				{
					report_error("Either argument type or argument name does not match in declaration and definition",NOLINE);
				}
			}
			
			delete $3;
		//}

		// set current_procedure as the Procedure *, so that function body will use it to push the local_list and the basic_block_list in it
		// already set	
		
	}
	
| 	NAME '(' ')'
	{

		if(program_object.variable_in_symbol_list_check(*$1) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}

		// check whether the function name is main, if so then enter it in procedure_map of program_object
//		if( (*$1) =="main" )
//		{
//			Procedure * temp = new Procedure(void_data_type, *$1, 0, *new Symbol_Table );
//			program_object.set_procedure_map(*temp);
//			current_procedure = temp;		
//			delete $1;
//		}
//		else
//		{
			// otherwise check whether the given function has been declared above, if not then throw an error
			// if defined, then check whether the arguments are correct(name, type and order all)
		
			current_procedure = program_object.get_procedure(*$1);
			if(current_procedure == NULL)
			{
				// this function has not been declared above
				report_error("Function not declared above", NOLINE);
			}
			
			//setting that this function is defined as well			
			program_object.set_procedure_defined(*$1);
			
			// now, match the arguments
			// parameters will be in the symbol table of the function
			
			Symbol_Table temp = current_procedure->get_symbol_table();	// this function is declared in procedure.hh
			//map<string, Data_Type> temp = current_procedure.get_arguments_list();
		
			if(temp.get_symbol_table_size() !=0)
			{
				report_error("No of arguments in Declaration and definition are not same", NOLINE);
			}
//		}
		// set current_procedure as the Procedure *, so that function body will use it to push the local_list and the basic_block_list in it
		// already set		

	}
;

function_body: 
	'{' declaration_statement_list
	{
		// so here append them in the local_list, instead of making it as the local_symbol_table
		// the arguments of the function are already in the symbol table
		// the current procedure is being referenced by current_procedure
		
		// we will call the append function to append the symbol table to the local_symbol_table, the append function will itself check whether any declared variable is same as an argument, if so, it will throw an error, otherwise it will append 
		// so we are not able to access value of current_procedure
		if(current_procedure == NULL)
		{
			//cout<<"Current_procedure is null\n";
			report_error("current_procedure is NULL",NOLINE);
		}
		
		if(program_object.variable_in_symbol_list_check(current_procedure->get_proc_name() ) )
		{
			report_error("Function name cannot be same as a global variable", NOLINE);
		}
		
		current_procedure->append_local_list(*$2);
		//current_procedure->set_local_list(*$2);		// The arguments should also be in the local_list(if they are, then how to ensure that which are the arguments and which are not)
		delete $2;
	}
    basic_block_list '}'
	{
		// the procedure is being referred by current_procedure
		current_procedure->set_basic_block_list(*$4);
		delete $4;
		
		// here do one more thing, there will be a list of return statements in every procedure
		// when we will reach here, then we will traverse tgrough that list
		// if return type is void and any return is not of type void then throw an error
		// if return type is non-void, then if all return statements are void then throw an error
		// if return type is non-void, then if any return statement returns something then that should match with with the return type of the procedure		
		
		list<Data_Type> my_list = current_procedure->get_return_list();
		list<Data_Type>::iterator itr;
		
		Data_Type proc_return_type = current_procedure->get_return_type();
		bool check_whether_non_void_return_statement_present = false;
		
		for(itr = my_list.begin();itr!=my_list.end();itr++)
		{
			if( (*itr) != void_data_type )
			{
				check_whether_non_void_return_statement_present = true;
			}
		}
		
		if(proc_return_type != void_data_type)
		{
			if(check_whether_non_void_return_statement_present == false)
			{
				report_error("Atleast one non void statement should be present in function as its return type is not void", NOLINE);
			}
		
		}
		
	}	
|	'{' basic_block_list '}'
	{
		current_procedure->set_basic_block_list(*$2);
		delete $2;	
		
		list<Data_Type> my_list = current_procedure->get_return_list();
		list<Data_Type>::iterator itr;
		
		Data_Type proc_return_type = current_procedure->get_return_type();
		bool check_whether_non_void_return_statement_present = false;
		
		for(itr = my_list.begin();itr!=my_list.end();itr++)
		{
			if( (*itr) != void_data_type )
			{
				check_whether_non_void_return_statement_present = true;
			}
		}
		
		if(proc_return_type != void_data_type)
		{
			if(check_whether_non_void_return_statement_present == false)
			{
				report_error("Atleast one non void statement should be present in function as its return type is not void", NOLINE);
			}
		
		}
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
		//cout<<"Inside the basic block action\n";
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
		//cout<<"Exiting the basic block action\n";
	}
;

executable_statement_list:
	assignment_statement_list
	{
		$$ = $1;
	}
|
	assignment_statement_list return_stmt ';'
	{
		// return_stmt will return a Return_Ast *, check if the current procedure is not main, then the return type should be compatiblke, otherwise it should throw an error
		if($1 !=NULL)
			$$ = $1;
		else
			$$ = new list<Ast *>;
			
		$$->push_back($2);
	
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
|	assignment_statement_list assignment_statement
	{
		if ($1 == NULL)
			$$ = new list<Ast *>;

		else
			$$ = $1;

		$$->push_back($2);
	}	
|	assignment_statement_list function_call_stmt
	{
		// add action here also
		// make an Ast Function_Ast(which will be for function call only, because we need this in function calls only, not at the time of decaration )
		// puh the Function_Ast * in the list<Ast*>, if it is not null, otherwise create one and push into it
		if($1 !=NULL)
		{
			$$ = $1;
		}
		else
		{
			$$ = new list<Ast*>;
		}
		
		$$->push_back($2);
	}	
;

function_call_stmt: 
	NAME '(' ')' ';'
	{
		// here a function call is made, I have to push it in the statement list
		Procedure * temp = program_object.get_procedure(*$1);
		if(temp == NULL)
		{
			report_error("Function is not declared", NOLINE);
		}

		program_object.set_called_procedure(*$1);

/*		if(!program_object.get_procedure_defined(*$1))
		{
			report_error("Function declared but not defined", NOLINE);
		}
*/	
		$$ = new Function_call_Ast(*$1,temp->get_return_type() );
	}
|	NAME '(' passed_arguments_list ')' ';' 
	{
		// here also the same thing, here first check whether they all are same as in the arguments list, and if so then push them in the local symbol table
		Procedure * temp = program_object.get_procedure(*$1);
		if(temp == NULL)
		{
			report_error("Function is not defined", NOLINE);
		}

		program_object.set_called_procedure(*$1);
		
/*		if(!program_object.get_procedure_defined(*$1))
		{
			report_error("Function declared but not defined", NOLINE);
		}
*/	
		// match the arguments list
		// passed_arguments_list is a list of Ast*
		int no_arguments = temp->get_no_of_arguments();
		if(no_arguments != $3->size() )
		{
			report_error("No. of arguments are not same in declaration and call of the function", NOLINE);
		}
		
		// passed_arguments_list will be list<Ast*>
		// so here just check the data type of the elements with that in the function's arguments list
		list<Symbol_Table_Entry *> local = temp->get_symbol_table().get_variable_table();		
		list<Ast *>::iterator itr1 = $3->begin();
		list<Symbol_Table_Entry *>::iterator itr2 = local.begin();
		
		int i=0;
		for(;i<no_arguments;i++)
		{
			if( (*itr1)->get_data_type() != (*itr2)->get_data_type() )
			{
				report_error("Data type of the argument at declaration and call is not same", NOLINE);
			}
			itr1++;
			itr2++;
		}
		
		$$ = new Function_call_Ast(*$1, *$3, temp->get_return_type() );
	}
;

passed_arguments_list: 
	comparison
	{
		// here i have to make a list of Ast* 
		// return the list of Ast* to function_call or function_call_stmt, 
		// in the actions of function call or function_call_stmt, check for correctness and store the value in the symbol_table
		
		$$ = new list<Ast *>;
		$$->push_back($1);
	
	}
| 	passed_arguments_list ',' comparison
	{
		if($1!=NULL)
		{
			$$ = $1;
		}
		else
		{
			$$ = new list<Ast *>;
		}
		$$->push_back($3);
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
	inner_comp GE expression
	{ 
		$$ = new Relational_Ast($1, RELATIONAL_OP::GE, $3);				//1
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	inner_comp GT expression
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::GT, $3);					//2
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	inner_comp LE expression
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::LE, $3);				//3
		int line = get_line_number();
		$$->check_ast(line);

	}
|
	inner_comp LT expression
	{
		$$ = new Relational_Ast($1, RELATIONAL_OP::LT, $3);				//4
		int line = get_line_number();
		$$->check_ast(line);
	}
|
	expression
	{
		$$ = $1;
	}
;

expression:
	expression '+' sub_expr
	{
		$$ = new Arithmetic_Ast($1, ARITHMETIC_OP::PLUS,$3);
		int line = get_line_number();
		$$->check_ast(line);
	}
|	expression '-' sub_expr
	{
		$$ = new Arithmetic_Ast($1, ARITHMETIC_OP::MINUS,$3);
		int line = get_line_number();
		$$->check_ast(line);
	}
|	sub_expr
	{
		$$ = $1;
	}
;

sub_expr:
	sub_expr '*' single_term
	{
		$$= new Arithmetic_Ast($1, ARITHMETIC_OP::MULT,$3);
		int line = get_line_number();
		$$->check_ast(line);
	}
|	sub_expr '/' single_term
	{
		$$= new Arithmetic_Ast($1, ARITHMETIC_OP::DIV,$3);
		int line = get_line_number();
		$$->check_ast(line);
	}
|	single_term
	{
		$$ = $1;
	}
;

single_term:
	function_call
	{
		// here check that the function called is not main(), otherwise give an error
		
		// also check that the function called is actually defined, otherwise throw an error, for this use variable_in_proc_map() function of program_object
		// if the return value of that is some number, than return a Number_ast* whose value is value returned by it, and return type is the return type of the function
		// if the return type of the function is void, then if it is in arithmetic operation, then return with an error;
		$$ = $1;
	}
|	variable
	{
		$$ = $1;
	}
|	'-' variable
	{
		// create an Ast having UMinus as OP and rhs as NULL
		$$= new Arithmetic_Ast($2, ARITHMETIC_OP::UMINUS, NULL);
		int line = get_line_number();
		$$->check_ast(line);
	}
|	constant
	{
		$$ = $1;
	}
|	'(' data_type ')' single_term
	{
		$$ = $4;
		if($2 == 1)
		{
			$$->set_data_type(int_data_type);
		}
		else if($2 == 2)
		{
			$$->set_data_type(float_data_type);
		}
		else if($2 == 3)
		{
			$$->set_data_type(double_data_type);
		}
		
		//int line = get_line_number();
		//$$->check_ast(line);
	}
|	'-' '(' data_type ')' single_term
	{
		// what if $5 is a variable, then set_data_type wouldn't work, because we wouldn't change the value in 
		
		$$= new Arithmetic_Ast($5, ARITHMETIC_OP::UMINUS, NULL);
		if($3 == 1)
		{
			$$->set_data_type(int_data_type);
		}
		else if($3 == 2)
		{
			$$->set_data_type(float_data_type);
		}
		else if($3 == 3)
		{
			$$->set_data_type(double_data_type);
		}
		
		//int line = get_line_number();
		//$$->check_ast(line);
	}	
|	'(' comparison ')'
	{
		$$ = $2;
		//int line = get_line_number();
		//$$->check_ast(line);
	}
|	'-' '(' comparison ')'
	{
		//$$ = - $2;
		$$= new Arithmetic_Ast($3, ARITHMETIC_OP::UMINUS, NULL);
		int line = get_line_number();
		$$->check_ast(line);
	}
;

data_type:
	INTEGER
	{$$ = 1;}
|
	FLOAT
	{$$ = 2;}
|
	DOUBLE
	{$$ = 3;}
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
|	FLOAT_NUMBER
	{
		$$ = new Number_Ast<float>($1, float_data_type);
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
function_call: 
	NAME '(' ')'
	{
	
		// use get procedue to get the pointer, if the pointer is NULL, then throw an error that function is not defined
		Procedure * temp = program_object.get_procedure(*$1);
		if(temp == NULL)
		{
			report_error("Function is not defined", NOLINE);
		}
	
		program_object.set_called_procedure(*$1);
			
/*		if(!program_object.get_procedure_defined(*$1))
		{
			report_error("Function declared but not defined", NOLINE);
		}
*/			
		// if the function return type is void, then throw an error
		if(temp->get_return_type() == void_data_type)
		{
			report_error("Incompatible type ", NOLINE);
		}
		
/*		
		// if the function is main, then also throw an error
		if(temp->get_proc_name() == "main")
		{
			report_error("Cannot call main", NOLINE);		
		}
		// can call main recursively as well
*/	

		// otherwise return 
		
		// have to return Function_Ast, which will
		// now, what should i return
		// see operationRet.ast, it will tell us that the arguments are the Ast's, i.e. if an argument is number, than use Number_ast for it, if it is string then use Name_Ast for it,
		// so it will be a list of Ast* and not a map of <string, Data_Type>
		
		$$ = new Function_call_Ast(*$1, temp->get_return_type() );
		
	}
| 	NAME '(' passed_arguments_list ')' 	
	{
		// check all the cases mentioned above
		// also check if the function is defined, then does the arguments match with the declaration of the function or not
		Procedure * temp = program_object.get_procedure(*$1);
		if(temp == NULL)
		{
			report_error("Function is not defined", NOLINE);
		}
		
		program_object.set_called_procedure(*$1);
		
/*		if(!program_object.get_procedure_defined(*$1))
		{
			report_error("Function declared but not defined", NOLINE);
		}
*/			
		// if the function return type is void, then throw an error
		if(temp->get_return_type() == void_data_type)
		{
			report_error("Incompatible type ", NOLINE);
		}

		// match the arguments list
		// passed_arguments_list is a list of Ast*
		int no_arguments = temp->get_no_of_arguments();
		if(no_arguments != $3->size() )
		{
			report_error("No. of arguments are not same in declaration and call of the function", NOLINE);
		}
		
		// passed_arguments_list will be list<Ast*>
		// so here just check the data type of the elements with that in the function's arguments list
		list<Symbol_Table_Entry *> local = temp->get_symbol_table().get_variable_table();		
		list<Ast *>::iterator itr1 = $3->begin();
		list<Symbol_Table_Entry *>::iterator itr2 = local.begin();
		
		int i=0;
		for(;i<no_arguments;i++)
		{
			if( (*itr1)->get_data_type() != (*itr2)->get_data_type() )
			{
				report_error("Data type of the argument at declaration and call is not same", NOLINE);
			}
			itr1++;
			itr2++;
		}
		
		// so the following portion of code is wrong
/*		int i =0;
		Symbol_Table local = temp.get_symbol_table;
		Symbol_Table::iterator itr1, itr2;
		itr1 = $3->begin();
		itr2 = local.begin();
		for(;i<no_arguments;i++)
		{
			if( (*itr1)->get_data_type() != (*itr2)->get_data_type() )
			{
				report_error("Data type of the argument at declaration and call is not same", NOLINE);
			}	
			itr1++;
			itr2++;
		}
*/		
		// create a function_ast and return it
		$$ = new Function_call_Ast(*$1, *$3, temp->get_return_type() );
		delete $3;
	}
;

return_stmt: 
	RETURN
  	{
  		// return Return_Ast
  		$$ = new Return_Ast();
  		current_procedure->push_in_return_list(void_data_type);
  	}
| 	RETURN comparison
  	{
  	
  		// if data type of return and procedure does not match, then throw an error
  		if($2->get_data_type() != current_procedure->get_return_type() )
  		{
  			int line_no = get_line_number();
  			report_error("Return type of the statement does not match with the return type of the procedure",line_no);
  		}
  		current_procedure->push_in_return_list($2->get_data_type() );
  		
  		$$ = new Return_Ast($2);
  	}
;  
