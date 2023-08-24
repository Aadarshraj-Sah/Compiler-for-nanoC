/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "A5_30.y"

    #include <iostream>
    #include "A5_30_translator.h"
    // #define DEBUG 1
    using namespace std;

    extern int yylex();         // From lexer
    void yyinfo(string s); 
    void yyerror(string s);     // Function to report errors
    extern char* yytext;        // From lexer, gives the text being currently scanned
    extern int yylineno;        // Used for keeping track of the line number
    extern string prevType;      // Used for storing the last encountered type

    Expression* tmpForBool;

#line 86 "A5_30.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 194 "A5_30.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A5_30_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   238

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   116,   122,   129,   139,   145,   154,   168,
     188,   196,   198,   203,   208,   216,   222,   231,   236,   280,
     284,   288,   292,   296,   303,   321,   333,   346,   362,   367,
     380,   397,   402,   417,   432,   447,   465,   469,   485,   505,
     509,   525,   529,   542,   546,   570,   577,   587,   591,   609,
     615,   624,   631,   635,   646,   650,   654,   662,   672,   676,
     683,   688,   711,   723,   739,   747,   749,   754,   764,   769,
     771,   778,   785,   790,   796,   801,   806,   815,   821,   826,
     831,   840,   851,   855,   862,   866,   877,   881,   888,   892,
     899,   912,   930,   946,   964,   974,   987,  1003,  1008,  1016,
    1018,  1023,  1025,  1030,  1039,  1041,  1046,  1048
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "ELSE", "FOR", "IF", "INT",
  "RETURN", "VOID", "LEFT_SQR_BRACKET", "RIGHT_SQR_BRACKET", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_CURLY_BRACE", "RIGHT_CURLY_BRACE", "DOT", "ARROW",
  "BITWISE_AND", "MULTIPLY", "ADD", "SUBTRACT", "NOT", "DIVIDE", "MODULO",
  "LESS_THAN", "GREATER_THAN", "LESS_THAN_EQUALS", "GREATER_THAN_EQUALS",
  "EQUALS", "NOT_EQUALS", "LOGICAL_AND", "LOGICAL_OR", "QUESTION_MARK",
  "COLON", "SEMICOLON", "ASSIGNMENT", "COMMA", "IDENTIFIER",
  "INT_CONSTANT", "CHAR_CONSTANT", "STRING_LITERAL", "THEN", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list_opt", "argument_expression_list",
  "unary_expression", "unary_operator", "multiplicative_expression",
  "additive_expression", "relational_expression", "equality_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "M", "N", "assignment_expression",
  "assignment_operator", "expression", "declaration", "init_declarator",
  "type_specifier", "declarator", "intermediate_identifier",
  "direct_declarator", "pointer", "parameter_list",
  "intermediate_declarator", "parameter_declaration", "initializer",
  "statement", "loop_statement", "compound_statement",
  "block_item_list_opt", "block_item_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "F", "X", "change_table", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "declaration_list_opt",
  "declaration_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF (-152)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-106)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     135,  -152,  -152,  -152,  -152,   -13,    78,  -152,  -152,  -152,
      56,   -26,     8,     4,  -152,   -25,  -152,  -152,   -16,  -152,
     197,  -152,   -13,  -152,   135,  -152,  -152,    35,   197,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
      89,    21,   197,   124,    68,    27,    83,    34,    91,  -152,
    -152,  -152,    43,    69,  -152,    11,  -152,  -152,    57,   197,
     197,    59,    72,  -152,   197,  -152,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,  -152,  -152,    81,
      55,  -152,    -9,    14,  -152,  -152,   107,   108,    88,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,   124,   124,    68,
      68,    68,    68,    27,    27,   197,   197,  -152,  -152,   117,
     162,  -152,  -152,   102,  -152,  -152,  -152,   130,   131,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,   120,  -152,  -152,   135,
    -152,  -152,   197,    83,    34,   197,   148,   197,  -152,   126,
    -152,  -152,  -152,    55,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,    55,  -152,   128,  -152,   153,   149,  -152,   186,  -152,
    -152,   197,  -152,   114,  -152,   186,  -152,  -152,   163,   197,
    -152,  -152,   114,   155,  -152,  -152,   151,    55,  -152,  -152,
    -152,  -152,  -152,   164,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    55,    56,    54,   102,     0,     0,    99,   101,    64,
      60,     0,    52,     0,    58,     0,     1,   100,     0,    51,
       0,   106,     0,    96,   104,    96,    57,     0,     0,    19,
      20,    21,    22,    23,     2,     6,     7,     4,     8,     3,
      17,    24,     0,    28,    31,    36,    39,    41,    43,    47,
      71,    53,    52,     0,   107,     0,    61,    50,     0,     0,
      14,     0,     0,    49,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    45,     0,
      83,    63,    70,     0,    65,     5,     0,     0,    13,    15,
      11,    12,    48,    25,    26,    27,    24,    29,    30,    32,
      33,    34,    35,    37,    38,     0,     0,    45,    94,     0,
       0,    95,    89,     0,    86,    87,    72,     0,    45,    84,
      73,    74,    75,    76,    59,    68,     0,    69,    62,     0,
       9,    10,     0,    40,    42,     0,     0,     0,    98,     0,
      96,    88,   103,     0,    67,    66,    16,    46,    95,    46,
      97,    83,    85,     0,    96,     0,     0,    45,     0,    45,
      81,     0,    45,     0,    44,     0,    46,    45,    90,     0,
      45,    46,     0,     0,    91,    45,     0,    83,    92,    77,
      78,    79,    80,     0,    93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,  -152,  -152,   -34,  -152,    70,   104,
      75,    82,    79,  -152,    32,   -59,  -121,   -17,  -152,   -28,
      80,  -152,     1,   166,   -77,   179,   113,  -152,  -152,    67,
    -152,  -151,  -152,  -152,  -147,  -152,    71,   -74,    23,    36,
    -152,    62,   -23,    37,  -152,   205,  -152,  -152,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    38,    39,    40,    87,    88,    41,    42,    43,    44,
      45,    46,    47,    48,    49,   105,    79,    57,    64,   113,
     114,    11,    22,    12,    13,    14,    15,    83,   127,    84,
      51,   115,   178,   116,   117,   118,   119,   120,   121,   122,
     136,   140,    53,   123,     6,     7,     8,    23,    24
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,     5,    55,    50,   156,   125,     9,     5,    65,    19,
       9,     1,   166,    10,     1,     2,    25,     3,     2,   106,
       3,   174,  -105,    27,    81,    10,   153,   128,   155,   124,
     183,    86,    93,    94,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    89,    20,   168,    56,    92,   135,   144,
     173,   129,    71,    72,    73,    74,    82,    63,     1,   143,
     108,   109,     2,   110,     3,    77,    18,    28,   -59,   111,
      85,    96,    96,    29,    30,    31,    32,    33,    16,    20,
       4,     1,   139,    80,   162,     2,     4,     3,    69,    70,
     112,   167,    21,    34,    35,    36,    37,    90,   161,    59,
     163,    60,   179,   165,    54,    61,    62,   147,   169,   149,
      91,   172,    75,    76,   107,   146,   176,   151,   130,   108,
     109,   131,   110,    78,   -46,   132,    28,    96,   111,   137,
      82,   158,    29,    30,    31,    32,    33,   141,     1,    97,
      98,   171,     2,    66,     3,   142,   -82,    67,    68,   112,
     103,   104,    34,    35,    36,    37,   108,   109,   124,   110,
     148,   150,   157,    28,   160,   177,   159,   170,   175,    29,
      30,    31,    32,    33,    28,    99,   100,   101,   102,   184,
      29,    30,    31,    32,    33,   134,   112,   133,    52,    34,
      35,    36,    37,   164,    26,   126,   145,   138,    28,   180,
      34,    35,    36,    37,    29,    30,    31,    32,    33,    28,
     154,    17,   181,   182,   152,    29,    30,    31,    32,    33,
       0,   112,     0,     0,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,    37
};

