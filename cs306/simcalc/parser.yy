%scanner scanner.h
%scanner-token-function d-scanner.lex()
%filenames parser
%parsefun-source parser.cc

%union
{
	char char_value;
};

%token <char_value>	ALPHABET
%token	IMPLIES FALSE

%%

W :
	ALPHABET 
	{}
| 
	FALSE 
	{}
| 
	'(' W IMPLIES W ')'
	{}
;
