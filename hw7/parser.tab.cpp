/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     PCAMERA = 259,
     POS = 260,
     ORIENT = 261,
     NDIST = 262,
     FDIST = 263,
     LEFT = 264,
     RIGHT = 265,
     TOP = 266,
     BOTTOM = 267,
     SEPARATOR = 268,
     TRANSFORM = 269,
     COORD3 = 270,
     POINT = 271,
     IFACESET = 272,
     TRANSLATE = 273,
     SCALEFACTOR = 274,
     SCALE = 275,
     ROTATION = 276,
     COORDINDEX = 277,
     POINTLIGHT = 278,
     LOCATION = 279,
     COLOR = 280,
     MATERIAL = 281,
     AMBIENT = 282,
     DIFFUSE = 283,
     SPECULAR = 284,
     SHININESS = 285,
     NORMAL = 286,
     VECTOR = 287,
     NORMALINDEX = 288,
     COMMA = 289,
     TEXTURE = 290,
     FILENAME = 291,
     WORD = 292,
     TEXTURECOORD = 293,
     TEXTUREINDEX = 294,
     FRAME = 295,
     LBRACE = 296,
     RBRACE = 297,
     LBRACKET = 298,
     RBRACKET = 299
   };
#endif
/* Tokens.  */
#define NUM 258
#define PCAMERA 259
#define POS 260
#define ORIENT 261
#define NDIST 262
#define FDIST 263
#define LEFT 264
#define RIGHT 265
#define TOP 266
#define BOTTOM 267
#define SEPARATOR 268
#define TRANSFORM 269
#define COORD3 270
#define POINT 271
#define IFACESET 272
#define TRANSLATE 273
#define SCALEFACTOR 274
#define SCALE 275
#define ROTATION 276
#define COORDINDEX 277
#define POINTLIGHT 278
#define LOCATION 279
#define COLOR 280
#define MATERIAL 281
#define AMBIENT 282
#define DIFFUSE 283
#define SPECULAR 284
#define SHININESS 285
#define NORMAL 286
#define VECTOR 287
#define NORMALINDEX 288
#define COMMA 289
#define TEXTURE 290
#define FILENAME 291
#define WORD 292
#define TEXTURECOORD 293
#define TEXTUREINDEX 294
#define FRAME 295
#define LBRACE 296
#define RBRACE 297
#define LBRACKET 298
#define RBRACKET 299




/* Copy the first part of user declarations.  */
#line 2 "parser.ypp"

#include <stdint.h>
#include <FlexLexer.h>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "matrix.h"
#include "data.h"

using namespace std;
int yyerror(const char *s);
int yylex();

vector<Keyframe> result;
Block block;
CameraBlock camera;
SeparatorBlock separator;
Keyframe keyframe;

