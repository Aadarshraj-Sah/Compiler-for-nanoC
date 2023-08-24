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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IDENTIFIERS = 265,
    INTEGER_CONSTANT = 266,
    CHARACTER_CONSTANT = 267,
    STRING_LITERAL = 268,
    LEFT_SQUARE_BRACKET = 269,
    RIGHT_SQUARE_BRACKET = 270,
    LEFT_PARENTHESIS = 271,
    RIGHT_PARENTHESIS = 272,
    LEFT_CURLY_BRACKET = 273,
    RIGHT_CURLY_BRACKET = 274,
    DOT = 275,
    ARROW = 276,
    BITWISE_AND = 277,
    MULTIPLY = 278,
    ADD = 279,
    SUBTRACT = 280,
    BITWISE_NOR = 281,
    NOT = 282,
    DIVIDE = 283,
    MODULO = 284,
    LESS_THAN = 285,
    GREATER_THAN = 286,
    LESS_THAN_EQUAL = 287,
    GREATER_THAN_EQUAL = 288,
    EQUAL = 289,
    NOT_EQUAL = 290,
    LOGICAL_AND = 291,
    LOGICAL_OR = 292,
    QUESTION_MARK = 293,
    COLON = 294,
    SEMICOLON = 295,
    ASSIGN = 296,
    COMMA = 297
  };
#endif
/* Tokens.  */
#define CHAR 258
#define ELSE 259
#define FOR 260
#define IF 261
#define INT 262
#define RETURN 263
#define VOID 264
#define IDENTIFIERS 265
#define INTEGER_CONSTANT 266
#define CHARACTER_CONSTANT 267
#define STRING_LITERAL 268
#define LEFT_SQUARE_BRACKET 269
#define RIGHT_SQUARE_BRACKET 270
#define LEFT_PARENTHESIS 271
#define RIGHT_PARENTHESIS 272
#define LEFT_CURLY_BRACKET 273
#define RIGHT_CURLY_BRACKET 274
#define DOT 275
#define ARROW 276
#define BITWISE_AND 277
#define MULTIPLY 278
#define ADD 279
#define SUBTRACT 280
#define BITWISE_NOR 281
#define NOT 282
#define DIVIDE 283
#define MODULO 284
#define LESS_THAN 285
#define GREATER_THAN 286
#define LESS_THAN_EQUAL 287
#define GREATER_THAN_EQUAL 288
#define EQUAL 289
#define NOT_EQUAL 290
#define LOGICAL_AND 291
#define LOGICAL_OR 292
#define QUESTION_MARK 293
#define COLON 294
#define SEMICOLON 295
#define ASSIGN 296
#define COMMA 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "A4_30.y"

    int int_value;
    char char_value;
    char *string_value;

#line 147 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
