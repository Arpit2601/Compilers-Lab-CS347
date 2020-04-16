%{
# include "main.tab.h"
%}

sp              [ \t]*
name_format     [_A-Za-z][_0-9A-Za-z]*
%%

{sp}SELECT{sp}				    {return SELECT;}
{sp}PROJECT{sp}				    {return PROJECT;}		 	
{sp}CARTESIAN_PRODUCT{sp}		{return CARTESIAN_PRODUCT;}
{sp}EQUI_JOIN{sp}			    {return EQUI_JOIN;}
{sp}"<"{sp}				        {return L;}
{sp}">"{sp}				        {return G;}
{sp}"<="{sp}				    {return LE;}
{sp}">="{sp}				    {return GE;}
{sp}"="{sp}				        {return EQ;}
{sp}"!="{sp}				    {return NEQ;}
{sp}"("{sp}				        {return LB;}
{sp}")"{sp}				        {return RB;}
{sp}AND{sp}				        {return AND;}
{sp}OR{sp}				        {return OR;}
{sp}NOT{sp}				        {return NOT;}
,				                {return COMMA;}
\.				                {return DOT;}
{name_format}		            { yylval.str=strdup(yytext); return NAME;}
'{name_format}'	        {int len = strlen(yytext); yytext[len-1] = '\0'  ; yylval.str=strdup(yytext+1);return STRING;}
\"{name_format}\"	    { int len = strlen(yytext); yytext[len-1] = '\0'  ; yylval.str=strdup(yytext+1);return STRING;}
[0-9]+				            {yylval.num = atoi(yytext); return NUM;}
[ \t]+				            {  }
\n				                {yylineno++; return NEWLINE;}
.				                {return ER;}

%%