struct Transform transformSet;
struct Coordinate3 coordinates;
struct IndexedFaceSet faceset;
struct IndexedFaceLines faceline;
struct Light light;




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 32 "parser.ypp"
{
    double ival;
    char *str;
    struct Vector3 vect3;
    struct Vector4 vect4;
}
/* Line 193 of yacc.c.  */
#line 220 "parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 233 "parser.tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  175

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      19,    23,    25,    28,    33,    39,    44,    49,    51,    54,
      57,    60,    63,    66,    69,    72,    75,    78,    90,    95,
      97,   100,   105,   113,   118,   123,   131,   137,   145,   147,
     150,   153,   156,   159,   161,   164,   169,   174,   179,   181,
     184,   189,   194,   199,   202,   204,   206,   210,   212,   216,
     218,   222,   226,   228,   232,   234,   238,   241,   243,   247,
     252,   254,   256,   258
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    46,    47,    -1,    48,    -1,    49,
      -1,    52,    -1,    56,    -1,    55,    -1,     3,    -1,    40,
       3,    50,    -1,    51,    -1,    50,    51,    -1,    18,     3,
       3,     3,    -1,    21,     3,     3,     3,     3,    -1,    20,
       3,     3,     3,    -1,     4,    75,    53,    76,    -1,    54,
      -1,    53,    54,    -1,     5,    69,    -1,     6,    74,    -1,
       7,     3,    -1,     8,     3,    -1,     9,     3,    -1,    10,
       3,    -1,    11,     3,    -1,    12,     3,    -1,    23,    75,
      24,     3,     3,     3,    25,     3,     3,     3,    76,    -1,
      13,    75,    57,    76,    -1,    58,    -1,    57,    58,    -1,
      14,    75,    59,    76,    -1,    15,    75,    16,    77,    70,
      78,    76,    -1,    17,    75,    61,    76,    -1,    26,    75,
      63,    76,    -1,    31,    75,    32,    77,    71,    78,    76,
      -1,    35,    75,    36,    37,    76,    -1,    38,    75,    16,
      77,    73,    78,    76,    -1,    60,    -1,    59,    60,    -1,
      18,    69,    -1,    19,    69,    -1,    21,    74,    -1,    62,
      -1,    61,    62,    -1,    22,    77,    66,    78,    -1,    33,
      77,    67,    78,    -1,    39,    77,    68,    78,    -1,    64,
      -1,    63,    64,    -1,    27,     3,     3,     3,    -1,    28,
       3,     3,     3,    -1,    29,     3,     3,     3,    -1,    30,
       3,    -1,     3,    -1,    65,    -1,    66,    34,    65,    -1,
      65,    -1,    67,    34,    65,    -1,    65,    -1,    68,    34,
      65,    -1,     3,     3,     3,    -1,    69,    -1,    70,    34,
      69,    -1,    69,    -1,    71,    34,    69,    -1,     3,     3,
      -1,    72,    -1,    73,    34,    72,    -1,     3,     3,     3,
       3,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,    96,   100,   105,   110,   117,   131,   140,
     146,   168,   170,   174,   181,   189,   198,   202,   204,   208,
     213,   218,   223,   228,   233,   238,   243,   250,   262,   266,
     268,   272,   278,   284,   290,   292,   294,   299,   304,   306,
     310,   320,   330,   343,   345,   349,   355,   357,   361,   363,
     367,   374,   381,   388,   395,   402,   407,   414,   419,   426,
     431,   438,   447,   452,   459,   464,   471,   479,   484,   491,
     501,   505,   509,   513
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "PCAMERA", "POS", "ORIENT",
  "NDIST", "FDIST", "LEFT", "RIGHT", "TOP", "BOTTOM", "SEPARATOR",
  "TRANSFORM", "COORD3", "POINT", "IFACESET", "TRANSLATE", "SCALEFACTOR",
  "SCALE", "ROTATION", "COORDINDEX", "POINTLIGHT", "LOCATION", "COLOR",
  "MATERIAL", "AMBIENT", "DIFFUSE", "SPECULAR", "SHININESS", "NORMAL",
  "VECTOR", "NORMALINDEX", "COMMA", "TEXTURE", "FILENAME", "WORD",
  "TEXTURECOORD", "TEXTUREINDEX", "FRAME", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "$accept", "file", "block", "numberKeyFrames", "keyframe",
  "transformations", "transformation", "camerablock", "cameralines",
  "cameraline", "lightblock", "sepblock", "sepitems", "sepitem",
  "translines", "transline", "ifslines", "ifsline", "materialLines",
  "materialLine", "single", "singles", "singlesNormal", "singlesTexture",
  "triple", "triples", "triplesNormal", "double", "doublesTexture", "quad",
  "open", "close", "sqopen", "sqclose", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    46,    47,    47,    47,    47,    47,    48,
      49,    50,    50,    51,    51,    51,    52,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    56,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    60,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    64,    64,    65,    66,    66,    67,    67,    68,
      68,    69,    70,    70,    71,    71,    72,    73,    73,    74,
      75,    76,    77,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     4,     5,     4,     4,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    11,     4,     1,
       2,     4,     7,     4,     4,     7,     5,     7,     1,     2,
       2,     2,     2,     1,     2,     4,     4,     4,     1,     2,
       4,     4,     4,     2,     1,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     1,     3,     2,     1,     3,     4,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     9,     0,     0,     0,     0,     3,     4,
       5,     6,     8,     7,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,    10,    11,     0,    19,     0,    20,    21,    22,
      23,    24,    25,    26,    71,    18,    16,     0,     0,     0,
       0,     0,     0,     0,    30,    28,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,    43,     0,     0,     0,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    61,     0,    40,
      41,    42,    39,    31,    72,     0,     0,     0,     0,    44,
      33,     0,     0,     0,    53,    49,    34,     0,     0,     0,
       0,    13,    15,     0,    69,    62,     0,    54,    55,     0,
      57,     0,    59,     0,     0,     0,     0,    64,     0,    36,
       0,    67,     0,     0,    14,     0,    73,     0,     0,    45,
       0,    46,     0,    47,    50,    51,    52,     0,     0,    66,
       0,     0,     0,    63,    32,    56,    58,    60,    65,    35,
      68,    37,     0,     0,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    42,    43,    11,    27,    28,
      12,    13,    36,    37,    76,    77,    82,    83,    88,    89,
     128,   129,   131,   133,    45,   126,   138,   141,   142,    47,
      15,    56,   105,   147
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -102
static const yytype_int16 yypact[] =
{
    -102,     8,  -102,  -102,   -37,   -37,   -37,     2,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,   121,    60,    -8,    92,    15,
      32,    38,    39,    47,    54,    68,    77,    17,  -102,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,    41,  -102,    86,    89,
      90,    93,    92,  -102,    94,  -102,   101,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,   102,    37,    66,
     111,    82,    33,   100,  -102,  -102,   106,   115,   131,   132,
    -102,   133,   139,    15,    15,    32,    -4,  -102,    81,    81,
      81,    81,    48,  -102,   140,   141,   142,   143,    73,  -102,
      81,   110,    81,   145,   146,   147,   148,  -102,   149,  -102,
    -102,  -102,  -102,  -102,  -102,    15,   150,   150,   150,  -102,
    -102,   151,   152,   153,  -102,  -102,  -102,    15,   116,   154,
     134,  -102,  -102,   157,  -102,  -102,   -31,  -102,  -102,   -25,
    -102,   -24,  -102,    10,   158,   159,   160,  -102,    34,  -102,
     161,  -102,    50,   162,  -102,    15,  -102,   116,   150,  -102,
     150,  -102,   150,  -102,  -102,  -102,  -102,    15,   116,  -102,
     154,   116,   163,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,   164,   116,  -102
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -102,  -102,  -102,  -102,  -102,  -102,   126,  -102,  -102,   144,
    -102,  -102,  -102,   136,  -102,    97,  -102,    87,  -102,    88,
    -101,  -102,  -102,  -102,   -72,  -102,  -102,    14,  -102,    95,
      31,   -36,    27,   -99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      65,    99,   100,   145,    14,    18,   130,   132,     2,   148,
     150,     3,     4,   146,    73,    74,    38,    75,    44,   146,
     146,     5,    19,    20,    21,    22,    23,    24,    25,    26,
     149,     6,   151,   125,   153,    46,    16,    17,    54,   158,
     103,    48,    49,   161,   152,   137,   110,   165,     7,   166,
      50,   167,   116,    78,   146,    29,    30,    51,    31,    54,
      57,    58,    59,    60,    61,    62,    63,    32,   157,    91,
      79,    52,    33,   163,    29,    30,    34,    31,   146,    35,
      53,    80,   139,    54,   160,   168,    32,    81,    79,    66,
      54,    33,    67,    68,   146,    34,    69,    71,    35,    80,
      84,    85,    86,    87,    72,    81,   106,   107,   108,    93,
      39,   164,    40,    41,    90,    54,    92,   117,    94,   119,
      73,    74,   169,    75,   104,   171,    19,    20,    21,    22,
      23,    24,    25,    26,    95,    96,    97,   174,    84,    85,
      86,    87,    98,   111,   112,   113,   114,   118,   120,   121,
     122,   123,   124,   127,   134,   135,   136,   140,    54,   143,
     144,   154,   155,   156,   159,   162,   172,   173,    70,   109,
     101,    55,    64,   102,   170,     0,   115
};

