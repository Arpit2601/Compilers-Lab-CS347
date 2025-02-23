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
%type <tree> BRACK_EQ
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
		ER {printf("INVALID Character here \n");} statement_list  |
		error NEWLINE {printf("Syntax error \n");} statement_list;

statement: SELECT L condition G LB BRACK_NAME RB
		{
			printf("Syntax is valid \n\n");




			char filename[100];
			memset(filename, 0, 100);

			sprintf(filename, "tables/%s.csv", $6->data.str);  // tables folder will hold all the csv files

			if (!if_file_exist(filename)){  // check if the table exist
				printf("No file name of the specified type \n");


			}
			else{

		// create a table of variables and their corresponding values  for each row of the tables

				char* variable[100];  // will hold the attribute name of the table
				char* value[100];   // will hold the corresponding value of the attributes in string format
				int type[100];      // type of the attribute


				FILE * file = fopen(filename, "r");

				char read[2000];
				memset(read, 0, 2000);
				fgets(read, 2000, file);
				read[strcspn(read, "\n")] = 0;

				char * field = strtok(read, ",");
				int i = 0;

				// store the attribute name in variable[100]
				while(field != NULL){
					variable[i] = strdup(field);
					// printf("%s\n", variable[i]);
					i++;
					field = strtok(NULL, ",");
				}

				int num_of_fields = i;

				for(int i = 0; i < num_of_fields; i++){     // store the  names in the form tablename.attribute
					char  temp[200];
					memset(temp, 0, 200);

					sprintf(temp, "%s.%s", $6->data.str, variable[i]);
					// printf("%s\n", temp);
					variable[i+num_of_fields] = strdup(temp);

				}

				memset(read, 0, 2000);

				fgets(read, 2000, file);   // reads the attribute type from the file
				read[strcspn(read, "\n")] = 0;

				field = strtok(read, ",");
				i = 0;
				while(field != NULL){       // store the attribute type
					char* temp = strdup(field);
					// printf("%s\n", temp);

					if(strcmp(temp, "int") == 0){
						type[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type[i] = 1;
					}
					i++;
					field = strtok(NULL, ",");
				}
				for(int i = 0; i < num_of_fields; i++){   // store the attribute type of attributes of form tablename.attribute

					type[num_of_fields+i] = type[i];
				}

				int error = 1;   // will store the error code if the error occurs

				for(int i = 0; i < num_of_fields; i++){   // print the attribute names
					printf("%s ", variable[i]);

				}

				printf("\n\n");

				memset(read, 0, 2000);

				int num_of_results = 0;
				while(fgets (read, 2000, file)){    // start reading the data rows
					read[strcspn(read, "\n")] = 0;
					field = strtok(read, ",");

					int i = 0;
					while(field !=  NULL){    // stores the attribute value in value array
						if (type[i] == 0){  // number type
							value[i] = strdup(field);
							value[i+num_of_fields] = value[i];

						}

						else {    // string type
							char * temp = strdup(field);
							temp[strlen(temp)-1] = '\0';
							value[i] = strdup(temp+1);
							value[i+num_of_fields] = value[i];

						}
						i++;
						field = strtok(NULL, ",");
					}

					// now value has the current data row value

					int currentrow  = ast_eval($3, variable, value, type, num_of_fields, &error);   // call the ast function

					if (error != 1){    // if error is changed inside ast_eval
						break;
					}

					if(currentrow){    // if ast_eval return 1 pritn the current data row

						num_of_results++;
						for(int i = 0; i < num_of_fields; i++){
							printf("%s ", value[i]);

						}

						printf("\n");
					}
					memset(read, 0, 2000);

				}

				if (error != 1){  // there is a error
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
					printf("\nNumber of matches: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}

				fclose(file);


			}


		}

		|PROJECT L attr_list G LB BRACK_NAME RB

		{

			printf("Syntax is valid \n\n");

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





				reverseattrlist($3);   // to bring the list in proper format
				struct attr * start = $3->first;


				int flag;

				while(start != NULL){   // checks if all the attributes in the list are in correct
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
					printf("\n\n");


					memset(read, 0, 2000);

					int num_of_results = 0;

					// read the data lines in csv
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

					printf("\nTotal number of results: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}
				
				fclose(file);




			}


// print only the columns with the the names in the attribute list


		}
		|LB BRACK_NAME RB CARTESIAN_PRODUCT LB BRACK_NAME RB
		{
			printf("Syntax is valid \n\n");
			char filename1[100], filename2[100];
			memset(filename1, 0, 100);
			memset(filename2, 0, 100);
			sprintf(filename1, "tables/%s.csv", $2->data.str);
			sprintf(filename2, "tables/%s.csv", $6->data.str);
			if (!if_file_exist(filename1)){
				printf("%s : No such file exists.\n", filename1);
			}
			else if (!if_file_exist(filename2)){
				printf("%s : No such file exists.\n", filename2);
			}
			else
			{

				FILE* file1 = fopen(filename1, "r");
				FILE* file2 = fopen(filename2, "r");

				char read1[2000];
				char read2[2000];
				memset(read1, 0, 2000);
				memset(read2, 0, 2000);
				fgets(read1, 2000, file1);
				fgets(read2, 2000, file2);
				read1[strcspn(read1, "\n")] = 0;
				read2[strcspn(read2, "\n")] = 0;


				// printing all the fields of both the files
				char *field1 = strtok(read1, ",");

				while(field1 != NULL)
				{
					// printf("%s	", field1);
					printf("%s.%s,",$2->data.str, field1);
					field1 = strtok(NULL, ",");
				}

				char *field2 = strtok(read2, ",");
				while(field2!=NULL)
				{
					printf("%s.%s,", $6->data.str, field2);
					field2 = strtok(NULL, ",");
				}
				printf("\n\n");

				// Now print the catesian product
				// Take a row of 1st file then
				char * line1 = NULL, *line2=NULL;
    			size_t len1 = 0, len2=0;
    			ssize_t read_file1, read_file2;
				int count1=0, count2=0;
				int total_records=0;
				
				
				
				
				while (fgets(read1, 2000, file1))
				{
					read1[strcspn(read1, "\n")] = 0;
					if(count1==0)
					{

					}
					else
					{
						// restarting the file2
						count2=0;
						line2=NULL;
						len2=0;
						read_file2=0;
						fseek(file2, 0, SEEK_SET);
						while(fgets(read2, 2000, file2))
						{
							read2[strcspn(read2, "\n")] = 0;
							if(count2==0 || count2==1){count2++;}
							else
							{
								// printf("%c",line1[strlen(line1)-1]);
								// line1[strlen(line1)-1]='\0';
								printf("%s", read1);printf(",");printf("%s", read2);
								printf("\n");
								total_records++;
							}

						}
						printf("\n");


					}
					count1++;

				}
				printf("\nTotal records: %d\n", total_records);
				printf("\n--------------------------------------\n\n");
			}

		}


		|LB BRACK_NAME RB EQUI_JOIN L condition_equi G LB BRACK_NAME RB  {

			printf("Syntax is valid \n");

			//Check if tables exist
			char filename1[100],filename2[100];
			memset(filename1,0,100);
			memset(filename2,0,100);
			sprintf(filename1,"tables/%s.csv",$2->data.str);
			sprintf(filename2,"tables/%s.csv",$9->data.str);
			if(!if_file_exist(filename1)){
				printf("%s : No such file exists.\n", filename1);
			}else if(!if_file_exist(filename2)){
				printf("%s : No such file exists.\n", filename1);
			} else{
				FILE* file1 = fopen(filename1, "r");
				FILE* file2 = fopen(filename2, "r");

				char* variable1[100];
				char* variable2[100];
				int type1[100];
				int type2[100];
				char* value1[100];
				char* value2[100];

				char read1[2000];
				memset(read1,0,2000);
				char read2[1000];
				memset(read2,0,1000);

				fgets(read1,2000,file1);
				fgets(read2,2000,file2);
				read1[strcspn(read1,"\n")]=0;
				read2[strcspn(read2,"\n")]=0;

				char * field1 = strtok(read1, ",");
				int i = 0;

				// store the tablename.attribute name in variable1[100]
				while(field1 != NULL){
					char  temp[200];
					memset(temp, 0, 200);
					sprintf(temp, "%s.%s", $2->data.str, strdup(field1));
					// printf("%s\n", variable1[i]);
					variable1[i]=strdup(temp);
					i++;
					field1 = strtok(NULL, ",");
				}

				int num_of_fields1 = i;

				memset(read1, 0, 2000);
				fgets(read1, 2000, file1);   // reads the attribute type from the file
				read1[strcspn(read1, "\n")] = 0;

				field1 = strtok(read1, ",");
				i = 0;
				while(field1 != NULL){       // store the tablename.attribute type
					char* temp = strdup(field1);
					if(strcmp(temp, "int") == 0){
						type1[i] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type1[i] = 1;
					}
					i++;
					field1 = strtok(NULL, ",");
				}

				//Do the same work as above for table2
				char * field2 = strtok(read2, ",");
				int k = 0;

				// store the names in variable2[100] in the form of tablename.attr
				while(field2 != NULL){
					char  temp[200];
					memset(temp, 0, 200);
					sprintf(temp, "%s.%s", $9->data.str, strdup(field2));
					variable2[k]=strdup(temp);
					// printf("%s\n", variable[i]);
					k++;
					field2 = strtok(NULL, ",");
				}

				int num_of_fields2 = k;

				memset(read2, 0, 2000);
				fgets(read2, 2000, file2);   // reads the attribute type from the file
				read2[strcspn(read2, "\n")] = 0;

				field2 = strtok(read2, ",");
				k = 0;
				while(field2 != NULL){       // store the tablename.attribute type
					char* temp = strdup(field2);
						if(strcmp(temp, "int") == 0){
						type2[k] = 0;
					}
					if(strcmp(temp, "str") == 0){
						type2[k] = 1;
					}
					k++;
					field2 = strtok(NULL, ",");
				}
				printf("\n");
				int error=1; //flag to store if an error has occurred
				//print all the fields
				for(int i=0;i<num_of_fields1;i++){
					printf("%s ",variable1[i]);
				}
				for(int i=0;i<num_of_fields2;i++){
					printf("%s ",variable2[i]);
				}
				printf("\n");
				int num_of_results = 0;
				while(fgets (read1, 2000, file1)){    // start reading the data rows
					read1[strcspn(read1, "\n")] = 0;
					field1 = strtok(read1, ",");
					int i = 0;
					while(field1 !=  NULL){    // stores the attribute value in value array
						if (type1[i] == 0){  // number type
							value1[i] = strdup(field1);
						}
						else {    // string type
							char * temp = strdup(field1);
							temp[strlen(temp)-1] = '\0';
							value1[i] = strdup(temp+1);
						}
						i++;
						field1 = strtok(NULL, ",");
					}
					int count=0;
					// now value has the current data row value for table 1
					fseek(file2,0,SEEK_SET); //to reset file2 to point at beginning of file
					while(fgets(read2,2000,file2)){
						if(count>1)
						{
						read2[strcspn(read2, "\n")] = 0;
						field2 = strtok(read2, ",");
						int i = 0;
						while(field2 !=  NULL){    // stores the attribute value in value array
							if (type2[i] == 0){  // number type
								value2[i] = strdup(field2);
							}
							else {    // string type
								char * temp = strdup(field2);
								temp[strlen(temp)-1] = '\0';
								value2[i] = strdup(temp+1);
							}
							i++;
							field2 = strtok(NULL, ",");
						}

						//now we have got the required values,types etc for both the tables, now check the condition

						int currentrow  = ast_eval2($6, variable1,variable2, value1,value2, type1,type2, num_of_fields1,num_of_fields2, &error,$2->data.str,$9->data.str);   // call the ast function
						if (error != 1){    // if error is changed inside ast_eval
							break;
						}
						if(currentrow){    // if ast_eval return 1 print the current data row for both the tables
							num_of_results++;
							for(int i = 0; i < num_of_fields1; i++){
								printf("%s ", value1[i]);
							}
							for(int i = 0; i < num_of_fields2; i++){
								printf("%s ", value2[i]);
							}
							printf("\n");
						}
							memset(read2, 0, 2000);
					}
					count++;
				}
					memset(read1,0,2000);
				}

				if (error != 1){  // there is a error
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
					if(error ==4){
						printf("Cannot have the table names on the both sides of = condition equal");
					}
				}

				if(error == 1 && num_of_results == 0){
					printf("There were no successful matches \n");
				}

				if (error == 1 && num_of_results > 0){
					printf("\nNumber of matches: %d \n", num_of_results);
					printf("\n--------------------------------------\n\n");
				}

			}
		}
		|%empty;



condition_equi: BRACK_EQ AND condition_equi
		{
			union Ast_data data;
			$$ = new_ast(15, data, $1, $3);
		}
		| BRACK_EQ
		{
			$$ = $1;
		}
		;


BRACK_EQ: Y EQ Y
	{
		union Ast_data data;
		$$ = new_ast(10, data, $1, $3);
	}
	|LB condition_equi RB 
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

	|BRACK_NUM op BRACK_NUM
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|BRACK_NUM op2 BRACK_NUM
	{
		union Ast_data data;
		$$ = new_ast($2, data, $1, $3);
	}
	|BRACK_STRING op2 BRACK_STRING
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
			$3->last->next = NULL;			
			$$ = $3;
		}
	   	   |Y COMMA attr_list
		{
			$3->last->next = malloc(sizeof(struct attr));
			$3->last->next->str = strdup($1->data.str);
			$3->last =   $3->last->next;
			$3->last->next = NULL;
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

		for(int i = 0; i < strlen($3->data.str); i++){
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
