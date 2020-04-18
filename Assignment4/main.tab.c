/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "main.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ast.h"
#include "files.h"

extern int yyparse();
extern int yylex();
void yyerror(char* s);
extern int yylineno;

#line 84 "main.tab.c"

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
#ifndef YY_YY_MAIN_TAB_H_INCLUDED
# define YY_YY_MAIN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SELECT = 258,
    PROJECT = 259,
    CARTESIAN_PRODUCT = 260,
    EQUI_JOIN = 261,
    L = 262,
    G = 263,
    LE = 264,
    GE = 265,
    EQ = 266,
    NEQ = 267,
    LB = 268,
    RB = 269,
    AND = 270,
    OR = 271,
    NOT = 272,
    COMMA = 273,
    DOT = 274,
    NAME = 275,
    STRING = 276,
    NUM = 277,
    NEWLINE = 278,
    ER = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "main.y"


	struct ast_tree * tree;
	int operator_type;
	int num;
	char* str;
	struct attr_list * list;

#line 161 "main.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAIN_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

#define YYUNDEFTOK  2
#define YYMAXUTOK   279

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    47,    47,    48,    49,    49,    50,    50,    52,   220,
     409,   504,   706,   710,   716,   721,   730,   735,   740,   745,
     753,   758,   763,   768,   773,   778,   783,   791,   796,   801,
     810,   814,   818,   824,   830,   834,   843,   850,   858,   868,
     882,   887,   894,   912,   919,   928,   936,   944,   950,   959
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "PROJECT", "CARTESIAN_PRODUCT",
  "EQUI_JOIN", "L", "G", "LE", "GE", "EQ", "NEQ", "LB", "RB", "AND", "OR",
  "NOT", "COMMA", "DOT", "NAME", "STRING", "NUM", "NEWLINE", "ER",
  "$accept", "statement_list", "$@1", "$@2", "statement", "condition_equi",
  "condition", "expr", "at", "op", "op2", "attr_list", "X", "Y",
  "BRACK_NAME", "BRACK_NUM", "BRACK_STRING", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

#define YYPACT_NINF -86

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-86)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      31,    -3,     3,    11,     8,   -86,    22,    64,   -86,    26,
      20,     8,   -86,    77,    31,   -86,    31,    31,    26,    26,
     -86,   -86,    37,    21,    86,   -86,    80,    86,    52,    20,
      93,    85,    70,    92,   113,   -86,   -86,   -86,    96,   101,
       5,    69,    39,   -86,   109,    26,    26,   -86,   -86,   -86,
     -86,   -86,   -86,   -86,    53,    -5,     8,    20,    20,    20,
     101,     5,   110,    20,    20,   -86,   111,   118,   -86,   -86,
     -86,   -86,     8,   -86,   -86,    53,   -86,   -86,    -5,   -86,
     -86,   -86,   -86,   -86,   -86,   -86,     8,   -86,   -86,     8,
      36,   112,   114,   115,   116,   117,    36,   119,   121,    80,
     -86,   -86,   -86,   120,    56,   122,    20,   -86,     8,   123,
     125,    36,   -86,   -86
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     4,     0,     3,     6,     0,
       0,     0,    44,     0,     0,     1,     0,     0,     0,     0,
      48,    46,     0,    18,     0,    41,    40,     0,     0,     0,
       0,    39,    38,     0,     0,     5,     2,     7,     0,    41,
      40,     0,     0,    19,     0,     0,     0,    30,    31,    32,
      33,    34,    35,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,     0,    26,    43,
      47,    49,     0,    16,    17,     0,    24,    27,     0,    25,
      28,    29,    42,    21,    22,    23,     0,    37,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     9,    10,     0,     0,     0,     0,    15,     0,    14,
       0,     0,    11,    13
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   100,   -86,   -86,   -86,   -85,   -16,   -86,   -86,   124,
     -15,    57,    54,    -6,    -4,   -13,   -17
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,    14,    17,     7,    97,    22,    23,    53,    57,
      58,    30,    24,    25,    26,    27,    28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      13,    42,    38,    43,    31,    41,    32,    33,    78,    55,
       9,   103,    39,    59,    40,    12,    20,    21,    10,    65,
       8,    11,    15,    60,    56,    61,   113,    59,    12,    73,
      74,   -12,     1,    29,     2,     3,    45,    46,    81,    18,
      12,    77,    80,    19,     4,    44,    12,    20,    21,    96,
      51,    52,    82,    71,   -12,     5,    12,    31,    31,    32,
      32,    93,    92,    51,    52,    92,    75,   106,    91,    60,
      69,    61,    60,    12,    61,    21,    47,    48,    49,    50,
      51,    52,    94,    70,    98,    95,    99,    16,    64,    56,
     104,    34,    61,    47,    48,    49,    50,    51,    52,    56,
     109,    62,    99,    63,   110,    98,    65,    99,    76,    79,
      68,    83,    84,    85,    35,    69,    36,    37,    66,    67,
      87,    88,    72,    86,    89,    90,   100,   105,    70,    71,
     101,   102,   106,     0,   107,   108,     0,     0,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,    54
};

