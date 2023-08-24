%{
    #include "y.tab.h"
%}

%option yylineno

DIGIT                           [0-9]
ID_NON_DIGIT                    [a-zA-Z_]
NON_ZERO_DIGIT                  [1-9]
IDENTIFIERS                     {ID_NON_DIGIT}({DIGIT}|{ID_NON_DIGIT})*
SIGN                            [+-]
DIGIT_SEQUENCE                  {DIGIT}+
INTEGER_CONSTANT                {NON_ZERO_DIGIT}{DIGIT}*|[0]
ESCAPE_SEQUENCE                 "\\'"|"\\""|"\\?"|"\\\"|"\\a"|"\\b"|"\\f"|"\\n"|"\\r"|"\\t"|"\\v"
C_CHAR                          [^\'\n\\]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE                 {C_CHAR}+
CHARACTER_CONSTANT              \'{C_CHAR_SEQUENCE}\'
S_CHAR                          [^\"\n\\]|{ESCAPE_SEQUENCE}
S_CHAR_SEQUENCE                 {S_CHAR}+
STRING_LITERAL                  \"{S_CHAR_SEQUENCE}?\"
SINGLE_COMMENT_STARTED          "//"
MULTILINE_STARTED               "/*"
MULTILINE_END                   "*/"
WS                              [ \n\t]
%x SINGLE_LINE_COMMENT
%x MULTIPLE_LINE_COMMENT

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

"char"                          { return CHAR; }
"else"                          { return ELSE; }
"for"                           { return FOR; }
"if"                            { return IF; }
"int"                           { return INT; }
"return"                        { return RETURN; }
"void"                          { return VOID; }

{IDENTIFIERS}                               {return IDENTIFIERS;}
{INTEGER_CONSTANT}                          {return INTEGER_CONSTANT;}
{CHARACTER_CONSTANT}                        {return CHARACTER_CONSTANT;}
{STRING_LITERAL}                            {return STRING_LITERAL;}

{SQUAREBRACKETOPEN}                             { return LEFT_SQUARE_BRACKET; }
{SQUAREBRACKETCLOSE}                             { return RIGHT_SQUARE_BRACKET; }
{ROUNDBRACKETOPEN}                             { return LEFT_PARENTHESIS; }
{ROUNDBRACKETCLOSE}                             { return RIGHT_PARENTHESIS; }
{CURLYBRACKETOPEN}                             { return LEFT_CURLY_BRACKET; }
{CURLYBRACKETCLOSE}                             { return RIGHT_CURLY_BRACKET; }
{DOT}                             { return DOT; }
{ARWCOM}                            { return ARROW; }
{AMPSND}                             { return BITWISE_AND; }
{MULTIPLICATION}                             { return MULTIPLY; }
{ADDITION}                             { return ADD; }
{SUBTRACTION}                             { return SUBTRACT; }
{NEGATION}                             { return BITWISE_NOR; }
{EXCLAIMATION}                             { return NOT; }
{DIVISION}                             { return DIVIDE; }
{MODULO}                             { return MODULO; }
{LESSTHAN}                             { return LESS_THAN; }
{GREATERTHAN}                             { return GREATER_THAN; }
{LESSTHANOREQUAL}                            { return LESS_THAN_EQUAL; }
{GREATERTHANOREQUAL}                            { return GREATER_THAN_EQUAL; }
{EQUAL}                            { return EQUAL; }
{NOTEQUAL}                            { return NOT_EQUAL; }
{AND}                            { return LOGICAL_AND; }
{OR}                            { return LOGICAL_OR; }
{QUESTION}                             { return QUESTION_MARK; }
{COLON}                             { return COLON; }
{SEMICOLON}                             { return SEMICOLON; }
{ASSIGN}                             { return ASSIGN; }
{COMMA}                             { return COMMA; }

{SINGLE_COMMENT_STARTED}                    {BEGIN(SINGLE_LINE_COMMENT);}
<SINGLE_LINE_COMMENT>.                      {}
<SINGLE_LINE_COMMENT>"\n"                   {BEGIN(INITIAL); }
{MULTILINE_STARTED}                         {BEGIN(MULTIPLE_LINE_COMMENT);}
<MULTIPLE_LINE_COMMENT>.                    {}
<MULTIPLE_LINE_COMMENT>"\n"                 {}
<MULTIPLE_LINE_COMMENT>{MULTILINE_END}      {BEGIN(INITIAL); }
{WS}                                        {}

%%