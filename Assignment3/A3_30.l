%{
#define SINGLE_LINE_COMMENT 	    1
#define MULTIPLE_LINE_COMMENT 	    2
#define RETURN 				        3
#define VOID 				        4
#define CHAR 				        5
#define FOR 				        6
#define IF 					        7
#define ELSE 				        8
#define INT 				        9

#define IDENTIFIER 			        10
#define INTEGER_CONSTANT            11
#define STRING_LITERAL   	        12
#define CHARACTER_CONSTANT      	13
#define BOOLEAN_CONSTANT 	        14

/*[](){}->&*+-/%! ? <><=>===!=&&||=: ;,*/
#define SQUAREBRACKETOPEN 			15
#define SQUAREBRACKETCLOSE 			16
#define ROUNDBRACKETOPEN 			17
#define ROUNDBRACKETCLOSE 			18
#define CURLYBRACKETOPEN 			19
#define CURLYBRACKETCLOSE 			20
#define DOT 				        21
#define ARWCOM 				        22
#define AMPSND 				        23
#define MULTIPLICATION 		        24
#define ADDITION 				    25
#define SUBTRACTION 				26
#define NEGATION 				    27
#define EXCLAIMATION 			    28
#define DIVISION 				    29
#define MODULO 				        30
#define LESSTHAN 	 			    31
#define GREATERTHAN 				32
#define LESSTHANOREQUAL 			33
#define GREATERTHANOREQUAL 			34
#define EQUAL 				        35
#define NOTEQUAL 				    36
#define AND 				        37
#define OR 					        38
#define QUESTION 			        39
#define COLON 				        40
#define SEMICOLON 			        41
#define ASSIGN 				        42
#define COMMA 				        43
%}
/* Regular Expression Definitions */
/*COMMENTS*/
SINGLE_LINE_COMMENT            [/][/][^\n]*
SEQUENCE                       [^*]|[*][^/]
MULTIPLE_LINE_COMMENT          [/][*]{SEQUENCE}*[*][/]
/*KEYWORDS*/
KEYWORD						"char"|"else"|"for"|"if"|"int"|"return"|"void"
/*IDENTIFIERS*/
IDENTIFIER_NONDIGIT         "_"|[a-zA-Z]
IDENTIFIER                  {IDENTIFIER_NONDIGIT}({IDENTIFIER_NONDIGIT}|[0-9])*
/*CONSTANTS*/
SIGN 						[+-]
NONZERO_DIGIT               [1-9]
DIGIT                       [0-9]
NONZERO_INTEGER_CONSTANT    {NONZERO_DIGIT}({NONZERO_DIGIT}|{DIGIT})*
UNSIGNED_INTEGER_CONSTANT   "0"|{NONZERO_INTEGER_CONSTANT}
SIGNED_INTEGER_CONSTANT     {SIGN}{NONZERO_INTEGER_CONSTANT}
INTEGER_CONSTANT            "0"|{NONZERO_INTEGER_CONSTANT}|{SIGNED_INTEGER_CONSTANT}



ESCAPE_SEQUENCE				"\\'"|"\\\""|"\?"|"\\"|"\a"|"\b"|"\f"|"\n"|"\r"|"\t"|"\v"
C_CHAR 						{ESCAPE_SEQUENCE}|[^("\'"|"\\"|"\n")]
C_CHAR_SEQUENCE				{C_CHAR}({C_CHAR})*
CHARACTER_CONSTANT			"\'"{C_CHAR_SEQUENCE}"\'"


/*STRING_LITERALS*/
S_CHAR  					{ESCAPE_SEQUENCE}|[^("\""|"\\"|"\n")]
S_CHAR_SEQUENCE				{S_CHAR}({S_CHAR})*
STRING_LITERAL 				"\""{S_CHAR_SEQUENCE}?"\""

PUNCTUATION			        "["|"]"|"("|")"|"{"|"}"|"."|"->"|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"%"|"<"|">"|"<="|">="|"=="|"!="|"&&"|"||"|"?"|":"|";"|","|"="|"*="|"/="|"%="|"+="|"-="|"&="

SQUAREBRACKETOPEN 			"["
SQUAREBRACKETCLOSE 			"]"
ROUNDBRACKETOPEN 			"("
ROUNDBRACKETCLOSE 			")"
CURLYBRACKETOPEN 			"{"
CURLYBRACKETCLOSE 			"}"
DOT 				"."
ARWCOM 				"->"
AMPSND 				"&"
MULTIPLICATION 		"*"
ADDITION 			"+"
SUBTRACTION 		"-"
NEGATION 			"~"
EXCLAIMATION 		"!"
DIVISION 			"/"
MODULO 				"%"
LESSTHAN 	 		"<"
GREATERTHAN 		">"
LESSTHANOREQUAL 	"<="
GREATERTHANOREQUAL 	">="
EQUAL 				"=="
NOTEQUAL 			"!="
AND 				"&&"
OR 					"||"
QUESTION 			"?"
COLON 				":"
SEMICOLON 			";"
ASSIGN 				"="
COMMA 				","


%%
{MULTIPLE_LINE_COMMENT} 		{return MULTIPLE_LINE_COMMENT;}
{SINGLE_LINE_COMMENT}			{return SINGLE_LINE_COMMENT;}

"return"					{ return RETURN; }
"void"						{ return VOID; }
"char"						{ return CHAR; }
"for"						{ return FOR; }
"if"						{ return IF; }
"int"						{ return INT; }
"else"						{ return ELSE; }
{INTEGER_CONSTANT}	        {return INTEGER_CONSTANT;}
{CHARACTER_CONSTANT}        {return CHARACTER_CONSTANT;}
{STRING_LITERAL}            {return STRING_LITERAL;}
{IDENTIFIER}	            {return IDENTIFIER;}

{SQUAREBRACKETOPEN} 		{ return SQUAREBRACKETOPEN;}
{SQUAREBRACKETCLOSE}		{ return SQUAREBRACKETCLOSE;}
{ROUNDBRACKETOPEN} 			{ return ROUNDBRACKETOPEN;}
{ROUNDBRACKETCLOSE} 		{ return ROUNDBRACKETCLOSE;}
{CURLYBRACKETOPEN}			{ return CURLYBRACKETOPEN;}
{CURLYBRACKETCLOSE} 		{ return CURLYBRACKETCLOSE;}
{DOT} 					    { return DOT;}
{ARWCOM}					{ return ARWCOM;}

{AMPSND}					{ return AMPSND;}
{MULTIPLICATION} 			{ return MULTIPLICATION;}
{ADDITION} 					{ return ADDITION;}
{SUBTRACTION}			    { return SUBTRACTION;}
{NEGATION}					{ return NEGATION;}
{EXCLAIMATION}				{ return EXCLAIMATION;}

{DIVISION} 					{ return DIVISION;}
{MODULO}					{ return MODULO;}
{LESSTHAN} 					{ return LESSTHAN;}
{GREATERTHAN} 				{ return GREATERTHAN;}
{LESSTHANOREQUAL} 			{ return LESSTHANOREQUAL;}
{GREATERTHANOREQUAL} 		{ return GREATERTHANOREQUAL;}
{EQUAL} 					{ return EQUAL;}
{NOTEQUAL} 					{ return NOTEQUAL;}
{AND} 					    { return AND;}
{OR} 					    { return OR;}

{QUESTION} 					{ return QUESTION;}
{COLON} 					{ return COLON;}
{SEMICOLON} 				{ return SEMICOLON;}
{ASSIGN} 					{ return ASSIGN;}
{COMMA} 					{ return COMMA;}
"\n"|" "|"\t"	{

}
%%





