%{
	#include <bits/stdc++.h>
	#include "mips.h"
	#include "main.tab.h"
	using namespace std;
	extern bool syntax_analysis;
	extern bool lexical_analysis;
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

TRUE 			"true"
FALSE			"false"
BOOL			"bool"

%%
"/*"                                BEGIN(remove_comment_found);
<remove_comment_found>"*/"          BEGIN(INITIAL);
<remove_comment_found>.             ;
<remove_comment_found>\n           ;
"//"[^\n]*                          ;


{SEMI}			{(yylval.node) = new AstNode("SEMI", yytext, NULL, NULL, NULL); return SEMI;}
{COLON}			{(yylval.node) = new AstNode("COLON", yytext, NULL, NULL, NULL); return COLON;}
{EQ}			{(yylval.node) = new AstNode("EQ", yytext, NULL, NULL, NULL); return EQ;}
{PLUS} 			{(yylval.node) = new AstNode("PLUS", yytext, NULL, NULL, NULL); return PLUS;}
{MINUS} 		{(yylval.node) = new AstNode("MINUS", yytext, NULL, NULL, NULL); return MINUS;}
{MULT} 			{(yylval.node) = new AstNode("MULT", yytext, NULL, NULL, NULL); return MULT;}
{DIVIDE} 		{(yylval.node) = new AstNode("DIVIDE", yytext, NULL, NULL, NULL); return DIVIDE;}
{MOD} 			{(yylval.node) = new AstNode("MOD", yytext, NULL, NULL, NULL); return MOD;}
{GT} 			{(yylval.node) = new AstNode("GT", yytext, NULL, NULL, NULL); return GT;}
{LT} 			{(yylval.node) = new AstNode("LT", yytext, NULL, NULL, NULL); return LT;}
{GTEQ} 			{(yylval.node) = new AstNode("GTEQ", yytext, NULL, NULL, NULL); return GTEQ;}
{LTEQ} 			{(yylval.node) = new AstNode("LTEQ", yytext, NULL, NULL, NULL); return LTEQ;}
{ASSIGN} 		{(yylval.node) = new AstNode("ASSIGN", yytext, NULL, NULL, NULL); return ASSIGN;}
{NEQ} 			{(yylval.node) = new AstNode("NEQ", yytext, NULL, NULL, NULL); return NEQ;}
{MAIN} 			{(yylval.node) = new AstNode("MAIN", yytext, NULL, NULL, NULL); return MAIN;}
{INT} 			{(yylval.node) = new AstNode("INT", yytext, NULL, NULL, NULL); return INT;}
{VOID} 			{(yylval.node) = new AstNode("VOID", yytext, NULL, NULL, NULL); return VOID;}
{TRUE} 			{(yylval.node) = new AstNode("TRUE", yytext, NULL, NULL, NULL); yylval.node->setDataType(_bool); return TRUE;}
{FALSE} 		{(yylval.node) = new AstNode("FALSE", yytext, NULL, NULL, NULL); yylval.node->setDataType(_bool); return FALSE;}
{FLOAT} 		{(yylval.node) = new AstNode("FLOAT", yytext, NULL, NULL, NULL); return FLOAT;}
{BOOL} 			{(yylval.node) = new AstNode("BOOL", yytext, NULL, NULL, NULL); return BOOL;}
{GET} 			{(yylval.node) = new AstNode("GET", yytext, NULL, NULL, NULL); return GET;}
{PUT} 			{(yylval.node) = new AstNode("PUT", yytext, NULL, NULL, NULL); return PUT;}
{RETURN} 		{(yylval.node) = new AstNode("RETURN", yytext, NULL, NULL, NULL); return RETURN;}
{OR} 			{(yylval.node) = new AstNode("OR", yytext, NULL, NULL, NULL); return OR;}
{AND} 			{(yylval.node) = new AstNode("AND", yytext, NULL, NULL, NULL); return AND;}
{IF} 			{(yylval.node) = new AstNode("IF", yytext, NULL, NULL, NULL); return IF;}
{SWITCH} 		{(yylval.node) = new AstNode("SWITCH", yytext, NULL, NULL, NULL); return SWITCH;}
{CASE} 			{(yylval.node) = new AstNode("CASE", yytext, NULL, NULL, NULL); return CASE;}
{DEFAULT} 		{(yylval.node) = new AstNode("DEFAULT", yytext, NULL, NULL, NULL); return DEFAULT;}

{FOR} 			{(yylval.node) = new AstNode("FOR", yytext, NULL, NULL, NULL); return FOR;}
{WHILE} 		{(yylval.node) = new AstNode("WHILE", yytext, NULL, NULL, NULL); return WHILE;}
{ELSE} 			{(yylval.node) = new AstNode("ELSE", yytext, NULL, NULL, NULL); return ELSE;}
{BREAK} 		{(yylval.node) = new AstNode("BREAK", yytext, NULL, NULL, NULL); return BREAK;}
{CONTINUE} 		{(yylval.node) = new AstNode("CONTINUE", yytext, NULL, NULL, NULL); return CONTINUE;}
{LCB}			{(yylval.node) = new AstNode("LCB", yytext, NULL, NULL, NULL); return LCB;}
{RCB}			{(yylval.node) = new AstNode("RCB", yytext, NULL, NULL, NULL); return RCB;}
{LB}			{(yylval.node) = new AstNode("LB", yytext, NULL, NULL, NULL); return LB;}
{RB}			{(yylval.node) = new AstNode("RB", yytext, NULL, NULL, NULL); return RB;}
{COMMA}			{(yylval.node) = new AstNode("COMMA", yytext, NULL, NULL, NULL); return COMMA;}

{NUM_INT}		{(yylval.node) = new AstNode("NUM_INT", yytext, NULL, NULL, NULL); yylval.node->setDataType(_int); return NUM_INT;}
{HEADER}		{(yylval.node) = new AstNode("HEADER", yytext, NULL, NULL, NULL); return HEADER;}
{NUM_FP}		{(yylval.node) = new AstNode("NUM_FP", yytext, NULL, NULL, NULL); yylval.node->setDataType(_float); return NUM_FP;}
{ID}			{(yylval.node) = new AstNode("ID", yytext, NULL, NULL, NULL); return ID;}

{nl} 			{}
{sp}			{}

.				{cerr<< "TOKEN CANNOT BE MATCHED :\t"<< yytext <<"\t"<<endl; lexical_analysis = false;}

%%