static const yytype_int16 yycheck[] =
{
      36,    73,    74,    34,    41,     3,   107,   108,     0,    34,
      34,     3,     4,    44,    18,    19,    24,    21,     3,    44,
      44,    13,     5,     6,     7,     8,     9,    10,    11,    12,
     129,    23,   131,   105,   133,     3,     5,     6,    42,   138,
      76,     3,     3,   142,    34,   117,    82,   148,    40,   150,
       3,   152,    88,    16,    44,    14,    15,     3,    17,    42,
      29,    30,    31,    32,    33,    34,    35,    26,    34,    36,
      22,     3,    31,   145,    14,    15,    35,    17,    44,    38,
       3,    33,   118,    42,    34,   157,    26,    39,    22,     3,
      42,    31,     3,     3,    44,    35,     3,     3,    38,    33,
      27,    28,    29,    30,     3,    39,    79,    80,    81,     3,
      18,   147,    20,    21,    32,    42,    16,    90,     3,    92,
      18,    19,   158,    21,    43,   161,     5,     6,     7,     8,
       9,    10,    11,    12,     3,     3,     3,   173,    27,    28,
      29,    30,     3,     3,     3,     3,     3,    37,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,    42,    25,
       3,     3,     3,     3,     3,     3,     3,     3,    42,    82,
      75,    27,    36,    76,   160,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,     0,     3,     4,    13,    23,    40,    47,    48,
      49,    52,    55,    56,    41,    75,    75,    75,     3,     5,
       6,     7,     8,     9,    10,    11,    12,    53,    54,    14,
      15,    17,    26,    31,    35,    38,    57,    58,    24,    18,
      20,    21,    50,    51,     3,    69,     3,    74,     3,     3,
       3,     3,     3,     3,    42,    54,    76,    75,    75,    75,
      75,    75,    75,    75,    58,    76,     3,     3,     3,     3,
      51,     3,     3,    18,    19,    21,    59,    60,    16,    22,
      33,    39,    61,    62,    27,    28,    29,    30,    63,    64,
      32,    36,    16,     3,     3,     3,     3,     3,     3,    69,
      69,    74,    60,    76,    43,    77,    77,    77,    77,    62,
      76,     3,     3,     3,     3,    64,    76,    77,    37,    77,
       3,     3,     3,     3,     3,    69,    70,     3,    65,    66,
      65,    67,    65,    68,     3,     3,     3,    69,    71,    76,
       3,    72,    73,    25,     3,    34,    44,    78,    34,    78,
      34,    78,    34,    78,     3,     3,     3,    34,    78,     3,
      34,    78,     3,    69,    76,    65,    65,    65,    69,    76,
      72,    76,     3,     3,    76
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
	    /* Fall through.  */
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

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
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
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 101 "parser.ypp"
    {

      ;}
    break;

  case 5:
#line 106 "parser.ypp"
    {

      ;}
    break;

  case 6:
#line 111 "parser.ypp"
    {
        block.blockType = 0;
        block.camera = camera;
        //result.push_back(block);
      ;}
    break;

  case 7:
#line 118 "parser.ypp"
    {
        block.blockType = 1;
        block.separator = separator;
        //result.push_back(block);
        separator.transforms.clear();
        separator.points.clear();
        separator.indices.clear();
        separator.normals.clear();
        separator.normalIndices.clear();
        separator.textureCoords.clear();
        separator.textureIndices.clear();
      ;}
    break;

  case 8:
#line 132 "parser.ypp"
    {
        block.blockType = 2;
        block.light = light;
        //result.push_back(block);
      ;}
    break;

  case 9:
#line 141 "parser.ypp"
    {
        keyframe.numberKeyframes = (yyvsp[(1) - (1)].ival);
      ;}
    break;

  case 10:
#line 147 "parser.ypp"
    {
        keyframe.frameNumber = (yyvsp[(2) - (3)].ival);
        result.push_back(keyframe);

        keyframe.translation.x = 0; // reset to default values for T, R, S
        keyframe.translation.y = 0;
        keyframe.translation.z = 0;

        keyframe.rotation.x = 0;
        keyframe.rotation.y = 0;
        keyframe.rotation.z = 0;
        keyframe.rotation.w = 0;

        keyframe.scaleFactor.x = 1;
        keyframe.scaleFactor.y = 1;
        keyframe.scaleFactor.z = 1;

      ;}
    break;

  case 13:
#line 175 "parser.ypp"
    {
        keyframe.translation.x = (yyvsp[(2) - (4)].ival);
        keyframe.translation.y = (yyvsp[(3) - (4)].ival);
        keyframe.translation.z = (yyvsp[(4) - (4)].ival);
      ;}
    break;

  case 14:
#line 182 "parser.ypp"
    {
        keyframe.rotation.x = (yyvsp[(2) - (5)].ival);
        keyframe.rotation.y = (yyvsp[(3) - (5)].ival);
        keyframe.rotation.z = (yyvsp[(4) - (5)].ival);
        keyframe.rotation.w = (yyvsp[(5) - (5)].ival);
      ;}
    break;

  case 15:
#line 190 "parser.ypp"
    {
        keyframe.scaleFactor.x = (yyvsp[(2) - (4)].ival);
        keyframe.scaleFactor.y = (yyvsp[(3) - (4)].ival);
        keyframe.scaleFactor.z = (yyvsp[(4) - (4)].ival);
      ;}
    break;

  case 19:
#line 209 "parser.ypp"
    {
        camera.position = (yyvsp[(2) - (2)].vect3);
      ;}
    break;

  case 20:
#line 214 "parser.ypp"
    {
        camera.orientation = (yyvsp[(2) - (2)].vect4);
      ;}
    break;

  case 21:
#line 219 "parser.ypp"
    {
        camera.nearDistance = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 22:
#line 224 "parser.ypp"
    {
        camera.farDistance = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 23:
#line 229 "parser.ypp"
    {
        camera.left = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 24:
#line 234 "parser.ypp"
    {
        camera.right = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 25:
#line 239 "parser.ypp"
    {
        camera.top = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 26:
#line 244 "parser.ypp"
    {
        camera.bottom = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 27:
#line 251 "parser.ypp"
    {
        light.location.x = (yyvsp[(4) - (11)].ival);
        light.location.y = (yyvsp[(5) - (11)].ival);
        light.location.z = (yyvsp[(6) - (11)].ival);
        light.color.x = (yyvsp[(8) - (11)].ival);
        light.color.y = (yyvsp[(9) - (11)].ival);
        light.color.z = (yyvsp[(10) - (11)].ival);
      ;}
    break;

  case 31:
#line 273 "parser.ypp"
    {
        separator.transforms.push_back(transformSet);
        transformSet.transformations.clear();
      ;}
    break;

  case 32:
#line 279 "parser.ypp"
    {
        separator.points.push_back(coordinates);
        coordinates.points.clear();
      ;}
    break;

  case 33:
#line 285 "parser.ypp"
    {
        separator.indices.push_back(faceset);
        faceset.lines.clear();
      ;}
    break;

  case 36:
#line 295 "parser.ypp"
    {
        separator.fileName = (yyvsp[(4) - (5)].str);
      ;}
    break;

  case 40:
#line 311 "parser.ypp"
    {
        struct TransformCommand cmd;
        cmd.transformation = "T";
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).x);
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).y);
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).z);
        transformSet.transformations.push_back(cmd);
      ;}
    break;

  case 41:
#line 321 "parser.ypp"
    {
        struct TransformCommand cmd;
        cmd.transformation = "S";
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).x);
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).y);
        cmd.data.push_back((yyvsp[(2) - (2)].vect3).z);
        transformSet.transformations.push_back(cmd);
      ;}
    break;

  case 42:
