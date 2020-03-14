%{
# include "main.tab.h"
%}

%%

SELECT				{printf("<%s> ",yytext );return SELECT;}
PROJECT				{printf("<%s> ",yytext );return PROJECT;}		 	
CARTESIAN_PRODUCT		{printf("<%s> ",yytext );return CARTESIAN_PRODUCT;}
EQUI_JOIN			{printf("<%s> ",yytext );return EQUI_JOIN;}
"<"				{printf("<%s> ",yytext );return L;}
">"				{printf("<%s> ",yytext );return G;}
"<="				{printf("<%s> ",yytext );return LE;}
">="				{printf("<%s> ",yytext );return GE;}
"="				{printf("<%s> ",yytext );return EQ;}
"!="				{printf("<%s> ",yytext );return NEQ;}
"("				{printf("<%s> ",yytext );return LB;}
")"				{printf("<%s> ",yytext );return RB;}
AND				{printf("<%s> ",yytext );return AND;}
OR				{printf("<%s> ",yytext );return OR;}
NOT				{printf("<%s> ",yytext );return NOT;}
,				{printf("<%s> ",yytext );return COMMA;}
\.				{printf("<%s> ",yytext );return DOT;}
[_A-Za-z][_0-9A-Za-z]*		{printf("<%s> ",yytext );return NAME;}
'[_A-Za-z][_0-9A-Za-z]*'	{printf("<%s> ",yytext );return STRING;}
[0-9]+				{printf("<%s> ",yytext );return NUM;}
[ \t]+				{  }
\n				{yylineno++; return NEWLINE;}
.				{return ER;}

%%
