%{
#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern int yylex();
void yyerror(char* s);
extern int yylineno;
%}

%token SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN L G LE GE EQ NEQ LB RB AND OR NOT COMMA DOT NAME STRING NUM NEWLINE ER

%%

statement_list: statement NEWLINE statement_list |
		statement|
		ER {printf("INVALID Character here");} statement_list  |
		error NEWLINE {printf("Syntax error in line number  %d\n",yylineno-1);} statement_list;  

statement: SELECT L condition G LB table_name RB  {printf("Syntax is valid \n");}| 
	   PROJECT L attr_list G LB table_name RB  {printf("Syntax is valid \n");}|
	   LB table_name RB factor  {printf("Syntax is valid \n");} |
		%empty; 
	   

factor: CARTESIAN_PRODUCT LB table_name RB |
	EQUI_JOIN L condition_equi G LB table_name RB ;


condition_equi: table_name DOT NAME EQ table_name DOT NAME AND condition_equi |
				table_name DOT NAME EQ table_name DOT NAME |
				%empty;

condition: expr cond|
	   NOT condition;

cond: AND condition |
      OR condition |
      %empty;

expr:   X at|
	NUM op X|
	STRING op2 X|
	X op X;
X: 	NAME|
	table_name DOT NAME;

at:     op NUM|
        op2 STRING;    
	  
op: L | G | LE | GE | EQ | NEQ ;

op2: EQ | NEQ;

attr_list: NAME atr|
	   table_name DOT NAME atr;

atr: COMMA attr_list |
     %empty;


table_name: NAME; 

%%

int main(int argc, char **argv)
{
  yyparse();
}

void yyerror(char *s)
{      


}
