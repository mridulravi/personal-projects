%scanner scanner.h
%scanner-token-function d-scanner.lex()
%filenames parser
%parsefun-source parser.cc

%union
{
	wff * hil;
	char char_value;
};

%token <char_value>	ALPHABET
%token	IMPLIES FALSE
%start S
%type <hil> W

%%

S : W
	{
		// call implement_dt on $1
		$1->implement_dt();
	}
;

W :
	ALPHABET 
	{
		$$ = new wff(NULL, NULL, $1);
	}
| 
	FALSE 
	{
		$$ = new wff(NULL, NULL, 'f');
	}
| 
	'(' W IMPLIES W ')'
	{
		$$ = new wff($2, $4, 'a');
	}
;
