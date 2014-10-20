/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 32 "parser.ypp"
{
    double ival;
    char *str;
    struct Vector3 vect3;
    struct Vector4 vect4;
}
/* Line 1529 of yacc.c.  */
#line 144 "parser.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