#line 331 "parser.ypp"
    {
        struct TransformCommand cmd;
        cmd.transformation = "R";
        cmd.data.push_back((yyvsp[(2) - (2)].vect4).x);
        cmd.data.push_back((yyvsp[(2) - (2)].vect4).y);
        cmd.data.push_back((yyvsp[(2) - (2)].vect4).z);
        cmd.data.push_back((yyvsp[(2) - (2)].vect4).w);
        transformSet.transformations.push_back(cmd);
      ;}
    break;

  case 45:
#line 350 "parser.ypp"
    {
        faceset.lines.push_back(faceline);
        faceline.indices.clear();
      ;}
    break;

  case 50:
#line 368 "parser.ypp"
    {
        separator.material.ambient.x = (yyvsp[(2) - (4)].ival);
        separator.material.ambient.y = (yyvsp[(3) - (4)].ival);
        separator.material.ambient.z = (yyvsp[(4) - (4)].ival);
      ;}
    break;

  case 51:
#line 375 "parser.ypp"
    {
        separator.material.diffuse.x = (yyvsp[(2) - (4)].ival);
        separator.material.diffuse.y = (yyvsp[(3) - (4)].ival);
        separator.material.diffuse.z = (yyvsp[(4) - (4)].ival);
      ;}
    break;

  case 52:
