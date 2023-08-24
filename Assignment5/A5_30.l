/* C Declarations and Definitions */
%{  
    #include <stdio.h>
    #include "A5_30_translator.h"
    #include "A5_30.tab.h"
%}

%option yylineno
%option noyywrap

%x SINGLE_LINE_COMMENT
%x MULTI_LINE_COMMENT

/* Regular Expression Definitions */

IDENTIFIER                      [_a-zA-Z][_a-zA-Z0-9]*

INT_CONSTANT                    [1-9][0-9]*|[0]

DIGIT_SEQUENCE                  [0-9]+


ENUM_CONSTANT                   {IDENTIFIER}

ESCAPE_SEQUENCE                 \\['"?\\abfnrtv]
C_CHAR                          [^\'\\\n]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE                 {C_CHAR}+
CHAR_CONSTANT                   \'({C_CHAR_SEQUENCE})\'

CONSTANT                        {INT_CONSTANT}|{ENUM_CONSTANT}|{CHAR_CONSTANT}

S_CHAR                          [^\"\\\n]|{ESCAPE_SEQUENCE}
S_CHAR_SEQUENCE                 {S_CHAR}+
STRING_LITERAL                  \"({S_CHAR_SEQUENCE}?)\"

WS                              [ \t\n]

/* Definitions of Rules and Actions */
%%

"//"                            { BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>.          { /* eat up the comment */ }
<SINGLE_LINE_COMMENT>\n         { BEGIN(INITIAL); }
<SINGLE_LINE_COMMENT><<EOF>>    { BEGIN(INITIAL); }

"/*"                            { BEGIN(MULTI_LINE_COMMENT); }
<MULTI_LINE_COMMENT>"*/"        { BEGIN(INITIAL); }
<MULTI_LINE_COMMENT>.           { /* eat up the comment */ }
<MULTI_LINE_COMMENT>\n          { /* eat up the comment */ }


"char"                          { return CHAR; }
"else"                          { return ELSE; }
"for"                           { return FOR; }
"if"                            { return IF; }
"int"                           { return INT; }
"return"                        { return RETURN; }
"void"                          { return VOID; }

"["                             { return LEFT_SQR_BRACKET; }
"]"                             { return RIGHT_SQR_BRACKET; }
"("                             { return LEFT_PAREN; }
")"                             { return RIGHT_PAREN; }
"{"                             { return LEFT_CURLY_BRACE; }
"}"                             { return RIGHT_CURLY_BRACE; }
"."                             { return DOT; }
"->"                            { return ARROW; }
"&"                             { return BITWISE_AND; }
"*"                             { return MULTIPLY; }
"+"                             { return ADD; }
"-"                             { return SUBTRACT; }
"!"                             { return NOT; }
"/"                             { return DIVIDE; }
"%"                             { return MODULO; }
"<"                             { return LESS_THAN; }
">"                             { return GREATER_THAN; }
"<="                            { return LESS_THAN_EQUALS; }
">="                            { return GREATER_THAN_EQUALS; }
"=="                            { return EQUALS; }
"!="                            { return NOT_EQUALS; }
"&&"                            { return LOGICAL_AND; }
"||"                            { return LOGICAL_OR; }
"?"                             { return QUESTION_MARK; }
":"                             { return COLON; }
";"                             { return SEMICOLON; }
"="                             { return ASSIGNMENT; }
","                             { return COMMA; }

{IDENTIFIER}                    { yylval.symptr = SymTbl_Current->lookup(yytext); return IDENTIFIER; }
{INT_CONSTANT}                  { yylval.intval = atoi(yytext); return INT_CONSTANT; }
{CHAR_CONSTANT}                 { yylval.charval = yytext; return CHAR_CONSTANT; }
{STRING_LITERAL}                { yylval.charval = yytext; return STRING_LITERAL; }
{WS}                            { /* ignore whitespaces */ }

%%
