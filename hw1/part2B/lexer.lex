/* Comments go here */
%{
#include <iostream>
#include <list>
#include "data.h"
/* Include tokens and variables from the parser (NUM, POLYTOK, yylval) */
#include "parser.tab.hpp"
using namespace std;
%}
%option noyywrap

DIGIT [0-9]

%%

-?(([0-9]+)|([0-9]*\.[0-9]*)([eE][-+]?[0-9]+)?)     { yylval.ival = atof(yytext); return NUM; }
[ \t\r\n]+   /* Eat whitespace */
polyline	 return POLYTOK; 
.            { cerr << "Unexpected character: " << yytext << endl;
               yyterminate();
             }
%%

/* Extra code goes here */
