#include <stdio.h>
#include "lex.yy.c"
extern char* yytext;
int yywrap(){return 1;}

int main()
{
  int token;
  while((token=yylex()))
  {
    switch(token) 
    {
        case SINGLE_LINE_COMMENT:    {printf("< SINGLE_LINE_COMMENT, %d, %s>\n",token,yytext); break;}
        case MULTIPLE_LINE_COMMENT:     {printf("< MULTIPLE_LINE_COMMENT, %d, %s>\n",token,yytext); break;}

        //KeyWords
        case RETURN: {printf("< KEYWORD: RETURN, %d, %s >\n",token,yytext); break;}
        case VOID: {printf("< KEYWORD: VOID, %d, %s >\n",token,yytext); break;}
        case CHAR: {printf("< KEYWORD: CHAR, %d, %s >\n",token,yytext); break;}
        case FOR: {printf("< KEYWORD: FOR, %d, %s >\n",token,yytext); break;}
        case IF: {printf("< KEYWORD: IF, %d, %s >\n",token,yytext); break;}
        case INT: {printf("< KEYWORD: INT, %d, %s >\n",token,yytext); break;}
        case ELSE: {printf("< KEYWORD: ELSE, %d, %s >\n",token,yytext); break;}
        
        // identifiers
        case IDENTIFIER: {printf("< IDENTIFIER, %d, %s>\n",token,yytext); break;}
        case INTEGER_CONSTANT: {printf("< CONSTANT: INTEGER_CONSTANT, %d, %s>\n",token,yytext); break;}
        case CHARACTER_CONSTANT: {yytext=yytext+1;yytext[strlen(yytext)-1]='\0';printf("< CONSTANT: CHARACTER_CONSTANT, %d, %s>\n",token,yytext); break;}
        case STRING_LITERAL: {yytext=yytext+1;yytext[strlen(yytext)-1]='\0';printf("< STRING_LITERAL, %d, %s>\n",token,yytext); break;}

        //punctuators
        case SQUAREBRACKETOPEN:      {printf("< PUNCTUATOR: SQUAREBRACKETOPEN, %d, %s>\n",token,yytext); break;}
        case SQUAREBRACKETCLOSE:     {printf("< PUNCTUATOR: SQUAREBRACKETCLOSE, %d, %s>\n",token,yytext); break;}
        case ROUNDBRACKETOPEN:      {printf("< PUNCTUATOR: ROUNDBRACKETOPEN, %d, %s>\n",token,yytext); break;}
        case ROUNDBRACKETCLOSE:     {printf("< PUNCTUATOR: ROUNDBRACKETCLOSE, %d, %s>\n",token,yytext); break;} 
        case CURLYBRACKETOPEN:     {printf("< PUNCTUATOR: CURLYBRACKETOPEN, %d, %s>\n",token,yytext); break;}
        case CURLYBRACKETCLOSE:    {printf("< PUNCTUATOR: CURLYBRACKETCLOSE, %d, %s>\n",token,yytext); break;}
        case DOT:    {printf("< PUNCTUATOR: DOT, %d, %s>\n",token,yytext); break;}
        case ARWCOM:    {printf("< PUNCTUATOR: ARWCOM, %d, %s>\n",token,yytext); break;}
        case AMPSND:    {printf("< PUNCTUATOR: AMPSND, %d, %s>\n",token,yytext); break;}
        case MULTIPLICATION: {printf("< PUNCTUATOR: MULTIPLICATION, %d, %s>\n",token,yytext); break;}
        case ADDITION:    {printf("< PUNCTUATOR: ADDITION, %d, %s>\n",token,yytext); break;}
        case SUBTRACTION:    {printf("< PUNCTUATOR: SUBTRACTION, %d, %s>\n",token,yytext); break;}
        case NEGATION:    {printf("< PUNCTUATOR: NEGATION, %d, %s>\n",token,yytext); break;}
        case EXCLAIMATION:    {printf("< PUNCTUATOR: EXCLAIMATION, %d, %s>\n",token,yytext); break;}
        case DIVISION:    {printf("< PUNCTUATOR: DIVISION, %d, %s>\n",token,yytext); break;}
        case MODULO:     {printf("< PUNCTUATOR: MODULO, %d, %s>\n",token,yytext); break;}
        case LESSTHAN:     {printf("< PUNCTUATOR: LESSTHAN, %d, %s>\n",token,yytext); break;}
        case GREATERTHAN:     {printf("< PUNCTUATOR: GREATERTHAN, %d, %s>\n",token,yytext); break;}
        case LESSTHANOREQUAL:    {printf("< PUNCTUATOR: LESSTHANOREQUAL, %d, %s>\n",token,yytext); break;}
        case GREATERTHANOREQUAL:    {printf("< PUNCTUATOR: GREATERTHANOREQUAL, %d, %s>\n",token,yytext); break;}
        case EQUAL:     {printf("< PUNCTUATOR: EQUAL, %d, %s>\n",token,yytext); break;}
        case NOTEQUAL:    {printf("< PUNCTUATOR: NOTEQUAL, %d, %s>\n",token,yytext); break;}
        case AND:    {printf("< PUNCTUATOR: AND, %d, %s>\n",token,yytext); break;}
        case OR:     {printf("< PUNCTUATOR: OR, %d, %s>\n",token,yytext); break;}
        case QUESTION:       {printf("< PUNCTUATOR: QUESTION, %d, %s>\n",token,yytext); break;}
        case COLON:      {printf("< PUNCTUATOR: COLON, %d, %s>\n",token,yytext); break;}
        case SEMICOLON:      {printf("< PUNCTUATOR: SEMICOLON, %d, %s>\n",token,yytext); break;}
        case ASSIGN:     {printf("< PUNCTUATOR: ASSIGN, %d, %s>\n",token,yytext); break;}
        case COMMA:      {printf("< PUNCTUATOR: COMMA, %d, %s>\n",token,yytext); break;}
    }
  }
return 0;
}