static const yytype_int16 yycheck[] =
{
      28,     0,    25,    20,   151,    82,    19,     6,    42,    35,
      19,     3,   163,    38,     3,     7,    12,     9,     7,    78,
       9,   172,    14,    39,    13,    38,   147,    13,   149,    38,
     177,    59,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    60,    36,   166,    11,    64,   107,   126,
     171,    37,    25,    26,    27,    28,    55,    36,     3,   118,
       5,     6,     7,     8,     9,    31,    10,    12,    12,    14,
      13,   105,   106,    18,    19,    20,    21,    22,     0,    36,
       0,     3,   110,    14,   158,     7,     6,     9,    20,    21,
      35,   165,    12,    38,    39,    40,    41,    38,   157,    10,
     159,    12,   176,   162,    24,    16,    17,   135,   167,   137,
      38,   170,    29,    30,    33,   132,   175,   140,    11,     5,
       6,    13,     8,    32,    33,    37,    12,   161,    14,    12,
     129,   154,    18,    19,    20,    21,    22,    35,     3,    69,
      70,   169,     7,    19,     9,    15,    15,    23,    24,    35,
      75,    76,    38,    39,    40,    41,     5,     6,    38,     8,
      12,    35,    34,    12,    15,    14,    13,     4,    13,    18,
      19,    20,    21,    22,    12,    71,    72,    73,    74,    15,
      18,    19,    20,    21,    22,   106,    35,   105,    22,    38,
      39,    40,    41,   161,    15,    82,   129,    35,    12,   176,
      38,    39,    40,    41,    18,    19,    20,    21,    22,    12,
     148,     6,   176,   176,   143,    18,    19,    20,    21,    22,
      -1,    35,    -1,    -1,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     9,    63,    65,    87,    88,    89,    19,
      38,    64,    66,    67,    68,    69,     0,    88,    10,    35,
      36,    63,    65,    90,    91,    12,    68,    39,    12,    18,
      19,    20,    21,    22,    38,    39,    40,    41,    44,    45,
      46,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      60,    73,    66,    85,    63,    85,    11,    60,    62,    10,
      12,    16,    17,    36,    61,    49,    19,    23,    24,    20,
      21,    25,    26,    27,    28,    29,    30,    31,    32,    59,
      14,    13,    65,    70,    72,    13,    62,    47,    48,    60,
      38,    38,    60,    49,    49,    49,    49,    51,    51,    52,
      52,    52,    52,    53,    53,    58,    58,    33,     5,     6,
       8,    14,    35,    62,    63,    74,    76,    77,    78,    79,
      80,    81,    82,    86,    38,    67,    69,    71,    13,    37,
      11,    13,    37,    54,    55,    58,    83,    12,    35,    62,
      84,    35,    15,    58,    67,    72,    60,    62,    12,    62,
      35,    85,    79,    59,    84,    59,    77,    34,    85,    13,
      15,    58,    80,    58,    57,    58,    74,    80,    59,    58,
       4,    62,    58,    59,    74,    13,    58,    14,    75,    80,
      81,    82,    86,    77,    15
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    50,    50,    51,    51,    51,    51,    52,    52,
      52,    53,    53,    53,    53,    53,    54,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    59,    60,    60,    61,
      62,    63,    64,    64,    65,    65,    65,    66,    66,    67,
      68,    68,    68,    68,    69,    70,    70,    71,    71,    72,
      72,    73,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    76,    77,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    84,    85,    86,    86,    87,
      87,    88,    88,    89,    90,    90,    91,    91
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     4,
       4,     3,     3,     1,     0,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       4,     1,     4,     1,     9,     0,     0,     1,     3,     1,
       1,     3,     1,     3,     1,     1,     1,     2,     1,     1,
       1,     4,     5,     4,     1,     1,     3,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     1,     0,     1,     3,     1,     1,     2,     1,
       8,    11,    14,    16,     0,     0,     0,     3,     2,     1,
       2,     1,     1,     7,     1,     0,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 110 "A5_30.y"
        {
            yyinfo("primary_expression -> IDENTIFIER\n");
            (yyval.expr) = new Expression();  // Create new expression
            (yyval.expr)->addr = (yyvsp[0].symptr);           // Store pointer to entry in the symbol table
            (yyval.expr)->type = "non_bool";
        }
#line 1529 "A5_30.tab.c"
    break;

  case 3:
#line 117 "A5_30.y"
        {
            yyinfo("primary_expression -> constant\n");
            (yyval.expr) = new Expression();  // Create new expression
            (yyval.expr)->addr = (yyvsp[0].symptr);           // Store pointer to entry in the symbol table
        }
#line 1539 "A5_30.tab.c"
    break;

  case 4:
#line 123 "A5_30.y"
        {
            yyinfo("primary_expression -> STRING_LITERAL\n");
            (yyval.expr) = new Expression();  // Create new expression
            (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType("ptr"), (yyvsp[0].charval));  // Create a new temporary, and store the value in that temporary
            (yyval.expr)->addr->sym_type->arrElementType = new SymbolType("char");
        }
#line 1550 "A5_30.tab.c"
    break;

  case 5:
#line 130 "A5_30.y"
        {
            yyinfo("primary_expression -> LEFT_PAREN expression RIGHT_PAREN\n");
            (yyval.expr) = (yyvsp[-1].expr);    // Simple assignment
            if((yyvsp[-1].expr)->type == "bool") 
                tmpForBool = (yyvsp[-1].expr);
        }
#line 1561 "A5_30.tab.c"
    break;

  case 6:
#line 140 "A5_30.y"
        {
            yyinfo("constant -> INT_CONSTANT\n");
            (yyval.symptr) = SymbolTable::gentemp(new SymbolType("int"), to_string((yyvsp[0].intval)));   // Create a new temporary, and store the value in that temporary
            emit("=", (yyval.symptr)->name, (yyvsp[0].intval));
        }
#line 1571 "A5_30.tab.c"
    break;

  case 7:
#line 146 "A5_30.y"
        {
            yyinfo("constant -> CHAR_CONSTANT\n");
            (yyval.symptr) = SymbolTable::gentemp(new SymbolType("float"), string((yyvsp[0].charval)));     // Create a new temporary, and store the value in that temporary
            emit("=", (yyval.symptr)->name, string((yyvsp[0].charval)));
        }
#line 1581 "A5_30.tab.c"
    break;

  case 8:
#line 155 "A5_30.y"
        {
            yyinfo("postfix_expression -> primary_expression\n");
            (yyval.arr) = new Array();           // Create a new Array
            if((yyvsp[0].expr)->type != "bool")
            {(yyval.arr)->array = (yyvsp[0].expr)->addr;        // Store the location of the primary expression
            (yyval.arr)->type = (yyvsp[0].expr)->addr->sym_type;   // Update the type
            (yyval.arr)->addr = (yyval.arr)->array;}
            else
            {
                (yyval.arr)->arr_type = "bool_temporary";
            }

        }
#line 1599 "A5_30.tab.c"
    break;

  case 9:
#line 169 "A5_30.y"
        {
            yyinfo("postfix_expression -> postfix_expression LEFT_SQR_BRACKET expression RIGHT_SQR_BRACKET\n");
            (yyval.arr) = new Array();               // Create a new Array
            (yyval.arr)->type = (yyvsp[-3].arr)->type->arrElementType;   // Set the type equal to the element type
            (yyval.arr)->array = (yyvsp[-3].arr)->array;          // Copy the base
            (yyval.arr)->addr = SymbolTable::gentemp(new SymbolType("int"));  // Store address of new temporary
            (yyval.arr)->arr_type = "arr";              // Set atype to "arr"

            if((yyvsp[-3].arr)->arr_type == "arr") {        // If we have an "arr" type then, multiply the size of the sub-type of Array with the expression value and add
                Symbol* sym = SymbolTable::gentemp(new SymbolType("int"));
                int sz = sizeOfType((yyval.arr)->type);
                emit("*", sym->name, (yyvsp[-1].expr)->addr->name, to_string(sz));
                emit("+", (yyval.arr)->addr->name, (yyvsp[-3].arr)->addr->name, sym->name);
            }
            else {                          // Compute the size
                int sz = sizeOfType((yyval.arr)->type);
                emit("*", (yyval.arr)->addr->name, (yyvsp[-1].expr)->addr->name, to_string(sz));
            }
        }
#line 1623 "A5_30.tab.c"
    break;

  case 10:
#line 189 "A5_30.y"
        {   
            yyinfo("postfix_expression -> postfix_expression LEFT_PAREN argument_expression_list_opt RIGHT_PAREN\n");
            // Corresponds to calling a function with the function name and the appropriate number of parameters
            (yyval.arr) = new Array();
            (yyval.arr)->array = SymbolTable::gentemp((yyvsp[-3].arr)->type);
            emit("call", (yyval.arr)->array->name, (yyvsp[-3].arr)->array->name, to_string((yyvsp[-1].numParams)));
        }
#line 1635 "A5_30.tab.c"
    break;

  case 11:
#line 197 "A5_30.y"
        { yyinfo("postfix_expression -> postfix_expression DOT IDENTIFIER\n");/* Ignored */ }
#line 1641 "A5_30.tab.c"
    break;

  case 12:
#line 199 "A5_30.y"
        { yyinfo("postfix_expression -> postfix_expression ARROW IDENTIFIER\n");/* Ignored */ }
#line 1647 "A5_30.tab.c"
    break;

  case 13:
#line 204 "A5_30.y"
        {
            yyinfo("argument_expression_list_opt -> argument_expression_list\n");
            (yyval.numParams) = (yyvsp[0].numParams);    // Assign $1 to $$
        }
#line 1656 "A5_30.tab.c"
    break;

  case 14:
#line 209 "A5_30.y"
        {
            yyinfo("argument_expression_list_opt -> \n");
            (yyval.numParams) = 0;     // No arguments, just equate to zero
        }
#line 1665 "A5_30.tab.c"
    break;

  case 15:
#line 217 "A5_30.y"
        {
            yyinfo("argument_expression_list -> assignment_expression\n");
            (yyval.numParams) = 1;                         // consider one argument
            emit("param", (yyvsp[0].expr)->addr->name);   // emit parameter
        }
#line 1675 "A5_30.tab.c"
    break;

  case 16:
#line 223 "A5_30.y"
        {
            yyinfo("argument_expression_list -> argument_expression_list COMMA assignment_expression\n");
            (yyval.numParams) = (yyvsp[-2].numParams) + 1;                    // consider one more argument, so add 1
            emit("param", (yyvsp[0].expr)->addr->name);   // emit parameter
        }
#line 1685 "A5_30.tab.c"
    break;

  case 17:
#line 232 "A5_30.y"
        {
            yyinfo("unary_expression -> postfix_expression\n");
            (yyval.arr) = (yyvsp[0].arr);    // Assign $1 to $$
        }
#line 1694 "A5_30.tab.c"
    break;

  case 18:
#line 237 "A5_30.y"
        {
            yyinfo("unary_expression -> unary_operator unary_expression\n");
            // Case of unary operator
            (yyval.arr) = new Array();
            switch((yyvsp[-1].unaryOp)) {
                case '&':   // Address
                    (yyval.arr)->array = SymbolTable::gentemp(new SymbolType("ptr"));    // Generate a pointer temporary
                    (yyval.arr)->array->sym_type->arrElementType = (yyvsp[0].arr)->array->sym_type;                 // Assign corresponding type
                    emit("= &", (yyval.arr)->array->name, (yyvsp[0].arr)->array->name);              // Emit the quad
                    break;
                case '*':   // De-referencing
                    (yyval.arr)->arr_type = "ptr";
                    (yyval.arr)->addr = SymbolTable::gentemp((yyvsp[0].arr)->array->sym_type->arrElementType);   // Generate a temporary of the appropriate type
                    (yyval.arr)->array = (yyvsp[0].arr)->array;                                      // Assign
                    emit("= *", (yyval.arr)->addr->name, (yyvsp[0].arr)->array->name);                // Emit the quad
                    break;
                case '+':   // Unary plus
                    (yyval.arr) = (yyvsp[0].arr);    // Simple assignment
                    break;
                case '-':   // Unary minus
                    (yyval.arr)->array = SymbolTable::gentemp(new SymbolType((yyvsp[0].arr)->array->sym_type->type));    // Generate temporary of the same base type
                    emit("= -", (yyval.arr)->array->name, (yyvsp[0].arr)->array->name);                              // Emit the quad
                    break;
                case '!':   // Logical not 
                    if((yyvsp[0].arr)->arr_type == "bool_temporary")
                    {
                        list<int> l = tmpForBool->falselist;
                        tmpForBool->falselist = tmpForBool->truelist;
                        tmpForBool->truelist = l;
                        (yyval.arr)->arr_type = "bool_temporary";
                    }
                    else
                    {
                        (yyval.arr)->array = SymbolTable::gentemp(new SymbolType((yyvsp[0].arr)->array->sym_type->type));    // Generate temporary of the same base type
                        emit("= !", (yyval.arr)->array->name, (yyvsp[0].arr)->array->name);                              // Emit the quad
                    }
                    break;
            }
        }
#line 1738 "A5_30.tab.c"
    break;

  case 19:
#line 281 "A5_30.y"
        {
            yyinfo("unary_operator -> BITWISE_AND\n");(yyval.unaryOp) = '&';
        }
#line 1746 "A5_30.tab.c"
    break;

  case 20:
#line 285 "A5_30.y"
        {
            yyinfo("unary_operator -> MULTIPLY\n");(yyval.unaryOp) = '*';
        }
#line 1754 "A5_30.tab.c"
    break;

  case 21:
#line 289 "A5_30.y"
        {
            yyinfo("unary_operator -> ADD\n");(yyval.unaryOp) = '+';
        }
#line 1762 "A5_30.tab.c"
    break;

  case 22:
#line 293 "A5_30.y"
        {
            yyinfo("unary_operator -> SUBTRACT\n");(yyval.unaryOp) = '-';
        }
#line 1770 "A5_30.tab.c"
    break;

  case 23:
#line 297 "A5_30.y"
        {
            yyinfo("unary_operator -> NOT\n");(yyval.unaryOp) = '!';
        }
#line 1778 "A5_30.tab.c"
    break;

  case 24:
#line 304 "A5_30.y"
        {
            yyinfo("multiplicative_expression -> unary_expression\n");
            (yyval.expr) = new Expression();          // Generate new expression
            if((yyvsp[0].arr)->arr_type == "arr") {        // atype "arr"
                (yyval.expr)->addr = SymbolTable::gentemp((yyvsp[0].arr)->addr->sym_type);  // Generate new temporary
                emit("=[]", (yyval.expr)->addr->name, (yyvsp[0].arr)->array->name, (yyvsp[0].arr)->addr->name);     // Emit the quad
            }
            else if((yyvsp[0].arr)->arr_type == "ptr") {   // atype "ptr"
                (yyval.expr)->addr = (yyvsp[0].arr)->addr;          // Assign the symbol table entry
            }
            else if((yyvsp[0].arr)->arr_type == "bool_temporary")
            {
                (yyval.expr) = tmpForBool;
            } else {
                (yyval.expr)->addr = (yyvsp[0].arr)->array;
            }
        }
#line 1800 "A5_30.tab.c"
    break;

  case 25:
#line 322 "A5_30.y"
        {   yyinfo("multiplicative_expression -> multiplicative_expression MULTIPLY unary_expression\n");
            // Indicates multiplication
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].arr)->array)) {     // Check for type compatibility
                (yyval.expr) = new Expression();                                                  // Generate new expression
                (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType((yyvsp[-2].expr)->addr->sym_type->type));    // Generate new temporary
                emit("*", (yyval.expr)->addr->name, (yyvsp[-2].expr)->addr->name, (yyvsp[0].arr)->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1816 "A5_30.tab.c"
    break;

  case 26:
#line 334 "A5_30.y"
        {
            yyinfo("multiplicative_expression -> multiplicative_expression DIVIDE unary_expression\n");
            // Indicates division
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].arr)->array)) {     // Check for type compatibility
                (yyval.expr) = new Expression();                                                  // Generate new expression
                (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType((yyvsp[-2].expr)->addr->sym_type->type));    // Generate new temporary
                emit("/", (yyval.expr)->addr->name, (yyvsp[-2].expr)->addr->name, (yyvsp[0].arr)->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1833 "A5_30.tab.c"
    break;

  case 27:
#line 347 "A5_30.y"
        {
            yyinfo("multiplicative_expression -> multiplicative_expression MODULO unary_expression\n");
            // Indicates modulo
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].arr)->array)) {     // Check for type compatibility
                (yyval.expr) = new Expression();                                                  // Generate new expression
                (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType((yyvsp[-2].expr)->addr->sym_type->type));    // Generate new temporary
                emit("%", (yyval.expr)->addr->name, (yyvsp[-2].expr)->addr->name, (yyvsp[0].arr)->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1850 "A5_30.tab.c"
    break;

  case 28:
#line 363 "A5_30.y"
        {
            yyinfo("additive_expression -> multiplicative_expression\n");
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 1859 "A5_30.tab.c"
    break;

  case 29:
#line 368 "A5_30.y"
        {   
            yyinfo("additive_expression -> additive_expression ADD multiplicative_expression\n");
            // Indicates addition
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {       // Check for type compatibility
                (yyval.expr) = new Expression();                                                  // Generate new expression
                (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType((yyvsp[-2].expr)->addr->sym_type->type));    // Generate new temporary
                emit("+", (yyval.expr)->addr->name, (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);                 // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1876 "A5_30.tab.c"
    break;

  case 30:
#line 381 "A5_30.y"
        {
            yyinfo("additive_expression -> additive_expression SUBTRACT multiplicative_expression\n");
            // Indicates subtraction
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {       // Check for type compatibility
                (yyval.expr) = new Expression();                                                  // Generate new expression
                (yyval.expr)->addr = SymbolTable::gentemp(new SymbolType((yyvsp[-2].expr)->addr->sym_type->type));    // Generate new temporary
                emit("-", (yyval.expr)->addr->name, (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);                 // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1893 "A5_30.tab.c"
    break;

  case 31:
#line 398 "A5_30.y"
        {
            yyinfo("relational_expression -> additive_expression\n");
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 1902 "A5_30.tab.c"
    break;

  case 32:
#line 403 "A5_30.y"
        {
            yyinfo("relational_expression -> relational_expression LESS_THAN additive_expression\n");
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("<", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);    // Emit "if x < y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1921 "A5_30.tab.c"
    break;

  case 33:
#line 418 "A5_30.y"
        {
            yyinfo("relational_expression -> relational_expression GREATER_THAN additive_expression\n");
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit(">", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);    // Emit "if x > y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1940 "A5_30.tab.c"
    break;

  case 34:
#line 433 "A5_30.y"
        {
            yyinfo("relational_expression -> relational_expression LESS_THAN_EQUALS additive_expression\n");
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("<=", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);   // Emit "if x <= y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1959 "A5_30.tab.c"
    break;

  case 35:
#line 448 "A5_30.y"
        {
            yyinfo("relational_expression -> relational_expression GREATER_THAN_EQUALS additive_expression\n");
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit(">=", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);   // Emit "if x >= y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 1978 "A5_30.tab.c"
    break;

  case 36:
#line 466 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 1986 "A5_30.tab.c"
    break;

  case 37:
#line 470 "A5_30.y"
        {
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                convertBoolToInt((yyvsp[-2].expr));                           // Convert bool to int
                convertBoolToInt((yyvsp[0].expr));
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("==", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);   // Emit "if x == y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 2006 "A5_30.tab.c"
    break;

  case 38:
#line 486 "A5_30.y"
        {
            if(typecheck((yyvsp[-2].expr)->addr, (yyvsp[0].expr)->addr)) {                   // Check for type compatibility
                convertBoolToInt((yyvsp[-2].expr));                           // Convert bool to int
                convertBoolToInt((yyvsp[0].expr));
                (yyval.expr) = new Expression();                          // Generate new expression of type bool
                (yyval.expr)->type = "bool";
                (yyval.expr)->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                (yyval.expr)->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("!=", "", (yyvsp[-2].expr)->addr->name, (yyvsp[0].expr)->addr->name);   // Emit "if x != y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
#line 2026 "A5_30.tab.c"
    break;

  case 39:
#line 506 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 2034 "A5_30.tab.c"
    break;

  case 40:
#line 510 "A5_30.y"
        {
            /*
                Here, we have augmented the grammar with the non-terminal M to facilitate backpatching
            */
            convertIntToBool((yyvsp[-3].expr));                                   // Convert the expressions from int to bool
            convertIntToBool((yyvsp[0].expr));
            (yyval.expr) = new Expression();                                  // Create a new bool expression for the result
            (yyval.expr)->type = "bool";
            backpatch((yyvsp[-3].expr)->truelist, (yyvsp[-1].instr));                            // Backpatching
            (yyval.expr)->truelist = (yyvsp[0].expr)->truelist;                            // Generate truelist from truelist of $4
            (yyval.expr)->falselist = merge((yyvsp[-3].expr)->falselist, (yyvsp[0].expr)->falselist);    // Generate falselist by merging the falselists of $1 and $4
        }
#line 2051 "A5_30.tab.c"
    break;

  case 41:
#line 526 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 2059 "A5_30.tab.c"
    break;

  case 42:
#line 530 "A5_30.y"
        {
            convertIntToBool((yyvsp[-3].expr));                                   // Convert the expressions from int to bool
            convertIntToBool((yyvsp[0].expr));
            (yyval.expr) = new Expression();                                  // Create a new bool expression for the result
            (yyval.expr)->type = "bool";
            backpatch((yyvsp[-3].expr)->falselist, (yyvsp[-1].instr));                           // Backpatching
            (yyval.expr)->falselist = (yyvsp[0].expr)->falselist;                          // Generate falselist from falselist of $4
            (yyval.expr)->truelist = merge((yyvsp[-3].expr)->truelist, (yyvsp[0].expr)->truelist);       // Generate truelist by merging the truelists of $1 and $4
        }
#line 2073 "A5_30.tab.c"
    break;

  case 43:
#line 543 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 2081 "A5_30.tab.c"
    break;

  case 44:
#line 547 "A5_30.y"
        {   
            /*
                Note the augmented grammar with the non-terminals M and N
            */
            // printf("here");
            (yyval.expr)->addr = SymbolTable::gentemp((yyvsp[-4].expr)->addr->sym_type);      // Generate temporary for the expression
            (yyval.expr)->addr->update_symbol((yyvsp[-4].expr)->addr->sym_type);
            emit("=", (yyval.expr)->addr->name, (yyvsp[0].expr)->addr->name);            // Assign the conditional expression
            list<int> l1 = makelist(nextinstr());
            emit("goto", "");                                   // Prevent fall-through
            backpatch((yyvsp[-3].stmt)->nextlist, nextinstr());               // Make list with next instruction
            emit("=", (yyval.expr)->addr->name, (yyvsp[-4].expr)->addr->name);
            list<int> l2 = makelist(nextinstr());               // Make list with next instruction
            l1 = merge(l1, l2);                                 // Merge the two lists
            emit("goto", "");                                   // Prevent fall-through
            backpatch((yyvsp[-7].stmt)->nextlist, nextinstr());               // Backpatching
            convertIntToBool((yyvsp[-8].expr));                               // Convert expression to bool
            backpatch((yyvsp[-8].expr)->truelist, (yyvsp[-5].instr));                        // When $1 is true, control goes to $4 (expression)
            backpatch((yyvsp[-8].expr)->falselist, (yyvsp[-1].instr));                       // When $1 is false, control goes to $8 (conditional_expression)
            backpatch(l1, nextinstr());
        }
#line 2107 "A5_30.tab.c"
    break;

  case 45:
#line 571 "A5_30.y"
        {   
            // Stores the next instruction value, and helps in backpatching
            (yyval.instr) = nextinstr();
        }
#line 2116 "A5_30.tab.c"
    break;

  case 46:
#line 578 "A5_30.y"
        {
            // Helps in control flow
            (yyval.stmt) = new Statement();
            (yyval.stmt)->nextlist = makelist(nextinstr());
            emit("goto", "");
        }
#line 2127 "A5_30.tab.c"
    break;

  case 47:
#line 588 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);    // Simple assignment
        }
#line 2135 "A5_30.tab.c"
    break;

  case 48:
#line 592 "A5_30.y"
        {
            if((yyvsp[-2].arr)->arr_type == "arr") {        // If atype is "arr", convert and emit
                (yyvsp[0].expr)->addr = convertType((yyvsp[0].expr)->addr, (yyvsp[-2].arr)->type->type);
                emit("[]=", (yyvsp[-2].arr)->array->name, (yyvsp[-2].arr)->addr->name, (yyvsp[0].expr)->addr->name);
            }
            else if((yyvsp[-2].arr)->arr_type == "ptr") {   // If atype is "ptr", emit 
                emit("*=", (yyvsp[-2].arr)->array->name, (yyvsp[0].expr)->addr->name);
            }
            else {
                (yyvsp[0].expr)->addr = convertType((yyvsp[0].expr)->addr, (yyvsp[-2].arr)->array->sym_type->type);
                emit("=", (yyvsp[-2].arr)->array->name, (yyvsp[0].expr)->addr->name);
            }
            (yyval.expr) = (yyvsp[0].expr);
        }
#line 2154 "A5_30.tab.c"
    break;

  case 49:
#line 610 "A5_30.y"
        { /* Ignored */ }
#line 2160 "A5_30.tab.c"
    break;

  case 50:
#line 616 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[0].expr);
        }
#line 2168 "A5_30.tab.c"
    break;

  case 51:
#line 625 "A5_30.y"
        { /* Ignored */ }
#line 2174 "A5_30.tab.c"
    break;

  case 52:
#line 632 "A5_30.y"
        {
            (yyval.symptr) = (yyvsp[0].symptr);
        }
#line 2182 "A5_30.tab.c"
    break;

  case 53:
#line 636 "A5_30.y"
        {   
            // Find out the initial value and emit it
            if((yyvsp[0].symptr)->val != "") {
                (yyvsp[-2].symptr)->val = (yyvsp[0].symptr)->val;
            }
            emit("=", (yyvsp[-2].symptr)->name, (yyvsp[0].symptr)->name);
        }
#line 2194 "A5_30.tab.c"
    break;

  case 54:
#line 647 "A5_30.y"
        {
            prevType = "void";   // Store the latest encountered type in prevType
        }
#line 2202 "A5_30.tab.c"
    break;

  case 55:
#line 651 "A5_30.y"
        {
            prevType = "char";   // Store the latest encountered type in prevType
        }
#line 2210 "A5_30.tab.c"
    break;

  case 56:
#line 655 "A5_30.y"
        {
            prevType = "int";    // Store the latest encountered type in prevType
        }
#line 2218 "A5_30.tab.c"
    break;

  case 57:
#line 663 "A5_30.y"
        {
            SymbolType* t = (yyvsp[-1].symType);
            // In case of multi-dimesnional arrays, keep on going down in a hierarchial fashion to get the base type
            while(t->arrElementType != NULL) {
                t = t->arrElementType;
            }
            t->arrElementType = (yyvsp[0].symptr)->sym_type;  // Store the base type
            (yyval.symptr) = (yyvsp[0].symptr)->update_symbol((yyvsp[-1].symType));    // Update
        }
#line 2232 "A5_30.tab.c"
    break;

  case 58:
#line 673 "A5_30.y"
        {/* Ignored */}
#line 2238 "A5_30.tab.c"
    break;

  case 59:
#line 677 "A5_30.y"
        {
            (yyval.symptr) = (yyvsp[0].symptr)->update_symbol(new SymbolType(prevType));   // For an identifier, update the type to prevType
            currentSym = (yyval.symptr);                         // Update pointer to current symbol
        }
#line 2247 "A5_30.tab.c"
    break;

  case 60:
#line 684 "A5_30.y"
        {
            (yyval.symptr) = (yyvsp[0].symptr)->update_symbol(new SymbolType(prevType));   // For an identifier, update the type to prevType
            currentSym = (yyval.symptr);                         // Update pointer to current symbol
        }
#line 2256 "A5_30.tab.c"
    break;

  case 61:
#line 689 "A5_30.y"
        {
            SymbolType* t = (yyvsp[-3].symptr)->sym_type;
            SymbolType* prev = NULL;
            // Keep moving recursively to get the base type
            while(t->type == "arr") {
                prev = t;
                t = t->arrElementType;
            }
            if(prev == NULL) {
                // int temp = atoi($3->addr->val.c_str());                // Get initial value
                int temp = (yyvsp[-1].intval);         // Get initial value
                SymbolType* tp = new SymbolType("arr", (yyvsp[-3].symptr)->sym_type, temp); // Create that type
                (yyval.symptr) = (yyvsp[-3].symptr)->update_symbol(tp);                                    // Update the symbol table for that symbol
            }
            else {
                // int temp = atoi($3->addr->val.c_str());                // Get initial value
                int temp = (yyvsp[-1].intval);         // Get initial value
                prev->arrElementType = new SymbolType("arr", t, temp);         // Create that type
                (yyval.symptr) = (yyvsp[-3].symptr)->update_symbol((yyvsp[-3].symptr)->sym_type);                              // Update the symbol table for that symbol
            }
        }
#line 2282 "A5_30.tab.c"
    break;

  case 62:
#line 712 "A5_30.y"
        {
            SymTbl_Current->name = (yyvsp[-4].symptr)->name;
            if((yyvsp[-4].symptr)->sym_type->type != "void") {
                Symbol* s = SymTbl_Current->lookup("return");    // Lookup for return value
                s->update_symbol((yyvsp[-4].symptr)->sym_type);
            }
            (yyvsp[-4].symptr)->nestedTblPtr = SymTbl_Current;
            SymTbl_Current->parent = SymTbl_Global;   // Update parent symbol table
            switchTable(SymTbl_Global);          // Switch current table to point to the global symbol table
            currentSym = (yyval.symptr);             // Update current symbol
        }
#line 2298 "A5_30.tab.c"
    break;

  case 63:
#line 724 "A5_30.y"
        {
            SymTbl_Current->name = (yyvsp[-3].symptr)->name;
            if((yyvsp[-3].symptr)->sym_type->type != "void") {
                Symbol* s = SymTbl_Current->lookup("return");    // Lookup for return value
                s->update_symbol((yyvsp[-3].symptr)->sym_type);
            }
            (yyvsp[-3].symptr)->nestedTblPtr = SymTbl_Current;
            SymTbl_Current->parent = SymTbl_Global;   // Update parent symbol table
            switchTable(SymTbl_Global);          // Switch current table to point to the global symbol table
            currentSym = (yyval.symptr);             // Update current symbol                       // Update pointer to current symbol
        }
#line 2314 "A5_30.tab.c"
    break;

  case 64:
#line 740 "A5_30.y"
        {
            (yyval.symType) = new SymbolType("ptr");     //  Create new type "ptr"
        }
#line 2322 "A5_30.tab.c"
    break;

  case 65:
#line 748 "A5_30.y"
        { /* Ignored */ }
#line 2328 "A5_30.tab.c"
    break;

  case 66:
#line 750 "A5_30.y"
        { /* Ignored */ }
#line 2334 "A5_30.tab.c"
    break;

  case 67:
#line 755 "A5_30.y"
        {
            SymbolType* t = (yyvsp[-1].symType);
            // In case of multi-dimesnional arrays, keep on going down in a hierarchial fashion to get the base type
            while(t->arrElementType != NULL) {
                t = t->arrElementType;
            }
            t->arrElementType = (yyvsp[0].symptr)->sym_type;  // Store the base type
            (yyval.symptr) = (yyvsp[0].symptr)->update_symbol((yyvsp[-1].symType));    // Update
        }
#line 2348 "A5_30.tab.c"
    break;

  case 68:
#line 765 "A5_30.y"
        {/* Ignored */}
#line 2354 "A5_30.tab.c"
    break;

  case 69:
#line 770 "A5_30.y"
        { /* Ignored */ }
#line 2360 "A5_30.tab.c"
    break;

  case 70:
#line 772 "A5_30.y"
        { /* Ignored */ }
#line 2366 "A5_30.tab.c"
    break;

  case 71:
#line 779 "A5_30.y"
        {
            (yyval.symptr) = (yyvsp[0].expr)->addr;   // Simple assignment
        }
#line 2374 "A5_30.tab.c"
    break;

  case 72:
#line 786 "A5_30.y"
        {
            yyinfo("compound_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2383 "A5_30.tab.c"
    break;

  case 73:
#line 791 "A5_30.y"
        {
            yyinfo("expression_statement\n");
            (yyval.stmt) = new Statement();           // Create new statement
            (yyval.stmt)->nextlist = (yyvsp[0].expr)->nextlist;    // Assign same nextlist
        }
#line 2393 "A5_30.tab.c"
    break;

  case 74:
#line 797 "A5_30.y"
        {
            yyinfo("selection_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2402 "A5_30.tab.c"
    break;

  case 75:
#line 802 "A5_30.y"
        {
            yyinfo("iteration_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2411 "A5_30.tab.c"
    break;

  case 76:
#line 807 "A5_30.y"
        {
            yyinfo("jump_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2420 "A5_30.tab.c"
    break;

  case 77:
#line 816 "A5_30.y"
        {
            yyinfo("loop_statement -> expression_statement\n");
            (yyval.stmt) = new Statement();           // Create new statement
            (yyval.stmt)->nextlist = (yyvsp[0].expr)->nextlist;    // Assign same nextlist
        }
#line 2430 "A5_30.tab.c"
    break;

  case 78:
#line 822 "A5_30.y"
        {
            yyinfo("loop_statement -> selection_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2439 "A5_30.tab.c"
    break;

  case 79:
#line 827 "A5_30.y"
        {
            yyinfo("loop_statement -> iteration_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2448 "A5_30.tab.c"
    break;

  case 80:
#line 832 "A5_30.y"
        {
            yyinfo("loop_statement -> jump_statement\n");
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2457 "A5_30.tab.c"
    break;

  case 81:
#line 841 "A5_30.y"
        {
            /*
                Here, the grammar has been augmented with non-terminals like X and change_table to allow creation of nested symbol tables
            */
            (yyval.stmt) = (yyvsp[-1].stmt);
            switchTable(SymTbl_Current->parent);     // Update current symbol table
        }
#line 2469 "A5_30.tab.c"
    break;

  case 82:
#line 852 "A5_30.y"
        {
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2477 "A5_30.tab.c"
    break;

  case 83:
#line 856 "A5_30.y"
        {
            (yyval.stmt) = new Statement();   // Create new statement
        }
#line 2485 "A5_30.tab.c"
    break;

  case 84:
#line 863 "A5_30.y"
        {
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2493 "A5_30.tab.c"
    break;

  case 85:
#line 867 "A5_30.y"
        {   
            /*
                This production rule has been augmented with the non-terminal M
            */
            (yyval.stmt) = (yyvsp[0].stmt);
            backpatch((yyvsp[-2].stmt)->nextlist, (yyvsp[-1].instr));    // After $1, move to block_item via $2
        }
#line 2505 "A5_30.tab.c"
    break;

  case 86:
#line 878 "A5_30.y"
        {
            (yyval.stmt) = new Statement();   // Create new statement
        }
#line 2513 "A5_30.tab.c"
    break;

  case 87:
#line 882 "A5_30.y"
        {
            (yyval.stmt) = (yyvsp[0].stmt);    // Simple assignment
        }
#line 2521 "A5_30.tab.c"
    break;

  case 88:
#line 889 "A5_30.y"
        {
            (yyval.expr) = (yyvsp[-1].expr);    // Simple assignment
        }
#line 2529 "A5_30.tab.c"
    break;

  case 89:
#line 893 "A5_30.y"
        {
            (yyval.expr) = new Expression();  // Create new expression
        }
#line 2537 "A5_30.tab.c"
    break;

  case 90:
#line 900 "A5_30.y"
        {
            /*
                This production rule has been augmented for control flow
            */
            backpatch((yyvsp[-4].stmt)->nextlist, nextinstr());                   // nextlist of N now has nextinstr
            convertIntToBool((yyvsp[-5].expr));                                   // Convert expression to bool
            (yyval.stmt) = new Statement();                                   // Create new statement
            backpatch((yyvsp[-5].expr)->truelist, (yyvsp[-2].instr));                            // Backpatching - if expression is true, go to M
            // Merge falselist of expression, nextlist of statement and nextlist of the last N
            list<int> temp = merge((yyvsp[-5].expr)->falselist, (yyvsp[-1].stmt)->nextlist);
            (yyval.stmt)->nextlist = merge((yyvsp[0].stmt)->nextlist, temp);
        }
#line 2554 "A5_30.tab.c"
    break;

  case 91:
#line 913 "A5_30.y"
        {
            /*
                This production rule has been augmented for control flow
            */
            backpatch((yyvsp[-7].stmt)->nextlist, nextinstr());                   // nextlist of N now has nextinstr
            convertIntToBool((yyvsp[-8].expr));                                   // Convert expression to bool
            (yyval.stmt) = new Statement();                                   // Create new statement
            backpatch((yyvsp[-8].expr)->truelist, (yyvsp[-5].instr));                            // Backpatching - if expression is true, go to first M, else go to second M
            backpatch((yyvsp[-8].expr)->falselist, (yyvsp[-1].instr));
            // Merge nextlist of statement, nextlist of N and nextlist of the last statement
            list<int> temp = merge((yyvsp[-4].stmt)->nextlist, (yyvsp[-3].stmt)->nextlist);
            (yyval.stmt)->nextlist = merge((yyvsp[0].stmt)->nextlist, temp);
        }
#line 2572 "A5_30.tab.c"
    break;

  case 92:
#line 931 "A5_30.y"
        {
            /*
                This production rule has been augmented with non-terminals like F, X, change_table and M to handle the control flow, 
                backpatching, detect the kind of loop, create a separate symbol table for the loop block and give it an appropriate name
            */
            (yyval.stmt) = new Statement();                   // Create a new statement
            convertIntToBool((yyvsp[-6].expr));                   // Convert expression to bool
            backpatch((yyvsp[-6].expr)->truelist, (yyvsp[-1].instr));           // Go to M3 if expression is true
            backpatch((yyvsp[-3].stmt)->nextlist, (yyvsp[-7].instr));           // Go back to M1 after N
            backpatch((yyvsp[0].stmt)->nextlist, (yyvsp[-5].instr));           // Go back to expression after loop_statement
            emit("goto", to_string((yyvsp[-5].instr)));   // Emit to prevent fall-through
            (yyval.stmt)->nextlist = (yyvsp[-6].expr)->falselist;           // Exit loop if expression_statement is false
            BlockName = "";
            switchTable(SymTbl_Current->parent);
        }
#line 2592 "A5_30.tab.c"
    break;

  case 93:
#line 947 "A5_30.y"
        {
            /*
                This production rule has been augmented with non-terminals like F, X, change_table and M to handle the control flow, 
                backpatching, detect the kind of loop, create a separate symbol table for the loop block and give it an appropriate name
            */
            (yyval.stmt) = new Statement();                   // Create a new statement
            convertIntToBool((yyvsp[-8].expr));                   // Convert expression to bool
            backpatch((yyvsp[-8].expr)->truelist, (yyvsp[-3].instr));           // Go to M3 if expression is true
            backpatch((yyvsp[-5].stmt)->nextlist, (yyvsp[-9].instr));           // Go back to M1 after N
            backpatch((yyvsp[-1].stmt)->nextlist, (yyvsp[-7].instr));           // Go back to expression after loop_statement
            emit("goto", to_string((yyvsp[-7].instr)));            // Emit to prevent fall-through
            (yyval.stmt)->nextlist = (yyvsp[-8].expr)->falselist;           // Exit loop if expression_statement is false
            BlockName = "";
            switchTable(SymTbl_Current->parent);
        }
#line 2612 "A5_30.tab.c"
    break;

  case 94:
#line 965 "A5_30.y"
        {   
            /*
            This non-terminal indicates the start of a for loop
            */
            BlockName = "FOR";
        }
#line 2623 "A5_30.tab.c"
    break;

  case 95:
#line 975 "A5_30.y"
        {   
            // Used for creating new nested symbol tables for nested blocks
            string newST = SymTbl_Current->name + "." + BlockName + "$" + to_string(SymTbl_Count++);  // Generate name for new symbol table
            Symbol* sym = SymTbl_Current->lookup(newST);
            sym->nestedTblPtr = new SymbolTable(newST);  // Create new symbol table
            sym->name = newST;
            sym->nestedTblPtr->parent = SymTbl_Current;
            sym->sym_type = new SymbolType("block");    // The type will be "block"
            currentSym = sym;    // Change the current symbol pointer
        }
#line 2638 "A5_30.tab.c"
    break;

  case 96:
#line 988 "A5_30.y"
        {   
            // Used for changing the symbol table on encountering functions
            if(currentSym->nestedTblPtr != NULL) {
                // If the symbol table already exists, switch to that table
                switchTable(currentSym->nestedTblPtr);
                emit("label", SymTbl_Current->name);
            }
            else {
                // If the symbol table does not exist already, create it and switch to it
                switchTable(new SymbolTable(""));
            }
        }
#line 2655 "A5_30.tab.c"
    break;

  case 97:
#line 1004 "A5_30.y"
        {
            (yyval.stmt) = new Statement();
            emit("return", (yyvsp[-1].expr)->addr->name);  // Emit return alongwith return value
        }
#line 2664 "A5_30.tab.c"
    break;

  case 98:
#line 1009 "A5_30.y"
        {
            (yyval.stmt) = new Statement();
            emit("return", "");             // Emit return without any return value
        }
#line 2673 "A5_30.tab.c"
    break;

  case 99:
#line 1017 "A5_30.y"
        { /* Ignored */ }
#line 2679 "A5_30.tab.c"
    break;

  case 100:
#line 1019 "A5_30.y"
        { /* Ignored */ }
#line 2685 "A5_30.tab.c"
    break;

  case 101:
#line 1024 "A5_30.y"
        { /* Ignored */ }
#line 2691 "A5_30.tab.c"
    break;

  case 102:
#line 1026 "A5_30.y"
        { /* Ignored */ }
#line 2697 "A5_30.tab.c"
    break;

  case 103:
#line 1031 "A5_30.y"
        {   
            SymTbl_Current->parent = SymTbl_Global;
            SymTbl_Count = 0;
            switchTable(SymTbl_Global);          // After reaching end of a function, change cureent symbol table to the global symbol table
        }
#line 2707 "A5_30.tab.c"
    break;

  case 104:
#line 1040 "A5_30.y"
        { /* Ignored */ }
#line 2713 "A5_30.tab.c"
    break;

  case 105:
#line 1042 "A5_30.y"
        { /* Ignored */ }
#line 2719 "A5_30.tab.c"
    break;

  case 106:
#line 1047 "A5_30.y"
        { /* Ignored */ }
#line 2725 "A5_30.tab.c"
    break;

  case 107:
#line 1049 "A5_30.y"
        { /* Ignored */ }
#line 2731 "A5_30.tab.c"
    break;


#line 2735 "A5_30.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1052 "A5_30.y"


void yyerror(string s) {
    /*
        This function prints any error encountered while parsing
    */
    cout << "Error occurred: " << s << endl;
    cout << "Line no.: " << yylineno << endl;
    cout << "Unable to parse: " << yytext << endl; 
}
void yyinfo(string s) {
    #ifdef DEBUG
        cout << s;
    #endif
}
