%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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


%type <tree> condition_equi
%type <tree> condition
%type <tree> expr 
%type <tree> at
%type <operator_type> op2
%type <operator_type> op
%type <list> attr_list
%type <tree> Y
%type <tree> X
%type <tree> BRACK_NAME
%type <tree> BRACK_NUM
%type <tree> BRACK_STRING
%type <str> STRING
%type <str> NAME
%type <num> NUM



%%

statement_list: statement NEWLINE statement_list |
		statement|
		ER {printf("INVALID Character here");} statement_list  |
		error NEWLINE {printf("Syntax error at line no  %d\n",yylineno-1);} statement_list;  

statement: SELECT L condition G LB BRACK_NAME RB 
		{
			printf("Syntax is valid \n");
			printf("peak node %d \n", $3->nodetype);
			printinorder($3);
			
		}
				
		|PROJECT L attr_list G LB BRACK_NAME RB 

		{
		
			printf("Syntax is valid \n");

			printattrlist($3);

		}
		|LB BRACK_NAME RB CARTESIAN_PRODUCT LB BRACK_NAME RB  {printf("Syntax is valid \n");} 
		|LB BRACK_NAME RB EQUI_JOIN L condition_equi G LB BRACK_NAME RB  {printf("Syntax is valid \n");} |
		%empty; 
	   


condition_equi: Y EQ Y AND condition_equi
		{
			union Ast_data data;
			struct ast_tree* tr = new_ast(10, data, $1, $3);
			$$ = new_ast(15, data, tr, $5);	
		} 
		| Y EQ Y
		{
			union Ast_data data;
			$$ = new_ast(10, data, $1, $3);
		}
		| LB condition_equi RB
		{
			$$ = $2;
		}
		; 



condition: expr AND condition
	{
		union Ast_data data;
		$$ = new_ast(15, data, $1, $3);
	}
	|expr OR condition
	{
		union Ast_data data;
		$$ = new_ast(16, data, $1, $3);
	}
	|expr
	{
		$$ = $1;
	}
	|NOT condition
	{
		union Ast_data data;
		$$ = new_ast(17, data, $2, NULL);
	}
	;


expr:   X at
	{
		($2)->left = $1;
		$$ = $2; 
	}
	|BRACK_NUM op X
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);			
	}
	|BRACK_NUM op2 X
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|BRACK_STRING op2 X
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|X op X
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|X op2 X
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|LB condition RB
	{

		$$ = $2;
	}
	;



at:     op BRACK_NUM
	{
		union Ast_data data;
		$$ = new_ast($1, data, NULL, $2);		
	}
|	op2 BRACK_NUM
	{
		union Ast_data data;
		$$ = new_ast($1, data, NULL, $2);
	}
|        op2 BRACK_STRING
	{
		union Ast_data data;
		$$ = new_ast($1, data, NULL, $2);
				
	}
;


op: L 
	{
		$$ = 6;
	}
| G 
	{
		$$ = 7;
	}
| LE
	{
		$$ = 8;
	}
| GE 
	{
		$$ = 9;
	}
;

op2: EQ 
	{
		$$ = 10;
	}
| NEQ
	{
		$$ = 11;
	}
;




attr_list: BRACK_NAME COMMA attr_list
		{		
			$3->last->next = malloc(sizeof(struct attr));
			$3->last->next->str = strdup($1->data.str);
			$3->last =   $3->last->next;
			$$ = $3;
		}
	   	   |Y COMMA attr_list
		{
			$3->last->next = malloc(sizeof(struct attr));
			$3->last->next->str = strdup($1->data.str);
			$3->last =   $3->last->next;
			$$ = $3;
		}

		|BRACK_NAME
		{
			$$ = malloc(sizeof(struct attr_list));
			$$->first = malloc(sizeof(struct attr));
			$$->last = $$->first;
			$$->first->next = NULL;
			$$->first->str = strdup($1->data.str); 	
				
		}

		|Y
		{
			$$ = malloc(sizeof(struct attr_list));
			$$->first = malloc(sizeof(struct attr));
			$$->last = $$->first;
			$$->first->next = NULL;
			$$->first->str = strdup($1->data.str); 	
				
		}
		;




X: 	BRACK_NAME
	{
		$$ = $1;
	
	}
	|Y
	{
	
		$$ = $1;
	}
;

Y: BRACK_NAME DOT BRACK_NAME
	{
	
		union Ast_data data;
		data.str = malloc(400);
		memset(data.str, 0, 400);
		for(int i = 0; i < strlen($1->data.str); i++){
			data.str[i] =  $1->data.str[i]; 		
		}
		data.str[strlen($1->data.str)] = '.';
		
		for(int i = 0; i < strlen($1->data.str); i++){
			data.str[i+1+strlen($1->data.str)] =  $3->data.str[i]; 
		}
		
		$$ = new_ast(2, data, NULL, NULL);

	}
	|LB Y RB
	{
		$$ = $2;	
	}
;


BRACK_NAME: NAME
	{
		union Ast_data data;
		data.str = strdup($1);
		
		$$ = new_ast(2, data, NULL, NULL);		
		

	} 
	|LB BRACK_NAME RB
	{
		$$ = $2;	
	}
	;



BRACK_NUM: NUM 
	{
	
	union Ast_data data;
	data.num = $1;
	$$ = new_ast(0, data, NULL, NULL);
	
	}
	|LB BRACK_NUM RB
	{
		$$ = $2;	
	}
	;

BRACK_STRING: STRING
	{
		union Ast_data data;
		data.str = strdup($1);
		
		$$ = new_ast(1, data, NULL, NULL);		
		

	} 
	| LB BRACK_STRING RB
	{
		
		$$ = $2;
	}
	;
	  

%%

int main(int argc, char **argv)
{
  yyparse();
}

void yyerror(char *s)
{      


}
