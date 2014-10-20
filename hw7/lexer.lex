/* Comments go here */
%{
#include <iostream>
#include <list>
#include "data.h"
/* Include tokens and variables from the parser (NUM, OPEN, CLOSE, yylval) */
#include "parser.tab.hpp"
using namespace std;
%}
%option noyywrap

DIGIT [0-9]

%%

-?(([0-9]+)|(([0-9]*\.)*[0-9]*)([eE][-+]?[0-9]+)?)     { yylval.ival = atof(yytext); return NUM; }
[ \t\r\n]+   /* Eat whitespace */
#.*       /* Eat comments */
PerspectiveCamera	 return PCAMERA;
position	 		 return POS;
orientation	 		 return ORIENT; 
nearDistance	 	 return NDIST; 
farDistance	 	     return FDIST;
left	 		 	 return LEFT; 
right 		 		 return RIGHT; 
top	 	 			 return TOP; 
bottom 	     		 return BOTTOM; 
Separator	 		 return SEPARATOR; 
Transform	 		 return TRANSFORM; 
Coordinate3	 		 return COORD3; 
point 				 return POINT;
IndexedFaceSet		 return IFACESET;
translation			 return TRANSLATE;
rotation			 return ROTATION;
scaleFactor			 return SCALEFACTOR;
scale  				 return SCALE;
coordIndex 			 return COORDINDEX;
PointLight			 return POINTLIGHT;
location 			 return LOCATION;
color 				 return COLOR;
Material			 return MATERIAL;
ambientColor		 return AMBIENT;
diffuseColor		 return DIFFUSE;
specularColor		 return SPECULAR;
shininess			 return SHININESS;
Normal				 return NORMAL;
vector				 return VECTOR;
normalIndex			 return NORMALINDEX;
Texture2			 return TEXTURE;
filename 			 return FILENAME;
[a-zA-Z][a-zA-Z0-9]*\.[a-zA-Z][a-zA-Z0-9]*  {yylval.str=strdup(yytext); return WORD; }
TextureCoordinate2	 return TEXTURECOORD;
textureCoordIndex 	 return TEXTUREINDEX;
Frame				 return FRAME;
,					 return COMMA;
"{"					 return LBRACE;
"}"					 return RBRACE;
"["					 return LBRACKET;
"]"					 return RBRACKET;
.            { cerr << "Unexpected character: " << yytext << endl;
               yyterminate();
             }
%%

/* Extra code goes here */