static const yytype_int8 yycheck[] =
{
       4,    18,    18,    19,    10,    18,    10,    11,    13,    24,
       7,    96,    18,    28,    18,    20,    21,    22,     7,    14,
      23,    13,     0,    29,    19,    29,   111,    42,    20,    45,
      46,     0,     1,    13,     3,     4,    15,    16,    55,    13,
      20,    54,    55,    17,    13,     8,    20,    21,    22,    13,
      11,    12,    56,    14,    23,    24,    20,    63,    64,    63,
      64,    78,    75,    11,    12,    78,    13,    11,    72,    75,
      14,    75,    78,    20,    78,    22,     7,     8,     9,    10,
      11,    12,    86,    14,    90,    89,    90,    23,    18,    19,
      96,    14,    96,     7,     8,     9,    10,    11,    12,    19,
     106,     8,   106,    18,   108,   111,    14,   111,    54,    55,
      14,    57,    58,    59,    14,    14,    16,    17,     5,     6,
      63,    64,    13,    13,    13,     7,    14,     8,    14,    14,
      14,    14,    11,    -1,    14,    13,    -1,    -1,    15,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    13,    24,    26,    29,    23,     7,
       7,    13,    20,    39,    27,     0,    23,    28,    13,    17,
      21,    22,    31,    32,    37,    38,    39,    40,    41,    13,
      36,    38,    39,    39,    14,    26,    26,    26,    31,    38,
      39,    40,    41,    31,     8,    15,    16,     7,     8,     9,
      10,    11,    12,    33,    34,    35,    19,    34,    35,    35,
      38,    39,     8,    18,    18,    14,     5,     6,    14,    14,
      14,    14,    13,    31,    31,    13,    37,    40,    13,    37,
      40,    41,    39,    37,    37,    37,    13,    36,    36,    13,
       7,    39,    40,    41,    39,    39,    13,    30,    38,    39,
      14,    14,    14,    30,    38,     8,    11,    14,    13,    38,
      39,    15,    14,    30
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    25,    26,    26,    27,    26,    28,    26,    29,    29,
      29,    29,    29,    30,    30,    30,    31,    31,    31,    31,
      32,    32,    32,    32,    32,    32,    32,    33,    33,    33,
      34,    34,    34,    34,    35,    35,    36,    36,    36,    36,
      37,    37,    38,    38,    39,    39,    40,    40,    41,    41
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     0,     3,     0,     4,     7,     7,
       7,    10,     0,     5,     3,     3,     3,     3,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     3,     3,     1,     3,     1,     3,     1,     3
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
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
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

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
  case 4:
#line 49 "main.y"
    {printf("INVALID Character here \n");}
#line 1325 "main.tab.c"
    break;

  case 6:
#line 50 "main.y"
    {printf("Syntax error \n");}
#line 1331 "main.tab.c"
    break;

  case 8:
#line 53 "main.y"
    {
			printf("Syntax is valid \n\n");




			char filename[100];
			memset(filename, 0, 100);

			sprintf(filename, "tables/%s.csv", (yyvsp[-1].tree)->data.str);  // tables folder will hold all the csv files

			if (!if_file_exist(filename)){  // check if the table exist
				printf("No file name of the specified type \n");


			}
			else{

		// create a table of variables and their corresponding values  for each row of the tables

				char* variable[100];  // will hold the attribute name of the table
				char* value[100];   // will hold the corresponding value of the attributes in string format
				int type[100];      // type of the attribute


				FILE * file = fopen(filename, "r");

				char read[2000];
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;

				char * field = strtok(read, ",");
				int i = 0;

				// store the attribute name in variable[100]
				while(field != NULL){
					variable[i] = strdup(field);
					// printf("%s\n", variable[i]);
					i++;
					field = strtok(NULL, ",");
				}

				int num_of_fields = i;

				for(int i = 0; i < num_of_fields; i++){     // store the  names in the form tablename.attribute
					char  temp[200];
					memset(temp, 0, 200);

					sprintf(temp, "%s.%s", (yyvsp[-1].tree)->data.str, variable[i]);
					// printf("%s\n", temp);
					variable[i+num_of_fields] = strdup(temp);

				}

				memset(read, 0, 2000);

				fgets(read, 2000, file);   // reads the attribute type from the file
				read[strcspn(read, "\n")] = 0;

				field = strtok(read, ",");
				i = 0;
				while(field != NULL){       // store the attribute type
					char* temp = strdup(field);
					// printf("%s\n", temp);

					if(strcmp(temp, "int") == 0){
						type[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type[i] = 1;
					}
					i++;
					field = strtok(NULL, ",");
				}
				for(int i = 0; i < num_of_fields; i++){   // store the attribute type of attributes of form tablename.attribute

					type[num_of_fields+i] = type[i];
				}

				int error = 1;   // will store the error code if the error occurs

				for(int i = 0; i < num_of_fields; i++){   // print the attribute names
					printf("%s ", variable[i]);

				}

				printf("\n\n");

				memset(read, 0, 2000);

				int num_of_results = 0;
				while(fgets (read, 2000, file)){    // start reading the data rows
					read[strcspn(read, "\n")] = 0;
					field = strtok(read, ",");

					int i = 0;
					while(field !=  NULL){    // stores the attribute value in value array
						if (type[i] == 0){  // number type
							value[i] = strdup(field);
							value[i+num_of_fields] = value[i];

						}

						else {    // string type
							char * temp = strdup(field);
							temp[strlen(temp)-1] = '\0';
							value[i] = strdup(temp+1);
							value[i+num_of_fields] = value[i];

						}
						i++;
						field = strtok(NULL, ",");
					}

					// now value has the current data row value

					int currentrow  = ast_eval((yyvsp[-4].tree), variable, value, type, num_of_fields, &error);   // call the ast function

					if (error != 1){    // if error is changed inside ast_eval
						break;
					}

					if(currentrow){    // if ast_eval return 1 pritn the current data row

						num_of_results++;
						for(int i = 0; i < num_of_fields; i++){
							printf("%s ", value[i]);

						}

						printf("\n");
					}
					memset(read, 0, 2000);

				}

				if (error != 1){  // there is a error
					printf("There is some error in the query error code %d . It means:", error);
					if(error == 0){
						printf("Invalid arguement in evaluate function");
					}
					if(error == 2){
						printf("Variable in condition is not in the table");
					}
					if(error == 3){
						printf("Type mismatch inbetween two quantities");
					}
				}

				if(error == 1 && num_of_results == 0){
					printf("There were no successful matches \n");
				}

				if (error == 1 && num_of_results > 0){
					printf("\nNumber of matches: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}

				fclose(file);


			}


		}
#line 1502 "main.tab.c"
    break;

  case 9:
#line 222 "main.y"
    {

			printf("Syntax is valid \n\n");

//			printattrlist($3);


			char filename[100];
			memset(filename, 0, 100);

			sprintf(filename, "tables/%s.csv", (yyvsp[-1].tree)->data.str);

			if (!if_file_exist(filename)){
				printf("No file name of the specified type \n");


			}
			else{


// first fill variable with variable names, value with the variable values and type with the variable type
				char* variable[100];
				char* value[100];
				int type[100];


				FILE * file = fopen(filename, "r");

				char read[2000];
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;

				char * field = strtok(read, ",");
				int i = 0;
				while(field != NULL){
					variable[i] = strdup(field);
					i++;
					field = strtok(NULL, ",");
				}

				int num_of_fields = i;

				for(int i = 0; i < num_of_fields; i++){
					char  temp[200];
					memset(temp, 0, 200);

					sprintf(temp, "%s.%s", (yyvsp[-1].tree)->data.str, variable[i]);

					variable[i+num_of_fields] = strdup(temp);

				}

				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;
				field = strtok(read, ",");
				i = 0;
				while(field != NULL){
					char* temp = strdup(field);
					if(strcmp(temp, "int") == 0){
						type[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type[i] = 1;
					}
					i++;
					field = strtok(NULL, ",");
				}
				for(int i = 0; i < num_of_fields; i++){

					type[num_of_fields+i] = type[i];
				}





				reverseattrlist((yyvsp[-4].list));   // to bring the list in proper format
				struct attr * start = (yyvsp[-4].list)->first;


				int flag;

				while(start != NULL){   // checks if all the attributes in the list are in correct
					flag = 0;
					for(int i = 0; i < 2 * num_of_fields; i++){
						if(strcmp(variable[i], start->str) == 0){
							flag = 1;

						}

					}

					if (flag == 0){
						break;
					}

					start = start->next;
				}


				if (flag == 0){

					printf("Something wrong in the attribute list \n");


				}

				else{
					start = (yyvsp[-4].list)->first;

					while(start != NULL){
						printf("%s ", start->str);
						start = start->next;

					}
					printf("\n\n");


					memset(read, 0, 2000);

					int num_of_results = 0;

					// read the data lines in csv
					while(fgets (read, 2000, file)){
						read[strcspn(read, "\n")] = 0;

						field = strtok(read, ",");

						int i = 0;
						while(field !=  NULL){
							if (type[i] == 0){
								value[i] = strdup(field);
								value[i+num_of_fields] = value[i];

							}

							else {
								char * temp = strdup(field);
								temp[strlen(temp)-1] = '\0';
								value[i] = strdup(temp+1);
								value[i+num_of_fields] = value[i];

							}
							i++;
							field = strtok(NULL, ",");
						}

						start = (yyvsp[-4].list)->first;

						while(start != NULL){

							for(int i = 0; i < 2 * num_of_fields ; i++){
								if(strcmp(start->str, variable[i]) == 0){
									printf("%s ", value[i]);
									break;
								}
							}
							start = start->next;

						}
						printf("\n");
						memset(read, 0, 2000);

						num_of_results++;



					}

					printf("\nTotal number of results: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}
				
				fclose(file);




			}


// print only the columns with the the names in the attribute list


		}
#line 1694 "main.tab.c"
    break;

  case 10:
#line 410 "main.y"
    {
			printf("Syntax is valid \n\n");
			char filename1[100], filename2[100];
			memset(filename1, 0, 100);
			memset(filename2, 0, 100);
			sprintf(filename1, "tables/%s.csv", (yyvsp[-5].tree)->data.str);
			sprintf(filename2, "tables/%s.csv", (yyvsp[-1].tree)->data.str);
			if (!if_file_exist(filename1)){
				printf("%s : No such file exists.\n", filename1);
			}
			else if (!if_file_exist(filename2)){
				printf("%s : No such file exists.\n", filename2);
			}
			else
			{

				FILE* file1 = fopen(filename1, "r");
				FILE* file2 = fopen(filename2, "r");

				char read1[2000];
				char read2[2000];
				memset(read1, 0, 2000);
				memset(read2, 0, 2000);
				fgets(read1, 2000, file1);
				fgets(read2, 2000, file2);
				read1[strcspn(read1, "\n")] = 0;
				read2[strcspn(read2, "\n")] = 0;


				// printing all the fields of both the files
				char *field1 = strtok(read1, ",");

				while(field1 != NULL)
				{
					// printf("%s	", field1);
					printf("%s.%s,",(yyvsp[-5].tree)->data.str, field1);
					field1 = strtok(NULL, ",");
				}

				char *field2 = strtok(read2, ",");
				while(field2!=NULL)
				{
					printf("%s.%s,", (yyvsp[-1].tree)->data.str, field2);
					field2 = strtok(NULL, ",");
				}
				printf("\n\n");

				// Now print the catesian product
				// Take a row of 1st file then
				char * line1 = NULL, *line2=NULL;
    			size_t len1 = 0, len2=0;
    			ssize_t read_file1, read_file2;
				int count1=0, count2=0;
				int total_records=0;
				while ((read_file1 = getline(&line1, &len1, file1)) != -1)
				{
					if(count1==0)
					{

					}
					else
					{
						// restarting the file2
						count2=0;
						line2=NULL;
						len2=0;
						read_file2=0;
						fseek(file2, 0, SEEK_SET);
						while((read_file2 = getline(&line2, &len2, file2)) != -1)
						{
							if(count2==0 || count2==1){count2++;}
							else
							{
								// printf("%c",line1[strlen(line1)-1]);
								line1[strlen(line1)-1]='\0';
								printf("%s", line1);printf(",");printf("%s", line2);
								total_records++;
							}

						}
						printf("\n");


					}
					count1++;

				}
				printf("\nTotal records: %d\n", total_records);
				printf("\n--------------------------------------\n\n");
			}

		}
#line 1791 "main.tab.c"
    break;

  case 11:
#line 504 "main.y"
    {

			printf("Syntax is valid \n");

			//Check if tables exist
			char filename1[100],filename2[100];
			memset(filename1,0,100);
			memset(filename2,0,100);
			sprintf(filename1,"tables/%s.csv",(yyvsp[-8].tree)->data.str);
			sprintf(filename2,"tables/%s.csv",(yyvsp[-1].tree)->data.str);
			if(!if_file_exist(filename1)){
				printf("%s : No such file exists.\n", filename1);
			}else if(!if_file_exist(filename2)){
				printf("%s : No such file exists.\n", filename1);
			} else{
				FILE* file1 = fopen(filename1, "r");
				FILE* file2 = fopen(filename2, "r");

				char* variable1[100];
				char* variable2[100];
				int type1[100];
				int type2[100];
				char* value1[100];
				char* value2[100];

				char read1[2000];
				memset(read1,0,2000);
				char read2[1000];
				memset(read2,0,1000);

				fgets(read1,2000,file1);
				fgets(read2,2000,file2);
				read1[strcspn(read1,"\n")]=0;
				read2[strcspn(read2,"\n")]=0;

				char * field1 = strtok(read1, ",");
				int i = 0;

				// store the tablename.attribute name in variable1[100]
				while(field1 != NULL){
					char  temp[200];
					memset(temp, 0, 200);
					sprintf(temp, "%s.%s", (yyvsp[-8].tree)->data.str, strdup(field1));
					// printf("%s\n", variable1[i]);
					variable1[i]=strdup(temp);
					i++;
					field1 = strtok(NULL, ",");
				}

				int num_of_fields1 = i;

				memset(read1, 0, 2000);
				fgets(read1, 2000, file1);   // reads the attribute type from the file
				read1[strcspn(read1, "\n")] = 0;

				field1 = strtok(read1, ",");
				i = 0;
				while(field1 != NULL){       // store the tablename.attribute type
					char* temp = strdup(field1);
					if(strcmp(temp, "int") == 0){
						type1[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type1[i] = 1;
					}
					i++;
					field1 = strtok(NULL, ",");
				}

				//Do the same work as above for table2
				char * field2 = strtok(read2, ",");
				int k = 0;

				// store the names in variable2[100] in the form of tablename.attr
				while(field2 != NULL){
					char  temp[200];
					memset(temp, 0, 200);
					sprintf(temp, "%s.%s", (yyvsp[-1].tree)->data.str, strdup(field2));
					variable2[k]=strdup(temp);
					// printf("%s\n", variable[i]);
					k++;
					field2 = strtok(NULL, ",");
				}

				int num_of_fields2 = k;

				memset(read2, 0, 2000);
				fgets(read2, 2000, file2);   // reads the attribute type from the file
				read2[strcspn(read2, "\n")] = 0;

				field2 = strtok(read2, ",");
				k = 0;
				while(field2 != NULL){       // store the tablename.attribute type
					char* temp = strdup(field2);
						if(strcmp(temp, "int") == 0){
						type2[k] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type2[k] = 1;
					}
					k++;
					field2 = strtok(NULL, ",");
				}
				printf("\n");
				int error=1; //flag to store if an error has occurred
				//print all the fields
				for(int i=0;i<num_of_fields1;i++){
					printf("%s ",variable1[i]);
				}
				for(int i=0;i<num_of_fields2;i++){
					printf("%s ",variable2[i]);
				}
				printf("\n");
				int num_of_results = 0;
				while(fgets (read1, 2000, file1)){    // start reading the data rows
					read1[strcspn(read1, "\n")] = 0;
					field1 = strtok(read1, ",");
					int i = 0;
					while(field1 !=  NULL){    // stores the attribute value in value array
						if (type1[i] == 0){  // number type
							value1[i] = strdup(field1);
						}
						else {    // string type
							char * temp = strdup(field1);
							temp[strlen(temp)-1] = '\0';
							value1[i] = strdup(temp+1);
						}
						i++;
						field1 = strtok(NULL, ",");
					}
					int count=0;
					// now value has the current data row value for table 1
					fseek(file2,0,SEEK_SET); //to reset file2 to point at beginning of file
					while(fgets(read2,2000,file2)){
						if(count>1)
						{
						read2[strcspn(read2, "\n")] = 0;
						field2 = strtok(read2, ",");
						int i = 0;
						while(field2 !=  NULL){    // stores the attribute value in value array
							if (type2[i] == 0){  // number type
								value2[i] = strdup(field2);
							}
							else {    // string type
								char * temp = strdup(field2);
								temp[strlen(temp)-1] = '\0';
								value2[i] = strdup(temp+1);
							}
							i++;
							field2 = strtok(NULL, ",");
						}

						//now we have got the required values,types etc for both the tables, now check the condition

						int currentrow  = ast_eval2((yyvsp[-4].tree), variable1,variable2, value1,value2, type1,type2, num_of_fields1,num_of_fields2, &error,(yyvsp[-8].tree)->data.str,(yyvsp[-1].tree)->data.str);   // call the ast function
						if (error != 1){    // if error is changed inside ast_eval
							break;
						}
						if(currentrow){    // if ast_eval return 1 print the current data row for both the tables
							num_of_results++;
							for(int i = 0; i < num_of_fields1; i++){
								printf("%s ", value1[i]);
							}
							for(int i = 0; i < num_of_fields2; i++){
								printf("%s ", value2[i]);
							}
							printf("\n");
						}
							memset(read2, 0, 2000);
					}
					count++;
				}
					memset(read1,0,2000);
				}

				if (error != 1){  // there is a error
					printf("There is some error in the query error code %d . It means:", error);
					if(error == 0){
						printf("Invalid arguement in evaluate function");
					}
					if(error == 2){
						printf("Variable in condition is not in the table");
					}
					if(error == 3){
						printf("Type mismatch inbetween two quantities");
					}
					if(error ==4){
						printf("Cannot have the table names on the both sides of = condition equal");
					}
				}

				if(error == 1 && num_of_results == 0){
					printf("There were no successful matches \n");
				}

				if (error == 1 && num_of_results > 0){
					printf("\nNumber of matches: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}

			}
		}
#line 1998 "main.tab.c"
    break;

  case 13:
#line 711 "main.y"
    {
			union Ast_data data;
			struct ast_tree* tr = new_ast(10, data, (yyvsp[-4].tree), (yyvsp[-2].tree));
			(yyval.tree) = new_ast(15, data, tr, (yyvsp[0].tree));
		}
#line 2008 "main.tab.c"
    break;

  case 14:
#line 717 "main.y"
    {
			union Ast_data data;
			(yyval.tree) = new_ast(10, data, (yyvsp[-2].tree), (yyvsp[0].tree));
		}
#line 2017 "main.tab.c"
    break;

  case 15:
#line 722 "main.y"
    {
			(yyval.tree) = (yyvsp[-1].tree);
		}
#line 2025 "main.tab.c"
    break;

  case 16:
#line 731 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast(15, data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2034 "main.tab.c"
    break;

  case 17:
#line 736 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast(16, data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2043 "main.tab.c"
    break;

  case 18:
#line 741 "main.y"
    {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2051 "main.tab.c"
    break;

  case 19:
#line 746 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast(17, data, (yyvsp[0].tree), NULL);
	}
#line 2060 "main.tab.c"
    break;

  case 20:
#line 754 "main.y"
    {
		((yyvsp[0].tree))->left = (yyvsp[-1].tree);
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2069 "main.tab.c"
    break;

  case 21:
#line 759 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2078 "main.tab.c"
    break;

  case 22:
#line 764 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2087 "main.tab.c"
    break;

  case 23:
#line 769 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2096 "main.tab.c"
    break;

  case 24:
#line 774 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2105 "main.tab.c"
    break;

  case 25:
#line 779 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2114 "main.tab.c"
    break;

  case 26:
#line 784 "main.y"
    {

		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2123 "main.tab.c"
    break;

  case 27:
#line 792 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, NULL, (yyvsp[0].tree));
	}
#line 2132 "main.tab.c"
    break;

  case 28:
#line 797 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, NULL, (yyvsp[0].tree));
	}
#line 2141 "main.tab.c"
    break;

  case 29:
#line 802 "main.y"
    {
		union Ast_data data;
		(yyval.tree) = new_ast((yyvsp[-1].operator_type), data, NULL, (yyvsp[0].tree));

	}
#line 2151 "main.tab.c"
    break;

  case 30:
#line 811 "main.y"
    {
		(yyval.operator_type) = 6;
	}
#line 2159 "main.tab.c"
    break;

  case 31:
#line 815 "main.y"
    {
		(yyval.operator_type) = 7;
	}
#line 2167 "main.tab.c"
    break;

  case 32:
#line 819 "main.y"
    {
		(yyval.operator_type) = 8;

	}
#line 2176 "main.tab.c"
    break;

  case 33:
#line 825 "main.y"
    {
		(yyval.operator_type) = 9;
	}
#line 2184 "main.tab.c"
    break;

  case 34:
#line 831 "main.y"
    {
		(yyval.operator_type) = 10;
	}
#line 2192 "main.tab.c"
    break;

  case 35:
#line 835 "main.y"
    {
		(yyval.operator_type) = 11;
	}
#line 2200 "main.tab.c"
    break;

  case 36:
#line 844 "main.y"
    {
			(yyvsp[0].list)->last->next = malloc(sizeof(struct attr));
			(yyvsp[0].list)->last->next->str = strdup((yyvsp[-2].tree)->data.str);
			(yyvsp[0].list)->last =   (yyvsp[0].list)->last->next;
			(yyval.list) = (yyvsp[0].list);
		}
#line 2211 "main.tab.c"
    break;

  case 37:
#line 851 "main.y"
    {
			(yyvsp[0].list)->last->next = malloc(sizeof(struct attr));
			(yyvsp[0].list)->last->next->str = strdup((yyvsp[-2].tree)->data.str);
			(yyvsp[0].list)->last =   (yyvsp[0].list)->last->next;
			(yyval.list) = (yyvsp[0].list);
		}
#line 2222 "main.tab.c"
    break;

  case 38:
#line 859 "main.y"
    {
			(yyval.list) = malloc(sizeof(struct attr_list));
			(yyval.list)->first = malloc(sizeof(struct attr));
			(yyval.list)->last = (yyval.list)->first;
			(yyval.list)->first->next = NULL;
			(yyval.list)->first->str = strdup((yyvsp[0].tree)->data.str);

		}
#line 2235 "main.tab.c"
    break;

  case 39:
#line 869 "main.y"
    {
			(yyval.list) = malloc(sizeof(struct attr_list));
			(yyval.list)->first = malloc(sizeof(struct attr));
			(yyval.list)->last = (yyval.list)->first;
			(yyval.list)->first->next = NULL;
			(yyval.list)->first->str = strdup((yyvsp[0].tree)->data.str);

		}
#line 2248 "main.tab.c"
    break;

  case 40:
#line 883 "main.y"
    {
		(yyval.tree) = (yyvsp[0].tree);

	}
#line 2257 "main.tab.c"
    break;

  case 41:
#line 888 "main.y"
    {

		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2266 "main.tab.c"
    break;

  case 42:
#line 895 "main.y"
    {

		union Ast_data data;
		data.str = malloc(400);
		memset(data.str, 0, 400);
		for(int i = 0; i < strlen((yyvsp[-2].tree)->data.str); i++){
			data.str[i] =  (yyvsp[-2].tree)->data.str[i];
		}
		data.str[strlen((yyvsp[-2].tree)->data.str)] = '.';

		for(int i = 0; i < strlen((yyvsp[0].tree)->data.str); i++){
			data.str[i+1+strlen((yyvsp[-2].tree)->data.str)] =  (yyvsp[0].tree)->data.str[i];
		}

		(yyval.tree) = new_ast(2, data, NULL, NULL);

	}
#line 2288 "main.tab.c"
    break;

  case 43:
#line 913 "main.y"
    {
		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2296 "main.tab.c"
    break;

  case 44:
#line 920 "main.y"
    {
		union Ast_data data;
		data.str = strdup((yyvsp[0].str));

		(yyval.tree) = new_ast(2, data, NULL, NULL);


	}
#line 2309 "main.tab.c"
    break;

  case 45:
#line 929 "main.y"
    {
		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2317 "main.tab.c"
    break;

  case 46:
#line 937 "main.y"
    {

	union Ast_data data;
	data.num = (yyvsp[0].num);
	(yyval.tree) = new_ast(0, data, NULL, NULL);

	}
#line 2329 "main.tab.c"
    break;

  case 47:
#line 945 "main.y"
    {
		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2337 "main.tab.c"
    break;

  case 48:
#line 951 "main.y"
    {
		union Ast_data data;
		data.str = strdup((yyvsp[0].str));

		(yyval.tree) = new_ast(1, data, NULL, NULL);


	}
#line 2350 "main.tab.c"
    break;

  case 49:
#line 960 "main.y"
    {

		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2359 "main.tab.c"
    break;


#line 2363 "main.tab.c"

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
                  yystos[*yyssp], yyvsp);
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
#line 967 "main.y"


int main(int argc, char **argv)
{
  yyparse();
}

void yyerror(char *s)
{


}
