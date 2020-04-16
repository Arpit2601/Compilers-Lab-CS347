%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ast.h"
#include "files.h"

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


		// check if the table exist

			char filename[100];
			memset(filename, 0, 100);
			
			sprintf(filename, "tables/%s.csv", $6->data.str);
			
			if (!if_file_exist(filename)){
				printf("No file name of the specified type \n");
				

			}
			else{

		// create a table of variables and their corresponding values  for each row of the tables 
		
				char* variable[100];
				char* value[100]; 
				int type[100];


				FILE * file = fopen(filename, "r");
				
				char read[2000];
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;				
				
				char * field = strtok(read, ",");
				int i = 0;
				while(field != NULL){
					variable[i] = strdup(field);
					i++;
					field = strtok(NULL, ",");				
				}
				
				int num_of_fields = i;
				
				for(int i = 0; i < num_of_fields; i++){
					char  temp[200];
					memset(temp, 0, 200);
					
					sprintf(temp, "%s.%s", $6->data.str, variable[i]);
					
					variable[i+num_of_fields] = strdup(temp);

				}

				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;

				field = strtok(read, ",");
				i = 0;				
				while(field != NULL){
					char* temp = strdup(field);
	
					if(strcmp(temp, "int") == 0){
						type[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type[i] = 1;
					}
					i++;
					field = strtok(NULL, ",");
				}
				for(int i = 0; i < num_of_fields; i++){

					type[num_of_fields+i] = type[i];
				}

// now take a walk through the ast and check if the ast evaluates to true. If yes than print the line else leave the line 				
				int error = 1;

				for(int i = 0; i < num_of_fields; i++){
					printf("%s ", variable[i]);

				}
				
				printf("\n");

				memset(read, 0, 2000);	

				int num_of_results = 0;
				while(fgets (read, 2000, file)){
					read[strcspn(read, "\n")] = 0;					
					field = strtok(read, ",");
					
					int i = 0;					
					while(field !=  NULL){
						if (type[i] == 0){
							value[i] = strdup(field);
							value[i+num_of_fields] = value[i];

						}

						else {
							char * temp = strdup(field);
							temp[strlen(temp)-1] = '\0';
							value[i] = strdup(temp+1);
							value[i+num_of_fields] = value[i];

						}
						i++;
						field = strtok(NULL, ",");
					}

					// now value has the current value for each of the field 

					int currentrow  = ast_eval($3, variable, value, type, num_of_fields, &error);

					if (error != 1){
						break;
					}
					
					if(currentrow){

						num_of_results++;
						for(int i = 0; i < num_of_fields; i++){
							printf("%s ", value[i]);

						}
						
						printf("\n");
					}
					memset(read, 0, 2000);	

				}

				if (error != 1){
					printf("There is some error in the query error code %d . It means:", error);
					if(error == 0){
						printf("Invalid arguement in evaluate function");
					}
					if(error == 2){
						printf("Variable in condition is not in the table");
					}
					if(error == 3){
						printf("Type mismatch inbetween two quantities");
					}				
				}

				if(error == 1 && num_of_results == 0){
					printf("There were no successful matches \n");
				}
				
				if (error == 1 && num_of_results > 0){
					printf("Number of matches: %d \n", num_of_results);
				}

		
			}			
			
			
		}
				
		|PROJECT L attr_list G LB BRACK_NAME RB 

		{
		
			printf("Syntax is valid \n");

//			printattrlist($3);


			char filename[100];
			memset(filename, 0, 100);
			
			sprintf(filename, "tables/%s.csv", $6->data.str);
			
			if (!if_file_exist(filename)){
				printf("No file name of the specified type \n");
				

			}
			else{


// first fill variable with variable names, value with the variable values and type with the variable type
				char* variable[100];
				char* value[100]; 
				int type[100];


				FILE * file = fopen(filename, "r");
				
				char read[2000];
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;				
				
				char * field = strtok(read, ",");
				int i = 0;
				while(field != NULL){
					variable[i] = strdup(field);
					i++;
					field = strtok(NULL, ",");				
				}
				
				int num_of_fields = i;
				
				for(int i = 0; i < num_of_fields; i++){
					char  temp[200];
					memset(temp, 0, 200);
					
					sprintf(temp, "%s.%s", $6->data.str, variable[i]);
					
					variable[i+num_of_fields] = strdup(temp);

				}
	
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;
				field = strtok(read, ",");
				i = 0;				
				while(field != NULL){
					char* temp = strdup(field);
					if(strcmp(temp, "int") == 0){
						type[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type[i] = 1;
					}
					i++;
					field = strtok(NULL, ",");
				}
				for(int i = 0; i < num_of_fields; i++){

					type[num_of_fields+i] = type[i];
				}



				// check all the fields in the attr_list
				// reverse the ll first 
				
				
				reverseattrlist($3);
				struct attr * start = $3->first;
				
				
				int flag;
				while(start != NULL){
					flag = 0;	
					for(int i = 0; i < 2 * num_of_fields; i++){
						if(strcmp(variable[i], start->str) == 0){
							flag = 1;

						}

					}
					
					if (flag == 0){
						break;
					}

					start = start->next;
				}


				if (flag == 0){

					printf("Something wrong in the attribute list \n");
					

				}

				else{
					start = $3->first;

					while(start != NULL){
						printf("%s ", start->str);
						start = start->next;

					}
					printf("\n");

					
					memset(read, 0, 2000);	

					int num_of_results = 0;														


					while(fgets (read, 2000, file)){
						read[strcspn(read, "\n")] = 0;
						
						field = strtok(read, ",");
						
						int i = 0;					
						while(field !=  NULL){
							if (type[i] == 0){
								value[i] = strdup(field);
								value[i+num_of_fields] = value[i];

							}

							else {
								char * temp = strdup(field);
								temp[strlen(temp)-1] = '\0';
								value[i] = strdup(temp+1);
								value[i+num_of_fields] = value[i];

							}
							i++;
							field = strtok(NULL, ",");
						}

						start = $3->first;

						while(start != NULL){
								
							for(int i = 0; i < 2 * num_of_fields ; i++){
								if(strcmp(start->str, variable[i]) == 0){
									printf("%s ", value[i]);
									break;		
								}
							}
							start = start->next;

						}
						printf("\n");
						memset(read, 0, 2000);

						num_of_results++;

																
				
					}

					printf("Total number of results: %d \n", num_of_results);
				}	




			}


// print only the columns with the the names in the attribute list 


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



condition: 
	expr AND condition
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
	};



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
