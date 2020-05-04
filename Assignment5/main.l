%{

	#include <bits/stdc++.h>

	#include "mips.h"
	#include "main.tab.h"

	using namespace std;

	extern bool syntax_analysis;

%}

%x remove_comment_found
%option yylineno
%option noyywrap

NUM_INT 		([-]*[0-9]+)
NUM_FP			([-]*[0-9]+\.[0-9]+)
ID		        ([A-Za-z_]([A-Za-z0-9_])*)
nl 			    [\n]
sp              [ \n\t]*

INT             "int"
FLOAT           "float"
VOID            "void"
LT              "<"
GT              ">"
LTEQ            "<="
GTEQ            ">="
EQ              "=="
NEQ             ("!="|"<>")
AND             "&&"
OR              "||"
NOT             "!"
ASSIGN          "="
PLUS            "+"
MINUS           "-"
DIVIDE          "/"
MULT            "*"
MOD             "%"
SEMI            ";"
COLON           ":"
COMMA           ","
LB              "("
RB              ")"
LCB             "{"
RCB             "}"

HEADER          (\#include[ \n\t]*\<.+\>)|((\#include[ \t\n]*\".+\"))
MAIN            "main"

FOR             "for"
WHILE           "while"
IF              "if"
ELSE            "else"
SWITCH          "switch"
CASE            "case"
RETURN          "return"
GET             "get"
PUT             "put"
BREAK           "break"
CONTINUE        "continue"
DEFAULT         "default"

TRUE 	"true"
FALSE	"false"
BOOL	"bool"


%%


"/*"                                BEGIN(remove_comment_found);
<remove_comment_found>"*/"          BEGIN(INITIAL);
<remove_comment_found>.             ;
<remove_comment_found>\n           ;
"//"[^\n]*                          ;


{SEMI}			{(yylval.node) = new Node("SEMI", yytext, NULL, NULL, NULL); return SEMI;}
{COLON}			{(yylval.node) = new Node("COLON", yytext, NULL, NULL, NULL); return COLON;}
{EQ}			{(yylval.node) = new Node("EQ", yytext, NULL, NULL, NULL); return EQ;}
{PLUS} 			{(yylval.node) = new Node("PLUS", yytext, NULL, NULL, NULL); return PLUS;}
{MINUS} 			{(yylval.node) = new Node("MINUS", yytext, NULL, NULL, NULL); return MINUS;}
{MULT} 			{(yylval.node) = new Node("MULT", yytext, NULL, NULL, NULL); return MULT;}
{DIVIDE} 			{(yylval.node) = new Node("DIVIDE", yytext, NULL, NULL, NULL); return DIVIDE;}
{MOD} 			{(yylval.node) = new Node("MOD", yytext, NULL, NULL, NULL); return MOD;}
{GT} 			{(yylval.node) = new Node("GT", yytext, NULL, NULL, NULL); return GT;}
{LT} 			{(yylval.node) = new Node("LT", yytext, NULL, NULL, NULL); return LT;}
{GTEQ} 			{(yylval.node) = new Node("GTEQ", yytext, NULL, NULL, NULL); return GTEQ;}
{LTEQ} 			{(yylval.node) = new Node("LTEQ", yytext, NULL, NULL, NULL); return LTEQ;}
{ASSIGN} 			{(yylval.node) = new Node("ASSIGN", yytext, NULL, NULL, NULL); return ASSIGN;}
{NEQ} 			{(yylval.node) = new Node("NEQ", yytext, NULL, NULL, NULL); return NEQ;}
{MAIN} 			{(yylval.node) = new Node("MAIN", yytext, NULL, NULL, NULL); return MAIN;}
{INT} 			{(yylval.node) = new Node("INT", yytext, NULL, NULL, NULL); return INT;}
{VOID} 			{(yylval.node) = new Node("VOID", yytext, NULL, NULL, NULL); return VOID;}
{TRUE} 			{(yylval.node) = new Node("TRUE", yytext, NULL, NULL, NULL); yylval.node->setDataType(_bool); return TRUE;}
{FALSE} 		{(yylval.node) = new Node("FALSE", yytext, NULL, NULL, NULL); yylval.node->setDataType(_bool); return FALSE;}
{FLOAT} 		{(yylval.node) = new Node("FLOAT", yytext, NULL, NULL, NULL); return FLOAT;}
{BOOL} 			{(yylval.node) = new Node("BOOL", yytext, NULL, NULL, NULL); return BOOL;}
{GET} 			{(yylval.node) = new Node("GET", yytext, NULL, NULL, NULL); return GET;}
{PUT} 			{(yylval.node) = new Node("PUT", yytext, NULL, NULL, NULL); return PUT;}
{RETURN} 		{(yylval.node) = new Node("RETURN", yytext, NULL, NULL, NULL); return RETURN;}
{OR} 			{(yylval.node) = new Node("OR", yytext, NULL, NULL, NULL); return OR;}
{AND} 			{(yylval.node) = new Node("AND", yytext, NULL, NULL, NULL); return AND;}
{IF} 			{(yylval.node) = new Node("IF", yytext, NULL, NULL, NULL); return IF;}
{SWITCH} 			{(yylval.node) = new Node("SWITCH", yytext, NULL, NULL, NULL); return SWITCH;}
{CASE} 			{(yylval.node) = new Node("CASE", yytext, NULL, NULL, NULL); return CASE;}
{DEFAULT} 			{(yylval.node) = new Node("DEFAULT", yytext, NULL, NULL, NULL); return DEFAULT;}

{FOR} 			{(yylval.node) = new Node("FOR", yytext, NULL, NULL, NULL); return FOR;}
{WHILE} 		{(yylval.node) = new Node("WHILE", yytext, NULL, NULL, NULL); return WHILE;}
{ELSE} 			{(yylval.node) = new Node("ELSE", yytext, NULL, NULL, NULL); return ELSE;}
{BREAK} 		{(yylval.node) = new Node("BREAK", yytext, NULL, NULL, NULL); return BREAK;}
{CONTINUE} 		{(yylval.node) = new Node("CONTINUE", yytext, NULL, NULL, NULL); return CONTINUE;}
{LCB}		{(yylval.node) = new Node("LCB", yytext, NULL, NULL, NULL); return LCB;}
{RCB}		{(yylval.node) = new Node("RCB", yytext, NULL, NULL, NULL); return RCB;}
{LB}		{(yylval.node) = new Node("LB", yytext, NULL, NULL, NULL); return LB;}
{RB}		{(yylval.node) = new Node("RB", yytext, NULL, NULL, NULL); return RB;}
{COMMA}			{(yylval.node) = new Node("COMMA", yytext, NULL, NULL, NULL); return COMMA;}

{NUM_INT}		{(yylval.node) = new Node("NUM_INT", yytext, NULL, NULL, NULL); yylval.node->setDataType(_int); return NUM_INT;}
{HEADER}			{(yylval.node) = new Node("HEADER", yytext, NULL, NULL, NULL); return HEADER;}
{NUM_FP}		{(yylval.node) = new Node("NUM_FP", yytext, NULL, NULL, NULL); yylval.node->setDataType(_float); return NUM_FP;}
{ID}			{(yylval.node) = new Node("ID", yytext, NULL, NULL, NULL); return ID;}

{nl} 			{}
{sp}		{}

.					{cerr<< "TOKEN CANNOT BE MATCHED :\t"<< yytext <<"\t"<<endl; syntax_analysis = false;}

%%
