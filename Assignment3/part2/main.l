%{
# include "main.tab.h"
%}

sp              [ \t]*
name_format     {sp}[_A-Za-z][_0-9A-Za-z]*{sp}
%%

{sp}SELECT{sp}				    {printf("<%s> ",yytext );return SELECT;}
{sp}PROJECT{sp}				    {printf("<%s> ",yytext );return PROJECT;}		 	
{sp}CARTESIAN_PRODUCT{sp}		{printf("<%s> ",yytext );return CARTESIAN_PRODUCT;}
{sp}EQUI_JOIN{sp}			    {printf("<%s> ",yytext );return EQUI_JOIN;}
{sp}"<"{sp}				        {printf("<%s> ",yytext );return L;}
{sp}">"{sp}				        {printf("<%s> ",yytext );return G;}
{sp}"<="{sp}				    {printf("<%s> ",yytext );return LE;}
{sp}">="{sp}				    {printf("<%s> ",yytext );return GE;}
{sp}"="{sp}				        {printf("<%s> ",yytext );return EQ;}
{sp}"!="{sp}				    {printf("<%s> ",yytext );return NEQ;}
{sp}"("{sp}				        {printf("<%s> ",yytext );return LB;}
{sp}")"{sp}				        {printf("<%s> ",yytext );return RB;}
{sp}AND{sp}				        {printf("<%s> ",yytext );return AND;}
{sp}OR{sp}				        {printf("<%s> ",yytext );return OR;}
{sp}NOT{sp}				        {printf("<%s> ",yytext );return NOT;}
,				                {printf("<%s> ",yytext );return COMMA;}
\.				                {printf("<%s> ",yytext );return DOT;}
{name_format}		            {printf("<%s> ",yytext );return NAME;}
{sp}'{name_format}'{sp}	        {printf("<%s> ",yytext );return STRING;}
{sp}\"{name_format}\"{sp}	    {printf("<%s> ",yytext );return STRING;}
[0-9]+				            {printf("<%s> ",yytext );return NUM;}
[ \t]+				            {  }
\n				                {yylineno++; return NEWLINE;}
.				                {return ER;}

%%
