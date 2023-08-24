/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_A5_30_TAB_H_INCLUDED
# define YY_YY_A5_30_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    ELSE = 259,
    FOR = 260,
    IF = 261,
    INT = 262,
    RETURN = 263,
    VOID = 264,
    LEFT_SQR_BRACKET = 265,
    RIGHT_SQR_BRACKET = 266,
    LEFT_PAREN = 267,
    RIGHT_PAREN = 268,
    LEFT_CURLY_BRACE = 269,
    RIGHT_CURLY_BRACE = 270,
    DOT = 271,
    ARROW = 272,
    BITWISE_AND = 273,
    MULTIPLY = 274,
    ADD = 275,
    SUBTRACT = 276,
    NOT = 277,
    DIVIDE = 278,
    MODULO = 279,
    LESS_THAN = 280,
    GREATER_THAN = 281,
    LESS_THAN_EQUALS = 282,
    GREATER_THAN_EQUALS = 283,
    EQUALS = 284,
    NOT_EQUALS = 285,
    LOGICAL_AND = 286,
    LOGICAL_OR = 287,
    QUESTION_MARK = 288,
    COLON = 289,
    SEMICOLON = 290,
    ASSIGNMENT = 291,
    COMMA = 292,
    IDENTIFIER = 293,
    INT_CONSTANT = 294,
    CHAR_CONSTANT = 295,
    STRING_LITERAL = 296,
    THEN = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "A5_30.y"

    int intval;             // For an integer value
    char* charval;          // For a char value
    int instr;              // A special type for instruction number, needed in backpatching
    char unaryOp;           // For unary operators
    int numParams;          // For number of parameters to a function
    Expression* expr;       // For an expression
    Statement* stmt;        // For a statement
    Symbol* symptr;           // For a symbol
    SymbolType* symType;    // For the type of a symbol
    Array* arr;             // For arrays

#line 113 "A5_30.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A5_30_TAB_H_INCLUDED  */
