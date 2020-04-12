%{
# include "main.tab.h"
%}

sp              [ \t]*
name_format     [_A-Za-z][_0-9A-Za-z]*
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
{name_format}		            {printf("<%s> ",yytext ); yylval.str=strdup(yytext); return NAME;}
'{name_format}'	        {printf("<%s> ",yytext ); int len = strlen(yytext); yytext[len-1] = '\0'  ; yylval.str=strdup(yytext+1);return STRING;}
\"{name_format}\"	    {printf("<%s> ",yytext ); int len = strlen(yytext); yytext[len-1] = '\0'  ; yylval.str=strdup(yytext+1);return STRING;}
[0-9]+				            {printf("<%s> ",yytext); yylval.num = atoi(yytext); return NUM;}
[ \t]+				            {  }
\n				                {yylineno++; return NEWLINE;}
.				                {return ER;}

%%
