#include <stdio.h>
#include <stdlib.h>
#include <string.h>




union Ast_data{
	int num;
	char* str;


};


// 0 for leaf node with int value;
// 1 for leaf node with string value;
// 2 for leaf node with column name;




struct ast_tree{

	int nodetype;     // 0, 1 , 2 for leaf nodes  and other values for operators

	union Ast_data data;

	struct ast_tree * left;

	struct ast_tree * right;
	
};




struct attr{
	
	char * str;
	struct attr* next;

};

struct attr_list{

	struct attr * first;
	struct attr * last; 	

	
};






struct ast_tree * new_ast(int nodetype, union Ast_data data_value, struct ast_tree * l, struct ast_tree * r);

int evaluatenum(int nodetype, int left, int right, int * flag);

int evaluatestr(int nodetype, char * strleft, char * strright, int *flag);

int ast_eval(struct ast_tree * tree, char ** variable, char ** value, int * type, int num_of_fields, int * flag);


void printinorder(struct ast_tree* node);

void printattrlist(struct attr_list* list);

void reverseattrlist(struct attr_list* list);