#line 382 "parser.ypp"
    {
        separator.material.specular.x = (yyvsp[(2) - (4)].ival);
        separator.material.specular.y = (yyvsp[(3) - (4)].ival);
        separator.material.specular.z = (yyvsp[(4) - (4)].ival);
      ;}
    break;

  case 53:
#line 389 "parser.ypp"
    {
        separator.material.shininess= (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 54:
#line 396 "parser.ypp"
    {
      (yyval.ival) = (yyvsp[(1) - (1)].ival);
      ;}
    break;

  case 55:
#line 403 "parser.ypp"
    {
        faceline.indices.push_back((yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 56:
#line 408 "parser.ypp"
    {
        faceline.indices.push_back((yyvsp[(3) - (3)].ival));
      ;}
    break;

  case 57:
#line 415 "parser.ypp"
    {
        separator.normalIndices.push_back((yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 58:
#line 420 "parser.ypp"
    {
        separator.normalIndices.push_back((yyvsp[(3) - (3)].ival));
      ;}
    break;

  case 59:
#line 427 "parser.ypp"
    {
        separator.textureIndices.push_back((yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 60:
#line 432 "parser.ypp"
    {
        separator.textureIndices.push_back((yyvsp[(3) - (3)].ival));
      ;}
    break;

  case 61:
#line 439 "parser.ypp"
    {
        (yyval.vect3).x = (yyvsp[(1) - (3)].ival);
        (yyval.vect3).y = (yyvsp[(2) - (3)].ival);
        (yyval.vect3).z = (yyvsp[(3) - (3)].ival);
      ;}
    break;

  case 62:
#line 448 "parser.ypp"
    {
        coordinates.points.push_back((yyvsp[(1) - (1)].vect3));
      ;}
    break;

  case 63:
#line 453 "parser.ypp"
    {
        coordinates.points.push_back((yyvsp[(3) - (3)].vect3));
      ;}
    break;

  case 64:
#line 460 "parser.ypp"
    {
        separator.normals.push_back((yyvsp[(1) - (1)].vect3));
      ;}
    break;

  case 65:
#line 465 "parser.ypp"
    {
        separator.normals.push_back((yyvsp[(3) - (3)].vect3));
      ;}
    break;

  case 66:
#line 472 "parser.ypp"
    {
        (yyval.vect3).x = (yyvsp[(1) - (2)].ival);
        (yyval.vect3).y = (yyvsp[(2) - (2)].ival);
      ;}
    break;

  case 67:
#line 480 "parser.ypp"
    {
        separator.textureCoords.push_back((yyvsp[(1) - (1)].vect3));
      ;}
    break;

  case 68:
#line 485 "parser.ypp"
    {
        separator.textureCoords.push_back((yyvsp[(3) - (3)].vect3));
      ;}
    break;

  case 69:
#line 492 "parser.ypp"
    {
      (yyval.vect4).x = (yyvsp[(1) - (4)].ival);
      (yyval.vect4).y = (yyvsp[(2) - (4)].ival);
      (yyval.vect4).z = (yyvsp[(3) - (4)].ival);
      (yyval.vect4).w = (yyvsp[(4) - (4)].ival);
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1977 "parser.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 517 "parser.ypp"


static FlexLexer *lexer;

int yyerror(const char * s)
{
   cerr << "Parse error: " << s << endl;
   return 0;
}

int yylex()
{
   return lexer->yylex();
}

vector<Keyframe> &parse_test(istream &datafile)
{

   // Construct the lexer.
   lexer = new yyFlexLexer(&datafile);
   // Run the parser.
   if(yyparse())
   {
       cerr << "Parse failed!" << endl;
       exit(1);
   }

   delete lexer;
   return result;
}

