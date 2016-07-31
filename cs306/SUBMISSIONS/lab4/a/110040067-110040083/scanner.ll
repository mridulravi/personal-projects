
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

%filenames="scanner"
%lex-source="scanner.cc"

%%
if		{
			store_token_name("IF");
			return Parser::IF; 
		}

else	{ 
			store_token_name("ELSE");
			return Parser::ELSE; 
		}
		
goto	{ 
			store_token_name("GOTO");
			return Parser::GOTO; 
		}
		
void	{
			store_token_name("VOID");
			return Parser::VOID; 
		}
		
int		{
			store_token_name("INTEGER");
			return Parser::INTEGER; 
		}
		
float	{
			store_token_name("FLOAT");
			return Parser::FLOAT;
		}
		
double	{
			store_token_name("DOUBLE");
			return Parser::DOUBLE;
		}

return	{ 
			store_token_name("RETURN");
			return Parser::RETURN; 
		}
		
"<bb "[[:digit:]]+">" { 
			store_token_name("BASIC BLOCK"); // here we will use atoi to extract the digits 
			string str; 
			for(int i = 4; matched()[i]!='>';i++) 
			{
				str.push_back(matched()[i]); 
			} 
			int value = atoi(str.c_str()); // now value stores the basic block number 
			if(value < 2) 
			{ 
				int line = lineNr();
 				report_error("Illegal basic block label", line); 
 			} 
 			else 
 			{ 
 				ParserBase::STYPE__ * val = getSval();
  				val->integer_value = value; 
  			} 
	  		return Parser::BASICBLOCK;
		}
		
"<="	{
			store_token_name("LE");
			return Parser::LE;
		}

">="	{
			store_token_name("GE");
			return Parser::GE;
		}
		
"<"		{
			store_token_name("LT");
			return Parser::LT;
		}
		
">"		{
			store_token_name("GT");
			return Parser::GT;
		}
		
"!="	{
			store_token_name("NE");
			return Parser::NE;
		}
		
"=="	{
			store_token_name("EQ");
			return Parser::EQ;
		}
		
"="		{
			store_token_name("ASSIGN_OP");
			return Parser::ASSIGN_OP;
		}
		
[-]?[[:digit:]]+"."[[:digit:]]+ 	{	
			//Always a optional "-" followed by 1 or more digits followed
			//by a "." followed by 1 or more digits		
			store_token_name("FNUM");
			
			ParserBase::STYPE__ * val = getSval();
			val->float_value = atof(matched().c_str());

			return Parser::FLOAT_NUMBER; 
		}

[:{}();=,]	{
			store_token_name("META CHAR");
			return matched()[0];
		}

[-]?[[:digit:]]+ 	{
				// have removed _ after digit block, earlier it was [[:digit:]_] 
				store_token_name("NUM");
				
				ParserBase::STYPE__ * val = getSval();
				val->integer_value = atoi(matched().c_str());

				return Parser::INTEGER_NUMBER; 
			}

[[:alpha:]_][[:alpha:][:digit:]_]* {
					store_token_name("NAME");

					ParserBase::STYPE__ * val = getSval();
					val->string_value = new std::string(matched());

					return Parser::NAME; 
				}
				
[-+*/]	{
			store_token_name("ARITHOP");
			return matched()[0];
		}

\n		{ 
			if (command_options.is_show_tokens_selected())
				ignore_token();
		}    

";;".*  	|
[ \t]		{
			if (command_options.is_show_tokens_selected())
				ignore_token();
		}


"//".* 	{
			//std::cout<<"The comment is "<<matched()<endl;
			//printf("%s", matched().c_str());
			if (command_options.is_show_tokens_selected())
				ignore_token();
		}

.		{ 
			string error_message;
			error_message =  "Illegal character `" + matched();
			error_message += "' on line " + lineNr();
			
			int line_number = lineNr();
			report_error(error_message, line_number);
		}
