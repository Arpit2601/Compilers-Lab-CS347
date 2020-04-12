%{
#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern int yylex();
void yyerror(char* s);
extern int yylineno;
%}

%union {

	struct ast_tree * tree;
	int operator_type;
	int num;
	char* str;
	struct attr_list * list;
}

%token SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN L G LE GE EQ NEQ LB RB AND OR NOT COMMA DOT NAME STRING NUM NEWLINE ER

%%

statement_list: statement NEWLINE statement_list |
		statement|
		ER {printf("INVALID Character here");} statement_list  |
		error NEWLINE {printf("Syntax error at line no  %d\n",yylineno-1);} statement_list;  

statement: SELECT L condition G LB BRACK_NAME RB  {printf("Syntax is valid \n");}| 
	   PROJECT L attr_list G LB BRACK_NAME RB  {printf("Syntax is valid \n");}|
	   LB BRACK_NAME RB CARTESIAN_PRODUCT LB BRACK_NAME RB  {printf("Syntax is valid \n");} |
	LB BRACK_NAME RB EQUI_JOIN L condition_equi G LB BRACK_NAME RB  {printf("Syntax is valid \n");} |
		%empty; 
	   


condition_equi: Y EQ Y AND condition_equi2
		| Y EQ Y;
condition_equi2 : Y EQ Y AND condition_equi2
		| Y EQ Y
		| LB condition_equi2 RB
		| %empty;


condition: expr AND condition|
	   expr OR condition|
	   expr|
	   NOT condition;


expr:   X at

	|BRACK_NUM op X
	|BRACK_NUM op2 X
	|BRACK_STRING op2 X
	|X op X
	|X op2 X
	|LB condition RB
	;



at:     op BRACK_NUM
|	op2 BRACK_NUM
|        op2 BRACK_STRING
;


op: L 
| G 
| LE
| GE 
;

op2: EQ 
| NEQ
;




attr_list: BRACK_NAME COMMA attr_list
		   |Y COMMA attr_list
		|BRACK_NAME
		
		|Y
		;




X: 	BRACK_NAME
	|Y
	;

Y: BRACK_NAME DOT BRACK_NAME
	|LB Y RB
;


BRACK_NAME: NAME
	|LB BRACK_NAME RB
	;



BRACK_NUM: NUM 
	|LB BRACK_NUM RB
	;

BRACK_STRING: STRING
	 
	| LB BRACK_STRING RB
	
	;
	  

%%

int main(int argc, char **argv)
{
  yyparse();
}

void yyerror(char *s)
{      


}
